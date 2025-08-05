/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_cube.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:31 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:25:32 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void apply_cube_transformation(t_app *fdf)
{
	float cube_size = fminf(fdf->width, fdf->height) / 4.0f;
	int total_points = fdf->width * fdf->height;
	int points_per_face = total_points / 6;
	
	for (int y = 0; y < fdf->height; y++)
	{
		for (int x = 0; x < fdf->width; x++)
		{
			int index = y * fdf->width + x;
			
			// Determine which face this point belongs to
			int face = index / points_per_face;
			if (face >= 6) face = 5; // Clamp to last face
			
			// Calculate local coordinates within the face
			int local_idx = index % points_per_face;
			int face_width = fdf->width / 3;  // Divide width among faces
			int face_height = fdf->height / 2; // Divide height between top and bottom
			
			if (face_width == 0) face_width = 1;
			if (face_height == 0) face_height = 1;
			
			int local_x = local_idx % face_width;
			int local_y = local_idx / face_width;
			
			// Normalize to [-1, 1] range
			float u = (local_x / (float)(face_width - 1)) * 2.0f - 1.0f;
			float v = (local_y / (float)(face_height - 1)) * 2.0f - 1.0f;
			
			float cube_x, cube_y, cube_z;
			
			// Map to cube faces with proper coordinates
			switch (face)
			{
				case 0: // Front face (Z = +1)
					cube_x = u * cube_size;
					cube_y = v * cube_size;
					cube_z = cube_size + fdf->points[index] * 0.05f;
					break;
				case 1: // Back face (Z = -1)
					cube_x = -u * cube_size;  // Flip X for back face
					cube_y = v * cube_size;
					cube_z = -cube_size + fdf->points[index] * 0.05f;
					break;
				case 2: // Right face (X = +1)
					cube_x = cube_size + fdf->points[index] * 0.05f;
					cube_y = v * cube_size;
					cube_z = -u * cube_size;
					break;
				case 3: // Left face (X = -1)
					cube_x = -cube_size + fdf->points[index] * 0.05f;
					cube_y = v * cube_size;
					cube_z = u * cube_size;
					break;
				case 4: // Top face (Y = +1)
					cube_x = u * cube_size;
					cube_y = cube_size + fdf->points[index] * 0.05f;
					cube_z = -v * cube_size;
					break;
				case 5: // Bottom face (Y = -1)
				default:
					cube_x = u * cube_size;
					cube_y = -cube_size + fdf->points[index] * 0.05f;
					cube_z = v * cube_size;
					break;
			}
			
			// Apply transformation matrix
			float sp[4] = {cube_x, cube_y, cube_z, 1};
			float *dp = (float *)&fdf->transformed_points[index];
			matrix4_dot_product(fdf->transformation_stack.combined, sp, dp);
		}
	}
}
