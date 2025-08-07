/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_pyramid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:45 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 18:32:36 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	transform_pyramid_point(t_app *fdf, t_meta_shape *s)
{
	float	dist_from_center;

	s->s_vec.u = (2.0f * s->coord.x / (fdf->width - 1)) - 1.0f;
	s->s_vec.v = (2.0f * s->coord.y / (fdf->height - 1)) - 1.0f;
	s->shape.x = s->s_vec.u * s->max_radius / 2.0f;
	s->shape.y = s->s_vec.v * s->max_radius / 2.0f;
	dist_from_center = fmaxf(fabsf(s->s_vec.u), fabsf(s->s_vec.v));
	if (dist_from_center <= 1.0f)
		s->shape.z = s->height_limit * (1.0f - dist_from_center);
	else
		s->shape.z = 0.0f;
	s->shape.z += fdf->points[s->index] * 0.05f;
	s->sp[0] = s->shape.x;
	s->sp[1] = s->shape.y;
	s->sp[2] = s->shape.z;
	s->sp[3] = 1;
	s->dp = (float *)&fdf->transformed_points[s->index];
	matrix4_dot_product(fdf->transformation_stack.combined, s->sp, s->dp);
}

void	apply_pyramid_transformation(t_app *fdf)
{
	t_meta_shape	s;

	s.max_radius = fminf(fdf->width, fdf->height) / 3.0f;
	s.height_limit = s.max_radius;
	s.coord.y = -1;
	while (++s.coord.y < fdf->height)
	{
		s.coord.x = -1;
		while (++s.coord.x < fdf->width)
		{
			s.index = s.coord.y * fdf->width + s.coord.x;
			transform_pyramid_point(fdf, &s);
		}
	}
}
