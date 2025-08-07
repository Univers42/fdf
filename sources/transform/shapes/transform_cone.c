/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:27 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 17:59:50 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

static void	calc_cone_coords(
	t_app *fdf, t_meta_shape *s, float max_radius, float height_limit
)
{
	int		index;
	float	height;
	float	angle;
	float	radius;

	index = s->coord.y * fdf->width + s->coord.x;
	s->index = index;
	height = (float)s->coord.y - (fdf->height / 2.0f);
	angle = ((float)s->coord.x / fdf->width) * 2.0f * M_PI;
	radius = 0.0f;
	if (fabsf(height) < height_limit)
	{
		radius = max_radius * (1.0f - fabsf(height) / height_limit);
		radius += fdf->points[index] * 0.1f;
		s->shape.x = radius * cosf(angle);
		s->shape.y = height;
		s->shape.z = radius * sinf(angle);
	}
	else
	{
		s->shape.x = 0.0f;
		s->shape.y = height;
		s->shape.z = 0.0f;
	}
}

static void	apply_cone_transform(
	t_app *fdf, t_meta_shape *s
)
{
	s->sp[0] = s->shape.x;
	s->sp[1] = s->shape.y;
	s->sp[2] = s->shape.z;
	s->sp[3] = 1;
	s->dp = (float *)&fdf->transformed_points[s->index];
	matrix4_dot_product(fdf->transformation_stack.combined, s->sp, s->dp);
}

static void	transform_cone_point(
	t_app *fdf, t_meta_shape *s, float max_radius, float height_limit
)
{
	calc_cone_coords(fdf, s, max_radius, height_limit);
	apply_cone_transform(fdf, s);
}

static void	cone_loop(t_app *fdf, float max_radius, float height_limit)
{
	t_meta_shape	s;

	s.coord.y = -1;
	while (++s.coord.y < fdf->height)
	{
		s.coord.x = -1;
		while (++s.coord.x < fdf->width)
		{
			transform_cone_point(fdf, &s, max_radius, height_limit);
		}
	}
}

void	apply_cone_transformation(t_app *fdf)
{
	float	max_radius;
	float	height_limit;

	max_radius = fminf(fdf->width, fdf->height) / 4.0f;
	height_limit = fdf->height * 0.5f;
	cone_loop(fdf, max_radius, height_limit);
}
