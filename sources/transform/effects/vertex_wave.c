/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_wave.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:34:42 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 14:16:04 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>


// Apply vertex wave effect - creates rippling waves across the surface
void    apply_vertex_wave_effect(t_app *fdf)
{
	if (!g_obj_effects.original_points)
		return;
	
	float wave_amplitude = 20.0f * g_obj_effects.intensity;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Normalize coordinates
			float norm_x = (float)x / fdf->width;
			float norm_y = (float)y / fdf->height;
			
			// Create multiple wave patterns
			float wave1 = sinf((norm_x * 8.0f + g_obj_effects.time_accumulator) * M_PI);
			float wave2 = sinf((norm_y * 6.0f + g_obj_effects.time_accumulator * 0.7f) * M_PI);
			float wave3 = sinf(((norm_x + norm_y) * 5.0f + g_obj_effects.time_accumulator * 1.2f) * M_PI);
			
			// Combine waves
			float wave_effect = (wave1 + wave2 + wave3) / 3.0f;
			
			// Apply to Z coordinate
			fdf->points[index] = g_obj_effects.original_points[index] + wave_effect * wave_amplitude;
		}
	}
}