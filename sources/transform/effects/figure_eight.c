/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure_eight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 14:15:27 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Apply INSANE figure-eight dance move - complex orbital motion
void apply_dance_figure_eight(t_app *fdf)
{
	float orbit_freq = 2.5f * g_dance.rhythm_multiplier;
	float orbit_size = 40.0f * g_dance.move_intensity;
	
	// MASSIVE figure-8 orbital motion
	float t = g_dance.time_accumulator * orbit_freq;
	float move_x = sinf(t) * orbit_size;
	float move_y = sinf(t * 2.0f) * orbit_size * 0.8f;
	float move_z = cosf(t * 1.3f) * orbit_size * 0.6f;
	
	transformation_stack_translate(&fdf->transformation_stack, 
		move_x * 0.05f, move_y * 0.05f, move_z * 0.05f);
	
	// CRAZY synchronized rotation on all axes
	transformation_stack_rotate_x(&fdf->transformation_stack, sinf(t * 2.2f) * 0.08f);
	transformation_stack_rotate_y(&fdf->transformation_stack, cosf(t * 1.8f) * 0.1f);
	transformation_stack_rotate_z(&fdf->transformation_stack, sinf(t * 3.1f) * 0.06f);
	
	// Add geometric distortion following the orbital pattern
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Create orbital wave effect
			float orbital_wave = sinf(t + norm_x * M_PI * 2.0f) * cosf(t * 1.5f + norm_y * M_PI * 3.0f);
			float distortion = orbital_wave * 25.0f * g_dance.move_intensity;
			
			fdf->points[index] = g_dance.original_points[index] + distortion;
		}
	}
}
