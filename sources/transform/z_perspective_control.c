/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_perspective_control.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:31 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:26:32 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define Z_SCALE_STEP 0.1f
#define MAX_Z_LIMIT 500.0f
#define MIN_Z_LIMIT 0.0f
#define CONVERGENCE_THRESHOLD 500.0f
#define CONVERGENCE_FACTOR 0.7f

typedef struct s_z_perspective {
	float	scale_factor;
	float	original_max_z;
	float	original_min_z;
	bool	initialized;
	float	*original_z_values;
	int		total_points;
} t_z_perspective;

static t_z_perspective g_z_control = {1.0f, 0.0f, 0.0f, false, NULL, 0};

// Initialize the z-perspective system
void init_z_perspective_control(t_app *fdf)
{
	if (g_z_control.initialized && g_z_control.original_z_values)
		return;
	
	g_z_control.total_points = fdf->width * fdf->height;
	g_z_control.original_max_z = fdf->max_z;
	g_z_control.original_min_z = fdf->min_z;
	g_z_control.scale_factor = 1.0f;
	
	// Store original z-values
	if (g_z_control.original_z_values)
		free(g_z_control.original_z_values);
		
	g_z_control.original_z_values = malloc(sizeof(float) * g_z_control.total_points);
	if (!g_z_control.original_z_values)
		return;
	
	// Copy original values
	for (int i = 0; i < g_z_control.total_points; i++)
		g_z_control.original_z_values[i] = fdf->points[i];
	
	g_z_control.initialized = true;
	printf("Z-Perspective Control initialized (original range: %.1f to %.1f)\n", 
		   g_z_control.original_min_z, g_z_control.original_max_z);
}

// Apply convergence function for extreme values
static float apply_convergence(float original_z, float scale_factor)
{
	float scaled_z = original_z * scale_factor;
	
	// Handle positive extreme values (peaks)
	if (scaled_z > CONVERGENCE_THRESHOLD)
	{
		float excess = scaled_z - CONVERGENCE_THRESHOLD;
		float converged_excess = excess * CONVERGENCE_FACTOR;
		
		// Logarithmic convergence for very high values
		if (excess > 200.0f)
		{
			converged_excess = 200.0f + logf(1.0f + (excess - 200.0f) / 100.0f) * 50.0f;
		}
		
		scaled_z = CONVERGENCE_THRESHOLD + converged_excess;
		
		// Hard limit at MAX_Z_LIMIT
		if (scaled_z > MAX_Z_LIMIT)
			scaled_z = MAX_Z_LIMIT;
	}
	
	// Handle negative values (valleys) - preserve unless explicitly in map
	if (original_z < 0.0f)
	{
		// Allow negative values from original map, but scale them
		scaled_z = original_z * scale_factor;
		
		// Prevent extreme negative scaling
		float min_allowed = g_z_control.original_min_z * 2.0f;
		if (scaled_z < min_allowed)
			scaled_z = min_allowed;
	}
	else if (scaled_z < MIN_Z_LIMIT)
	{
		// Positive values shouldn't go below 0 unless original was negative
		scaled_z = MIN_Z_LIMIT;
	}
	
	return scaled_z;
}

// Reduce z-perspective (Ctrl + Down Arrow)
void reduce_z_perspective(t_app *fdf)
{
	if (!g_z_control.initialized)
		init_z_perspective_control(fdf);
	
	if (!g_z_control.original_z_values)
		return;
	
	// Decrease scale factor
	g_z_control.scale_factor -= Z_SCALE_STEP;
	if (g_z_control.scale_factor < 0.1f)
		g_z_control.scale_factor = 0.1f;
	
	// Apply new scaling with convergence
	float new_max = 0.0f, new_min = 0.0f;
	
	for (int i = 0; i < g_z_control.total_points; i++)
	{
		float original_z = g_z_control.original_z_values[i];
		float new_z = apply_convergence(original_z, g_z_control.scale_factor);
		
		fdf->points[i] = new_z;
		
		// Track new range
		if (i == 0 || new_z > new_max) new_max = new_z;
		if (i == 0 || new_z < new_min) new_min = new_z;
	}
	
	// Update FDF ranges
	fdf->max_z = new_max;
	fdf->min_z = new_min;
	
	printf("Z-Perspective reduced (scale: %.1f, range: %.1f to %.1f)\n", 
		   g_z_control.scale_factor, new_min, new_max);
}

// Increase z-perspective (Ctrl + Up Arrow)
void increase_z_perspective(t_app *fdf)
{
	if (!g_z_control.initialized)
		init_z_perspective_control(fdf);
	
	if (!g_z_control.original_z_values)
		return;
	
	// Increase scale factor
	g_z_control.scale_factor += Z_SCALE_STEP;
	if (g_z_control.scale_factor > 3.0f)
		g_z_control.scale_factor = 3.0f;
	
	// Apply new scaling with convergence
	float new_max = 0.0f, new_min = 0.0f;
	
	for (int i = 0; i < g_z_control.total_points; i++)
	{
		float original_z = g_z_control.original_z_values[i];
		float new_z = apply_convergence(original_z, g_z_control.scale_factor);
		
		fdf->points[i] = new_z;
		
		// Track new range
		if (i == 0 || new_z > new_max) new_max = new_z;
		if (i == 0 || new_z < new_min) new_min = new_z;
	}
	
	// Update FDF ranges
	fdf->max_z = new_max;
	fdf->min_z = new_min;
	
	printf("Z-Perspective increased (scale: %.1f, range: %.1f to %.1f)\n", 
		   g_z_control.scale_factor, new_min, new_max);
}

// Reset z-perspective to original values
void reset_z_perspective(t_app *fdf)
{
	if (!g_z_control.initialized || !g_z_control.original_z_values)
		return;
	
	g_z_control.scale_factor = 1.0f;
	
	// Restore original values
	for (int i = 0; i < g_z_control.total_points; i++)
		fdf->points[i] = g_z_control.original_z_values[i];
	
	// Restore original ranges
	fdf->max_z = g_z_control.original_max_z;
	fdf->min_z = g_z_control.original_min_z;
	
	printf("Z-Perspective reset (original range: %d to %d)\n", 
		   fdf->min_z, fdf->max_z);
}

// Get current scale factor for display
float get_z_perspective_scale(void)
{
	return g_z_control.scale_factor;
}

// Cleanup z-perspective system
void cleanup_z_perspective_control(void)
{
	if (g_z_control.original_z_values)
	{
		free(g_z_control.original_z_values);
		g_z_control.original_z_values = NULL;
	}
	g_z_control.initialized = false;
	g_z_control.scale_factor = 1.0f;
}

// Advanced perspective control with custom convergence
void set_z_perspective_mode(t_app *fdf, int mode)
{
	if (!g_z_control.initialized)
		init_z_perspective_control(fdf);
	
	float target_scale = 1.0f;
	
	switch (mode)
	{
		case 0: // Flat mode - extreme reduction
			target_scale = 0.2f;
			break;
		case 1: // Low perspective
			target_scale = 0.5f;
			break;
		case 2: // Normal
			target_scale = 1.0f;
			break;
		case 3: // High perspective
			target_scale = 1.5f;
			break;
		case 4: // Extreme perspective
			target_scale = 2.0f;
			break;
		default:
			return;
	}
	
	g_z_control.scale_factor = target_scale;
	
	// Apply the scaling
	float new_max = 0.0f, new_min = 0.0f;
	
	for (int i = 0; i < g_z_control.total_points; i++)
	{
		float original_z = g_z_control.original_z_values[i];
		float new_z = apply_convergence(original_z, g_z_control.scale_factor);
		
		fdf->points[i] = new_z;
		
		if (i == 0 || new_z > new_max) new_max = new_z;
		if (i == 0 || new_z < new_min) new_min = new_z;
	}
	
	fdf->max_z = (int)new_max;
	fdf->min_z = (int)new_min;
	
	printf("Z-Perspective mode %d set (scale: %.1f)\n", mode, target_scale);
}
