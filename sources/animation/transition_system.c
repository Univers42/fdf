/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition_system.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:28:19 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 17:27:22 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>

#define TRANSITION_FRAMES 60
#define SHAPE_COUNT 11

typedef enum e_shape_type {
	SHAPE_ORIGINAL = 0,
	SHAPE_TORUS = 1,
	SHAPE_SPHERE = 2,
	SHAPE_CUBE = 3,
	SHAPE_PYRAMID = 4,
	SHAPE_DNA = 5,
	SHAPE_CHIPS = 6,
	SHAPE_WAVE = 7,
	SHAPE_HEART = 8,
	SHAPE_CONE = 9,
	SHAPE_TUBE = 10
} t_shape_type;

typedef struct s_transition {
	int				frame;
	int				max_frames;
	bool			active;
	t_shape_type	current_shape;
	t_shape_type	target_shape;
	float			*original_positions;
	bool			initialized;
} t_transition;

static t_transition g_transition = {0, TRANSITION_FRAMES, false, SHAPE_ORIGINAL, SHAPE_ORIGINAL, NULL, false};

// Ease-in-out function
static float ease_in_out(float t)
{
	return t * t * (3.0f - 2.0f * t);
}

// Store original grid positions once
static void store_original_positions(t_app *fdf)
{
	if (g_transition.initialized)
		return;
		
	if (g_transition.original_positions)
		free(g_transition.original_positions);
		
	g_transition.original_positions = malloc(sizeof(float) * fdf->width * fdf->height * 3);
	if (!g_transition.original_positions)
		return;
	
	// Store original grid positions
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			g_transition.original_positions[index * 3 + 0] = (float)x;
			g_transition.original_positions[index * 3 + 1] = (float)y;
			g_transition.original_positions[index * 3 + 2] = fdf->points[index];
		}
	}
	g_transition.initialized = true;
}

// Get shape position based on shape type
static void get_shape_position(t_shape_type shape, t_app *fdf, int x, int y, float *out_x, float *out_y, float *out_z)
{
	int index = y * fdf->width + x;
	float orig_z = g_transition.original_positions[index * 3 + 2];
	
	// Prevent division by zero and out of bounds access
	if (fdf->width <= 1 || fdf->height <= 1 || index >= fdf->width * fdf->height)
	{
		*out_x = (float)x;
		*out_y = (float)y;
		*out_z = orig_z;
		return;
	}
	
	// Direct calculation without creating temporary app structures
	switch (shape)
	{
		case SHAPE_ORIGINAL:
			*out_x = (float)x;
			*out_y = (float)y;
			*out_z = orig_z;
			break;
			
		case SHAPE_TORUS:
		{
			float major_r = fminf(fdf->width, fdf->height) / 3.0f;
			float minor_r = major_r / 4.0f;
			float u = (2.0f * M_PI * x) / (float)(fdf->width - 1);
			float v = (2.0f * M_PI * y) / (float)(fdf->height - 1);
			
			*out_x = (major_r + minor_r * cosf(v)) * cosf(u);
			*out_y = (major_r + minor_r * cosf(v)) * sinf(u);
			*out_z = minor_r * sinf(v) + orig_z * 0.05f;
			break;
		}
		
		case SHAPE_SPHERE:
		{
			float radius = fminf(fdf->width, fdf->height) / 3.0f;
			float theta = (2.0f * M_PI * x) / (float)(fdf->width - 1);
			float phi = (M_PI * y) / (float)(fdf->height - 1);
			
			*out_x = radius * sinf(phi) * cosf(theta);
			*out_y = radius * sinf(phi) * sinf(theta);
			*out_z = radius * cosf(phi) + orig_z * 0.05f;
			break;
		}
		
		case SHAPE_CUBE:
		{
			float cube_size = fminf(fdf->width, fdf->height) / 3.0f;
			float norm_x = (2.0f * x / (fdf->width - 1)) - 1.0f;
			float norm_y = (2.0f * y / (fdf->height - 1)) - 1.0f;
			
			*out_x = norm_x * cube_size / 2.0f;
			*out_y = norm_y * cube_size / 2.0f;
			
			// Simplified cube logic for transitions
			if (fabsf(norm_x) <= 0.8f && fabsf(norm_y) <= 0.8f)
			{
				float dist = sqrtf(norm_x * norm_x + norm_y * norm_y);
				*out_z = cube_size / 2.0f * (1.0f - dist * 0.3f) + orig_z * 0.1f;
			}
			else
				*out_z = orig_z * 0.1f;
			break;
		}
		
		case SHAPE_PYRAMID:
		{
			float base = fminf(fdf->width, fdf->height) / 3.0f;
			float norm_x = (2.0f * x / (fdf->width - 1)) - 1.0f;
			float norm_y = (2.0f * y / (fdf->height - 1)) - 1.0f;
			float dist = fmaxf(fabsf(norm_x), fabsf(norm_y));
			
			*out_x = norm_x * base / 2.0f;
			*out_y = norm_y * base / 2.0f;
			*out_z = (dist <= 1.0f) ? base * (1.0f - dist) + orig_z * 0.05f : orig_z * 0.05f;
			break;
		}
		
		case SHAPE_DNA:
		{
			float dna_radius = fminf(fdf->width, fdf->height) / 6.0f;
			float norm_y = (2.0f * y / (fdf->height - 1)) - 1.0f;
			float height_param = norm_y;
			float twist_angle = height_param * 4.0f * M_PI;
			
			// Simplified DNA for transitions
			float phase = (x % 2 == 0) ? 0.0f : M_PI;
			*out_x = dna_radius * cosf(twist_angle + phase);
			*out_y = height_param * fdf->height * 0.4f;
			*out_z = dna_radius * sinf(twist_angle + phase) + orig_z * 0.02f;
			break;
		}
		
		case SHAPE_CHIPS:
		{
			float scale = fminf(fdf->width, fdf->height) / 3.0f;
			float norm_x = (2.0f * x / (fdf->width - 1)) - 1.0f;
			float norm_y = (2.0f * y / (fdf->height - 1)) - 1.0f;
			
			*out_x = norm_x * scale;
			*out_y = norm_y * scale;
			*out_z = 0.3f * (norm_x * norm_x - norm_y * norm_y) * scale + orig_z * 0.1f;
			break;
		}
		
		case SHAPE_WAVE:
		{
			float wave_amplitude = fminf(fdf->width, fdf->height) / 6.0f;
			float base_radius = fminf(fdf->width, fdf->height) / 3.0f;
			float norm_x = (2.0f * x / (fdf->width - 1)) - 1.0f;
			float norm_y = (2.0f * y / (fdf->height - 1)) - 1.0f;
			
			*out_x = norm_x * base_radius;
			*out_y = norm_y * base_radius;
			
			float wave1 = sinf(norm_x * 3.0f * M_PI) * cosf(norm_y * 3.0f * M_PI);
			*out_z = wave_amplitude * wave1 + orig_z * 0.1f;
			break;
		}
		
		case SHAPE_HEART:
		{
			float heart_scale = fminf(fdf->width, fdf->height) / 4.0f;
			float norm_x = (2.0f * x / (fdf->width - 1)) - 1.0f;
			float norm_y = -((2.0f * y / (fdf->height - 1)) - 1.0f); // Flip Y
			
			*out_x = norm_x * heart_scale;
			*out_y = norm_y * heart_scale;
			
			// Simplified heart shape for transitions
			if (norm_y > 0.0f)
			{
				// Upper lobes
				float dist1 = sqrtf((norm_x + 0.5f) * (norm_x + 0.5f) + (norm_y - 0.3f) * (norm_y - 0.3f));
				float dist2 = sqrtf((norm_x - 0.5f) * (norm_x - 0.5f) + (norm_y - 0.3f) * (norm_y - 0.3f));
				if (dist1 < 0.6f || dist2 < 0.6f)
					*out_z = heart_scale * 0.3f;
				else
					*out_z = 0.0f;
			}
			else
			{
				// Lower point
				float point_factor = 1.0f + norm_y;
				if (point_factor > 0.0f && fabsf(norm_x) < point_factor * 0.8f)
					*out_z = heart_scale * 0.2f * point_factor;
				else
					*out_z = 0.0f;
			}
			*out_z += orig_z * 0.02f;
			break;
		}
		
		case SHAPE_CONE:
		{
			float max_radius = fminf(fdf->width, fdf->height) / 4.0f;
			float angle = ((float)x / fdf->width) * 2.0f * M_PI;
			float height = (float)y - (fdf->height / 2.0f);
			float height_limit = fdf->height * 0.5f;
			
			if (fabsf(height) < height_limit)
			{
				float radius = max_radius * (1.0f - fabsf(height) / height_limit);
				*out_x = radius * cosf(angle);
				*out_y = height;
				*out_z = radius * sinf(angle);
			}
			else
			{
				*out_x = 0.0f;
				*out_y = height;
				*out_z = 0.0f;
			}
			break;
		}
		
		case SHAPE_TUBE:
		{
			float base_radius = fminf(fdf->width, fdf->height) / 4.0f;
			float height_limit = fdf->height * 0.5f;
			
			float angle = ((float)x / fdf->width) * 2.0f * M_PI;
			float radius = base_radius + orig_z * 0.3f;
			float height = (float)y - (fdf->height / 2.0f);
			
			// Check if we're at the top or bottom edge to create caps
			if (fabsf(height) >= height_limit * 0.95f)
			{
				// Create circular caps using 2D grid coordinates
				float center_x = fdf->width / 2.0f;
				float center_y = fdf->height / 2.0f;
				
				// Calculate distance from center of the grid
				float dx = x - center_x;
				float dy = (y < center_y) ? (y - 0) : (y - (fdf->height - 1));
				float grid_radius = sqrtf(dx * dx + dy * dy);
				float max_grid_radius = fdf->width / 2.0f;
				
				// Only create cap if point is within circular boundary
				if (grid_radius <= max_grid_radius)
				{
					float cap_ratio = grid_radius / max_grid_radius;
					float cap_radius = cap_ratio * radius;
					
					*out_x = cap_radius * cosf(angle);
					*out_y = height;
					*out_z = cap_radius * sinf(angle);
				}
				else
				{
					// Points outside circle
					*out_x = 0.0f;
					*out_y = height;
					*out_z = 0.0f;
				}
			}
			else
			{
				// Normal cylinder wall
				*out_x = radius * cosf(angle);
				*out_y = height;
				*out_z = radius * sinf(angle);
			}
			break;
		}
	}
}

// Apply current shape with transformation matrix (for persistent shapes)
static void apply_shape_with_transform(t_app *fdf, t_shape_type shape)
{
	switch (shape)
	{
		case SHAPE_ORIGINAL:
			// Use normal point transformation - matrix will be applied in transform_points()
			break;
		case SHAPE_TORUS:
			apply_torus_transformation(fdf, 0, 0); // Parameters will be calculated inside
			break;
		case SHAPE_SPHERE:
			// For sphere, apply shape transformation
			for (int y = 0; y < fdf->height; y++)
			{
				for (int x = 0; x < fdf->width; x++)
				{
					int index = y * fdf->width + x;
					float shape_x, shape_y, shape_z;
					get_shape_position(SHAPE_SPHERE, fdf, x, y, &shape_x, &shape_y, &shape_z);
					
					float sp[4] = {shape_x, shape_y, shape_z, 1};
					float *dp = (float *)&fdf->transformed_points[index];
					matrix4_dot_product(fdf->transformation_stack.combined, sp, dp);
				}
			}
			break;
		case SHAPE_CUBE:
			apply_cube_transformation(fdf);
			break;
		case SHAPE_PYRAMID:
			apply_pyramid_transformation(fdf);
			break;
		case SHAPE_DNA:
			apply_dna_transformation(fdf);
			break;
		case SHAPE_CHIPS:
			apply_chips_transformation(fdf);
			break;
		case SHAPE_WAVE:
			apply_wave_transformation(fdf);
			break;
		case SHAPE_HEART:
			apply_heart_transformation(fdf);
			break;
		case SHAPE_CONE:
			apply_cone_transformation(fdf);
			break;
		case SHAPE_TUBE:
			apply_tube_transformation(fdf);
			break;
	}
}

void	transition_update(t_app *fdf)
{
	if (!g_transition.active && g_transition.current_shape == SHAPE_ORIGINAL)
		return;

	store_original_positions(fdf);
	if (!g_transition.original_positions)
		return;

	// If transition is active, interpolate between shapes
	if (g_transition.active)
	{
		float progress = (float)g_transition.frame / g_transition.max_frames;
		float smooth_t = ease_in_out(progress);

		for (int y = 0; y < fdf->height; y++)
		{
			for (int x = 0; x < fdf->width; x++)
			{
				int index = y * fdf->width + x;
				
				// Get current shape position
				float current_x = 0.0f, current_y = 0.0f, current_z = 0.0f;
				get_shape_position(g_transition.current_shape, fdf, x, y, &current_x, &current_y, &current_z);
				
				// Get target shape position
				float target_x = 0.0f, target_y = 0.0f, target_z = 0.0f;
				get_shape_position(g_transition.target_shape, fdf, x, y, &target_x, &target_y, &target_z);
				
				// Interpolate between current and target positions
				float final_x = current_x + (target_x - current_x) * smooth_t;
				float final_y = current_y + (target_y - current_y) * smooth_t;
				float final_z = current_z + (target_z - current_z) * smooth_t;
				
				// Apply transformation matrix to the interpolated position
				// This is where auto-rotation gets applied!
				float sp[4], *dp;
				sp[0] = final_x;
				sp[1] = final_y;
				sp[2] = final_z;
				sp[3] = 1;
				dp = (float *)&fdf->transformed_points[index];
				matrix4_dot_product(fdf->transformation_stack.combined, sp, dp);
			}
		}
		
		g_transition.frame++;
		if (g_transition.frame >= g_transition.max_frames)
		{
			g_transition.active = false;
			g_transition.frame = 0;
			g_transition.current_shape = g_transition.target_shape;
		}
	}
	// If transition is complete and we're not in original shape, maintain current shape
	// This is the key part - shapes must use the transformation matrix!
	else if (g_transition.current_shape != SHAPE_ORIGINAL)
	{
		apply_shape_with_transform(fdf, g_transition.current_shape);
	}
}

void	transition_start_torus(bool to_torus)
{
	// Cycle through shapes in circular buffer manner
	(void)to_torus; // Mark as unused parameter
	
	// Allow new transitions even if one is active (interrupt current transition)
	t_shape_type next_shape = (g_transition.current_shape + 1) % SHAPE_COUNT;
	
	g_transition.active = true;
	g_transition.frame = 0;
	g_transition.target_shape = next_shape;
}

bool	transition_is_active(void)
{
	// Return true if we're animating OR if we're in a transformed shape (not original)
	return g_transition.active || g_transition.current_shape != SHAPE_ORIGINAL;
}

// Add cleanup function for transition system
void	transition_cleanup(void)
{
	if (g_transition.original_positions)
	{
		free(g_transition.original_positions);
		g_transition.original_positions = NULL;
	}
	g_transition.initialized = false;
	g_transition.active = false;
	g_transition.frame = 0;
	g_transition.current_shape = SHAPE_ORIGINAL;
	g_transition.target_shape = SHAPE_ORIGINAL;
}
