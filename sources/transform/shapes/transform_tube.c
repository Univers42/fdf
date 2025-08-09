/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_tube.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:53 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 18:44:54 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"
#include "ft_math.h"

static void	set_tube_wall(t_meta_shape *s, float angle, float radius,
	int height)
{
	int	height_half;

	height_half = height / 2;
	s->s_shape.x = radius * cosf(angle);
	s->s_shape.y = (float)s->s_coord.y - height_half;
	s->s_shape.z = radius * sinf(angle);
}

static void	calc_tube_cap_vars(t_app *fdf, t_meta_shape *s, float *vars)
{
	float		center_x;
	t_point2	d;
	float		grid_radius;
	float		max_grid_radius;
	float		cap_ratio;

	center_x = fdf->width / 2.0f;
	d.x = s->s_coord.x - center_x;
	if ((float)s->s_coord.y - (fdf->height / 2) < 0)
		d.y = s->s_coord.y - 0;
	else
		d.y = s->s_coord.y - (fdf->height - 1);
	grid_radius = sqrtf(d.x * d.x + d.y * d.y);
	max_grid_radius = fdf->width / 2.0f;
	cap_ratio = grid_radius / max_grid_radius;
	vars[0] = cap_ratio;
}

static void	update_pos(t_meta_shape *s, t_app *fdf)
{
	s->sp[0] = s->s_shape.x;
	s->sp[1] = s->s_shape.y;
	s->sp[2] = s->s_shape.z;
	s->sp[3] = 1;
	s->dp = (float *)&fdf->transformed_points[s->index];
}

static void	calc_tube_point(t_app *fdf, t_meta_shape *s, float max_radius)
{
	float	angle;
	float	radius;
	float	height;
	float	height_limit;
	float	cap_vars[1];

	s->index = s->s_coord.y * fdf->width + s->s_coord.x;
	angle = get_tube_angle(s->s_coord.x, fdf->width);
	radius = get_tube_radius(fdf, s, max_radius);
	height = (float)s->s_coord.y - (fdf->height / 2.0f);
	height_limit = fdf->height * 0.5f;
	if (fabsf(height) >= height_limit * 0.95f)
	{
		calc_tube_cap_vars(fdf, s, cap_vars);
		s->s_shape.x = cap_vars[0] * radius * cosf(angle);
		s->s_shape.y = height;
		s->s_shape.z = cap_vars[0] * radius * sinf(angle);
	}
	else
		set_tube_wall(s, angle, radius, fdf->height);
	s->s_shape.z += fdf->points[s->index] * 0.05f;
	update_pos(s, fdf);
	matrix4_dot_product(fdf->trans_stack.combined, s->sp, s->dp);
}

void	apply_tube_transformation(t_app *fdf)
{
	t_meta_shape	s;
	float			max_radius;

	max_radius = fminf(fdf->width, fdf->height) / 4.0f;
	s.s_coord.y = -1;
	while (++s.s_coord.y < fdf->height)
	{
		s.s_coord.x = -1;
		while (++s.s_coord.x < fdf->width)
		{
			calc_tube_point(fdf, &s, max_radius);
		}
	}
}
