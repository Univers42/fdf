/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_tube.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:53 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:25:54 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void apply_tube_transformation(t_app *fdf)
{
	float base_radius = fminf(fdf->width, fdf->height) / 4.0f;
	float height_limit = fdf->height * 0.5f;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Map grid coordinates similar to your original algorithm
			float angle = ((float)x / fdf->width) * 2.0f * M_PI;
			float radius = base_radius + fdf->points[index] * 0.3f;
			float height = (float)y - (fdf->height / 2.0f); // Center the height
			
			float tube_x, tube_y, tube_z;
			
			// Check if we're at the top or bottom edge to create caps
			if (fabsf(height) >= height_limit * 0.95f)
			{
				// Create circular caps at top and bottom using 2D coordinates
				float center_x = fdf->width / 2.0f;
				float center_y = fdf->height / 2.0f;
				
				// Calculate distance from center of the grid
				float dx = x - center_x;
				float dy = (y < center_y) ? (y - 0) : (y - (fdf->height - 1)); // Distance from edge
				float grid_radius = sqrtf(dx * dx + dy * dy);
				float max_grid_radius = fdf->width / 2.0f;
				
				// Only create cap if point is within circular boundary
				if (grid_radius <= max_grid_radius)
				{
					// Map grid position to cap circle
					float cap_ratio = grid_radius / max_grid_radius;
					float cap_radius = cap_ratio * radius;
					
					// Create flat circular surface
					tube_x = cap_radius * cosf(angle);
					tube_y = height; // Keep at cap level
					tube_z = cap_radius * sinf(angle);
				}
				else
				{
					// Points outside circle - don't render (move to center)
					tube_x = 0.0f;
					tube_y = height;
					tube_z = 0.0f;
				}
			}
			else
			{
				// Normal cylinder wall
				tube_x = radius * cosf(angle);
				tube_y = height; // Y stays the same (cylinder height)
				tube_z = radius * sinf(angle);
			}
			
			// Apply transformation matrix
			float sp[4] = {tube_x, tube_y, tube_z, 1};
			float *dp = (float *)&fdf->transformed_points[index];
			matrix4_dot_product(fdf->transformation_stack.combined, sp, dp);
		}
	}
}
