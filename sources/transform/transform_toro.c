/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_toro.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:49 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:25:50 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	apply_torus_transformation(t_app *fdf, float major_radius, float minor_radius)
{
	int		x, y, index;
	float	u, v;
	float	torus_x, torus_y, torus_z;

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
			
			// Store in transformed_points for rendering
			fdf->transformed_points[index].x = torus_x;
			fdf->transformed_points[index].y = torus_y;
			fdf->transformed_points[index].z = torus_z + fdf->points[index] * 0.1f;
		}
	}
}
