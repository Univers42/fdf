/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_heart.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:40 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 18:30:56 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

static float	calc_heart_lower_point(float norm_x, float norm_y)
{
	float	point_factor;

	point_factor = 1.0f + norm_y;
	if (point_factor > 0.0f && fabsf(norm_x) < point_factor * 0.8f)
		return (0.2f * point_factor);
	return (0.0f);
}

static float	get_heart_norm_x(t_meta_shape *s, t_app *fdf)
{
	return ((2.0f * s->coord.x / (fdf->width - 1)) - 1.0f);
}

static float	get_heart_norm_y(t_meta_shape *s, t_app *fdf)
{
	return (-((2.0f * s->coord.y / (fdf->height - 1)) - 1.0f));
}

static void	calc_heart_coords(t_app *fdf, t_meta_shape *s, float heart_scale)
{
	float	norm_x;
	float	norm_y;
	float	heart_z;

	s->index = s->coord.y * fdf->width + s->coord.x;
	norm_x = get_heart_norm_x(s, fdf);
	norm_y = get_heart_norm_y(s, fdf);
	s->shape.x = norm_x * heart_scale;
	s->shape.y = norm_y * heart_scale;
	if (norm_y > 0.0f)
		heart_z = calc_heart_upper_lobes(norm_x, norm_y);
	else
		heart_z = calc_heart_lower_point(norm_x, norm_y);
	s->shape.z = heart_z * heart_scale + fdf->points[s->index] * 0.02f;
	s->sp[0] = s->shape.x;
	s->sp[1] = s->shape.y;
	s->sp[2] = s->shape.z;
	s->sp[3] = 1;
	s->dp = (float *)&fdf->transformed_points[s->index];
	matrix4_dot_product(fdf->transformation_stack.combined, s->sp, s->dp);
}

void	apply_heart_transformation(t_app *fdf)
{
	t_meta_shape	s;
	float			heart_scale;

	heart_scale = fminf(fdf->width, fdf->height) / 4.0f;
	s.coord.y = -1;
	while (++s.coord.y < fdf->height)
	{
		s.coord.x = -1;
		while (++s.coord.x < fdf->width)
		{
			calc_heart_coords(fdf, &s, heart_scale);
		}
	}
}
