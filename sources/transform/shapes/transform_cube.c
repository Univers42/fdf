/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_cube.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:31 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 18:15:15 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	calc_cube_face_coords(t_meta_shape *s)
{
	s->s_face.face = s->index / s->s_face.tot_point;
	if (s->s_face.face >= 6)
		s->s_face.face = 5;
	s->s_loc.idx = s->index % s->s_face.tot_point;
	s->s_loc.x = s->s_loc.idx % s->s_face.width;
	s->s_loc.y = s->s_loc.idx / s->s_face.width;
	s->s_vec.u = (s->s_loc.x / (float)(s->s_face.width - 1)) * 2.0f - 1.0f;
	s->s_vec.v = (s->s_loc.y / (float)(s->s_face.height - 1)) * 2.0f - 1.0f;
}

static void	calc_cube_coords(t_app *fdf, t_meta_shape *s)
{
	calc_cube_face_coords(s);
	if (s->s_face.face <= 1)
		apply_cube_face_0_1(s, fdf);
	else if (s->s_face.face <= 3)
		apply_cube_face_2_3(s, fdf);
	else
		apply_cube_face_4_5(s, fdf);
}

static void	apply_cube_transform(t_app *fdf, t_meta_shape *s)
{
	s->sp[0] = s->shape.x;
	s->sp[1] = s->shape.y;
	s->sp[2] = s->shape.z;
	s->sp[3] = 1;
	s->dp = (float *)&fdf->transformed_points[s->index];
	matrix4_dot_product(fdf->transformation_stack.combined, s->sp, s->dp);
}

static void	transform_cube_point(t_app *fdf, t_meta_shape *s)
{
	s->index = s->coord.y * fdf->width + s->coord.x;
	calc_cube_coords(fdf, s);
	apply_cube_transform(fdf, s);
}

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
			transform_cube_point(fdf, &s);
		}
	}
}
