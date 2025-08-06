/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_cube.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:31 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/06 21:04:15 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	apply_cube_transformation(t_app *fdf)
{
	t_meta_shape	s;

	s.max_radius = fminf(fdf->width, fdf->height) / 4.0f;
	s.total_points = fdf->width * fdf->height;
	s.s_face.tot_point = s.total_points / 6;
	s.s_face.width = fdf->width / 3;
	s.s_face.height = fdf->height / 2;
	if (s.s_face.width == 0)
		s.s_face.width = 1;
	if (s.s_face.height == 0)
		s.s_face.height = 1;
	s.coord.y = -1;
	while (++s.coord.y < fdf->height)
	{
		s.coord.x = -1;
		while (++s.coord.x < fdf->width)
		{
			s.index = s.coord.y * fdf->width + s.coord.x;
			s.s_face.face = s.index / s.s_face.tot_point;
			if (s.s_face.face >= 6)
				s.s_face.face = 5;
			s.s_loc.idx = s.index % s.s_face.tot_point;
			s.s_loc.x = s.s_loc.idx % s.s_face.width;
			s.s_loc.y = s.s_loc.idx / s.s_face.width;
			s.s_vec.u = (s.s_loc.x / (float)(s.s_face.width - 1)) * 2.0f - 1.0f;
			s.s_vec.v = (s.s_loc.y / (float)(s.s_face.height - 1)) * 2.0f - 1.0f;
			switch (s.s_face.face)
			{
				case 0:
					s.shape.x = s.s_vec.u * s.max_radius;
					s.shape.y = s.s_vec.v * s.max_radius;
					s.shape.z = s.max_radius + fdf->points[s.index] * 0.05f;
					break;
				case 1:
					s.shape.x = -s.s_vec.u * s.max_radius;
					s.shape.y = s.s_vec.v * s.max_radius;
					s.shape.z = -s.max_radius + fdf->points[s.index] * 0.05f;
					break;
				case 2:
					s.shape.x = s.max_radius + fdf->points[s.index] * 0.05f;
					s.shape.y = s.s_vec.v * s.max_radius;
					s.shape.z = -s.s_vec.u * s.max_radius;
					break;
				case 3:
					s.shape.x = -s.max_radius + fdf->points[s.index] * 0.05f;
					s.shape.y = s.s_vec.v * s.max_radius;
					s.shape.z = s.s_vec.u * s.max_radius;
					break;
				case 4:
					s.shape.x = s.s_vec.u * s.max_radius;
					s.shape.y = s.max_radius + fdf->points[s.index] * 0.05f;
					s.shape.z = -s.s_vec.v * s.max_radius;
					break;
				case 5:
				default:
					s.shape.x = s.s_vec.u * s.max_radius;
					s.shape.y = -s.max_radius + fdf->points[s.index] * 0.05f;
					s.shape.z = s.s_vec.v * s.max_radius;
					break;
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
