/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_chips.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:25:22 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void apply_chips_transformation(t_app *fdf)
{
	float scale = fminf(fdf->width, fdf->height) / 3.0f;
	float a = 0.3f; // Controls the curvature
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Normalize coordinates to [-1, 1]
			float norm_x = (2.0f * x / (fdf->width - 1)) - 1.0f;
			float norm_y = (2.0f * y / (fdf->height - 1)) - 1.0f;
			
			float chip_x = norm_x * scale;
			float chip_y = norm_y * scale;
			
			// Hyperbolic paraboloid equation: z = a * (x² - y²)
			// This creates the classic saddle/Pringles shape
			float chip_z = a * (norm_x * norm_x - norm_y * norm_y) * scale;
			
			// Add the original Z variation for texture
			chip_z += fdf->points[index] * 0.1f;
			
			// Apply transformation matrix
			float sp[4] = {chip_x, chip_y, chip_z, 1};
			float *dp = (float *)&fdf->transformed_points[index];
			matrix4_dot_product(fdf->transformation_stack.combined, sp, dp);
		}
	}
}
