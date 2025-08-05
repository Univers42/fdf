/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_pyramid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:45 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:25:46 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void apply_pyramid_transformation(t_app *fdf)
{
	float pyramid_base = fminf(fdf->width, fdf->height) / 3.0f;
	float pyramid_height = pyramid_base;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Map to pyramid coordinates
			float norm_x = (2.0f * x / (fdf->width - 1)) - 1.0f;
			float norm_y = (2.0f * y / (fdf->height - 1)) - 1.0f;
			
			float pyramid_x = norm_x * pyramid_base / 2.0f;
			float pyramid_y = norm_y * pyramid_base / 2.0f;
			
			// Calculate distance from center for pyramid shape
			float dist_from_center = fmaxf(fabsf(norm_x), fabsf(norm_y));
			
			// Create pyramid volume (square base tapering to point)
			float pyramid_z;
			if (dist_from_center <= 1.0f)
			{
				// Inside pyramid volume - height decreases linearly from center
				pyramid_z = pyramid_height * (1.0f - dist_from_center);
			}
			else
			{
				pyramid_z = 0.0f;
			}
			
			// Add original terrain as base texture
			pyramid_z += fdf->points[index] * 0.05f;
			
			// Apply transformation matrix
			float sp[4] = {pyramid_x, pyramid_y, pyramid_z, 1};
			float *dp = (float *)&fdf->transformed_points[index];
			matrix4_dot_product(fdf->transformation_stack.combined, sp, dp);
		}
	}
}
