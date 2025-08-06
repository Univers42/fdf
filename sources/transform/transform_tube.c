/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_tube.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:53 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/06 21:29:28 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	tube_wall(t_meta_shape *s, t_app *fdf)
{
	s->shape.x = s->radius * cosf(s->angle);
	s->shape.y = s->height;
	s->shape.z = s->radius * sinf(s->angle);
	(void)fdf;
}

static void	tube_cap(t_meta_shape *s, float center_x, float center_y, float max_grid_radius)
{
	float	dx = s->coord.x - center_x;
	float	dy = (s->coord.y < center_y) ? (s->coord.y - 0) : (s->coord.y - (center_y * 2 - 1));
	float	grid_radius = sqrtf(dx * dx + dy * dy);

	if (grid_radius <= max_grid_radius)
	{
		float cap_ratio = grid_radius / max_grid_radius;
		float cap_radius = cap_ratio * s->radius;
		s->shape.x = cap_radius * cosf(s->angle);
		s->shape.y = s->height;
		s->shape.z = cap_radius * sinf(s->angle);
	}
	else
	{
		s->shape.x = 0.0f;
		s->shape.y = s->height;
		s->shape.z = 0.0f;
	}
}

static void	calc_tube_point(t_meta_shape *s, t_app *fdf, float center_x, float center_y, float max_grid_radius)
{
	s->angle = ((float)s->coord.x / fdf->width) * 2.0f * M_PI;
	s->radius = s->max_radius + fdf->points[s->index] * 0.3f;
	s->height = (float)s->coord.y - (fdf->height / 2.0f);

	if (fabsf(s->height) >= s->height_limit * 0.95f)
		tube_cap(s, center_x, center_y, max_grid_radius);
	else
		tube_wall(s, fdf);
}

void	apply_tube_transformation(t_app *fdf)
{
	t_meta_shape	s;
	float			center_x;
	float			center_y;
	float			max_grid_radius;

	s.max_radius = fminf(fdf->width, fdf->height) / 4.0f;
	s.height_limit = fdf->height * 0.5f;
	center_x = fdf->width / 2.0f;
	center_y = fdf->height / 2.0f;
	max_grid_radius = fdf->width / 2.0f;
	s.coord.y = -1;
	while (++s.coord.y < fdf->height)
	{
		s.coord.x = -1;
		while (++s.coord.x < fdf->width)
		{
			s.index = s.coord.y * fdf->width + s.coord.x;
			calc_tube_point(&s, fdf, center_x, center_y, max_grid_radius);
			s.sp[0] = s.shape.x;
			s.sp[1] = s.shape.y;
			s.sp[2] = s.shape.z;
			s.sp[3] = 1;
			s.dp = (float *)&fdf->transformed_points[s.index];
			matrix4_dot_product(fdf->transformation_stack.combined, s.sp, s.dp);
		}
	}
}
