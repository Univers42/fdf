/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_dna.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:35 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:25:36 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void apply_dna_transformation(t_app *fdf)
{
	float dna_radius_base = fminf(fdf->width, fdf->height) / 6.0f;
	float map_radius = dna_radius_base;
	float height_limit = fdf->height * 0.9f;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Map coordinates to height and position
			float height = (float)y - (fdf->height / 2.0f); // Center the height
			float angle = height * 0.1f; // Control twist rate
			
			// Create two helixes based on X coordinate (even/odd pattern)
			float phase;
			if (x % 2 == 0)
				phase = 0.0f;          // First helix
			else
				phase = M_PI;          // Second helix (180° offset)
			
			// Calculate radius with original Z influence
			float radius = map_radius * 0.5f + fdf->points[index] * 0.2f;
			
			// Close the ends by reducing radius at top and bottom
			if (fabsf(height) > height_limit)
			{
				float end_factor = (height_limit - fabsf(height)) / (height_limit * 0.1f);
				end_factor = fmaxf(0.0f, end_factor); // Ensure non-negative
				radius *= end_factor;
			}
			
			// Apply DNA helix transformation
			float dna_x = radius * cosf(angle + phase);
			float dna_y = height;
			float dna_z = radius * sinf(angle + phase);
			
			// Apply transformation matrix
			float sp[4] = {dna_x, dna_y, dna_z, 1};
			float *dp = (float *)&fdf->transformed_points[index];
			matrix4_dot_product(fdf->transformation_stack.combined, sp, dp);
		}
	}
}
