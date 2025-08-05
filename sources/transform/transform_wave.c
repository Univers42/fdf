/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_wave.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:57 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:25:58 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void apply_wave_transformation(t_app *fdf)
{
	float wave_amplitude = fminf(fdf->width, fdf->height) / 6.0f;
	float base_radius = fminf(fdf->width, fdf->height) / 3.0f;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Map to wave coordinates
			float norm_x = (2.0f * x / (fdf->width - 1)) - 1.0f;
			float norm_y = (2.0f * y / (fdf->height - 1)) - 1.0f;
			
			float wave_x = norm_x * base_radius;
			float wave_y = norm_y * base_radius;
			
			// Create complex wave interference pattern
			float freq1 = 3.0f, freq2 = 5.0f, freq3 = 7.0f;
			float wave1 = sinf(norm_x * freq1 * M_PI) * cosf(norm_y * freq1 * M_PI);
			float wave2 = sinf(norm_x * freq2 * M_PI + M_PI/4) * cosf(norm_y * freq2 * M_PI);
			float wave3 = sinf(sqrtf(norm_x*norm_x + norm_y*norm_y) * freq3 * M_PI);
			
			// Combine waves with different amplitudes
			float wave_z = wave_amplitude * (
				0.5f * wave1 + 
				0.3f * wave2 + 
				0.2f * wave3
			);
			
			// Add radial wave component (like dropping stone in water)
			float dist_from_center = sqrtf(norm_x * norm_x + norm_y * norm_y);
			float radial_wave = sinf(dist_from_center * 8.0f * M_PI) * 
							   expf(-dist_from_center * 2.0f);
			wave_z += wave_amplitude * 0.4f * radial_wave;
			
			// Add original terrain as base modulation
			wave_z += fdf->points[index] * 0.1f;
			
			// Apply transformation matrix
			float sp[4] = {wave_x, wave_y, wave_z, 1};
			float *dp = (float *)&fdf->transformed_points[index];
			matrix4_dot_product(fdf->transformation_stack.combined, sp, dp);
		}
	}
}
