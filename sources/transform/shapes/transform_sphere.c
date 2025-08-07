/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:04:58 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 17:41:50 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	transform_sphere_point(
	t_app *fdf, t_meta_shape *s, float radius
)
{
	s->index = s->coord.y * fdf->width + s->coord.x;
	s->s_vec.u = (2.0f * M_PI * s->coord.x) / fdf->width;
	s->s_vec.v = (M_PI * s->coord.y) / fdf->height;
	s->shape.x = radius * sinf(s->s_vec.v) * cosf(s->s_vec.u);
	s->shape.y = radius * sinf(s->s_vec.v) * sinf(s->s_vec.u);
	s->shape.z = radius * cosf(s->s_vec.v);
	s->shape.z += fdf->points[s->index] * 0.1f;
	s->sp[0] = s->shape.x;
	s->sp[1] = s->shape.y;
	s->sp[2] = s->shape.z;
	s->sp[3] = 1;
	s->dp = (float *)&fdf->transformed_points[s->index];
	matrix4_dot_product(fdf->transformation_stack.combined, s->sp, s->dp);
}

void	apply_sphere_transformation(t_app *fdf, float radius)
{
	t_meta_shape	s;

	if (radius == 0)
		radius = fminf(fdf->width, fdf->height) / 3.0f;
	s.coord.y = -1;
	while (++s.coord.y < fdf->height)
	{
		s.coord.x = -1;
		while (++s.coord.x < fdf->width)
			transform_sphere_point(fdf, &s, radius);
	}
}
