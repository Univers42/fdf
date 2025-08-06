/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_toro.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:49 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/06 04:12:28 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	apply_torus_transformation(t_app *fdf, float major_radius, float minor_radius)
{
	int		x, y, index;
	float	u, v;
	float	torus_x, torus_y, torus_z;

	// Calculate appropriate radii if not provided
	if (major_radius == 0 || minor_radius == 0)
	{
		major_radius = fminf(fdf->width, fdf->height) / 3.0f;
		minor_radius = major_radius / 4.0f;
	}

	for (y = 0; y < fdf->height; y++)
	{
		for (x = 0; x < fdf->width; x++)
		{
			index = y * fdf->width + x;
			
			// Map grid coordinates to torus parameters
			u = (2.0f * M_PI * x) / fdf->width;
			v = (2.0f * M_PI * y) / fdf->height;
			
			// Torus parametric equations
			torus_x = (major_radius + minor_radius * cosf(v)) * cosf(u);
			torus_y = (major_radius + minor_radius * cosf(v)) * sinf(u);
			torus_z = minor_radius * sinf(v);
			
			// Add original terrain as texture detail
			torus_z += fdf->points[index] * 0.1f;
			
			// Apply transformation matrix - this is where auto-rotation happens!
			float sp[4] = {torus_x, torus_y, torus_z, 1};
			float *dp = (float *)&fdf->transformed_points[index];
			matrix4_dot_product(fdf->transformation_stack.combined, sp, dp);
		}
	}
}
