/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_toro.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:49 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 18:44:54 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Helper to compute torus coordinates and apply transformation
static void	transform_torus_point(
	t_app *fdf, t_meta_shape *s, float major_radius, float minor_radius
)
{
	s->index = s->s_coord.y * fdf->width + s->s_coord.x;
	s->s_vec.u = (2.0f * M_PI * s->s_coord.x) / fdf->width;
	s->s_vec.v = (2.0f * M_PI * s->s_coord.y) / fdf->height;
	s->s_shape.x = (major_radius + minor_radius * cosf(s->s_vec.v))
		* cosf(s->s_vec.u);
	s->s_shape.y = (major_radius + minor_radius * cosf(s->s_vec.v))
		* sinf(s->s_vec.u);
	s->s_shape.z = minor_radius * sinf(s->s_vec.v);
	s->s_shape.z += fdf->points[s->index] * 0.1f;
	s->sp[0] = s->s_shape.x;
	s->sp[1] = s->s_shape.y;
	s->sp[2] = s->s_shape.z;
	s->sp[3] = 1;
	s->dp = (float *)&fdf->transformed_points[s->index];
	matrix4_dot_product(fdf->trans_stack.combined, s->sp, s->dp);
}

void	apply_torus_transformation(t_app *fdf,
									float major_radius,
									float minor_radius)
{
	t_meta_shape	s;

	if (major_radius == 0 || minor_radius == 0)
	{
		s.max_radius = fminf(fdf->width, fdf->height) / 3.0f;
		major_radius = s.max_radius;
		minor_radius = major_radius / 4.0f;
	}
	s.s_coord.y = -1;
	while (++s.s_coord.y < fdf->height)
	{
		s.s_coord.x = -1;
		while (++s.s_coord.x < fdf->width)
			transform_torus_point(fdf, &s, major_radius, minor_radius);
	}
}
