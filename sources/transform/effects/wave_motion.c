/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wave_motion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:27 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 14:16:08 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Apply WILD wave motion dance - creates massive traveling waves
void apply_dance_wave_motion(t_app *fdf)
{
	float wave_amplitude = 40.0f * g_dance.move_intensity;
	float wave_freq = 3.0f * g_dance.rhythm_multiplier;
	
	// Figure-8 movement pattern with HUGE amplitude
	float move_x = sinf(g_dance.time_accumulator * wave_freq) * 25.0f;
	float move_z = sinf(g_dance.time_accumulator * wave_freq * 2.0f) * 15.0f;
	
	transformation_stack_translate(&fdf->transformation_stack, move_x * 0.1f, 0, move_z * 0.1f);
	
	// MASSIVE wave deformation through the geometry
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Multiple HUGE traveling waves
			float wave_offset = (norm_x + norm_y) * M_PI * 4.0f;
			float wave1 = sinf(g_dance.time_accumulator * wave_freq * 4.0f + wave_offset) * wave_amplitude;
			
			// Add interference patterns
			float wave2 = sinf(g_dance.time_accumulator * wave_freq * 2.5f + norm_x * M_PI * 6.0f) * wave_amplitude * 0.7f;
			float wave3 = cosf(g_dance.time_accumulator * wave_freq * 3.2f + norm_y * M_PI * 5.0f) * wave_amplitude * 0.5f;
			
			fdf->points[index] = g_dance.original_points[index] + wave1 + wave2 + wave3;
		}
	}
}
