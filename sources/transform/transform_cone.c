/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:27 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/06 20:49:04 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>


void	apply_cone_transformation(t_app *fdf)
{
	t_meta_shape	s;

	s.max_radius = fminf(fdf->width, fdf->height) / 4.0f;
	s.height_limit = fdf->height * 0.5f;
	s.coord.y = -1;
	while (++s.coord.y < fdf->height)
	{
		s.coord.x = -1;
		while (++s.coord.x < fdf->width)
		{
			s.index = s.coord.y * fdf->width + s.coord.x;
			s.angle = ((float)s.coord.x / fdf->width) * 2.0f * M_PI;
			s.height = (float)s.coord.y - (fdf->height / 2.0f);
			if (fabsf(s.height) < s.height_limit)
			{
				s.radius = s.max_radius * (1.0f - fabsf(s.height) / s.height_limit);
				s.radius += fdf->points[s.index] * 0.1f;
				s.shape.x = s.radius * cosf(s.angle);
				s.shape.y = s.height;
				s.shape.z = s.radius * sinf(s.angle);
			}
			else
			{
				s.shape.x = 0.0f;
				s.shape.y = s.height;
				s.shape.z = 0.0f;
			}
			s.sp[0] = s.shape.x;
			s.sp[1] = s.shape.y;
			s.sp[2] = s.shape.z;
			s.sp[3] = 1;
			s.dp = (float *)&fdf->transformed_points[s.index];
			matrix4_dot_product(fdf->transformation_stack.combined, s.sp, s.dp);
		}
	}
}
