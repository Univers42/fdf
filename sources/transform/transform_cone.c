/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:27 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:25:28 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void apply_cone_transformation(t_app *fdf)
{
	float max_radius = fminf(fdf->width, fdf->height) / 4.0f;
	float height_limit = fdf->height * 0.5f;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Map grid coordinates to cone coordinates
			float angle = ((float)x / fdf->width) * 2.0f * M_PI;
			float height = (float)y - (fdf->height / 2.0f); // Center the height
			
			float cone_x, cone_y, cone_z;
			
			// Create closed cone - radius decreases with height
			if (fabsf(height) < height_limit)
			{
				float radius = max_radius * (1.0f - fabsf(height) / height_limit);
				radius += fdf->points[index] * 0.1f; // Add Z variation for texture
				
				cone_x = radius * cosf(angle);
				cone_y = height;
				cone_z = radius * sinf(angle);
			}
			else
			{
				// Close the tip
				cone_x = 0.0f;
				cone_y = height;
				cone_z = 0.0f;
			}
			
			// Apply transformation matrix
			float sp[4] = {cone_x, cone_y, cone_z, 1};
			float *dp = (float *)&fdf->transformed_points[index];
			matrix4_dot_product(fdf->transformation_stack.combined, sp, dp);
		}
	}
}
