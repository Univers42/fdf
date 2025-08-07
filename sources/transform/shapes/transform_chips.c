/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_chips.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 23:03:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	transform_chip_point(
	t_app *fdf, t_meta_shape *s, float scale, float a
)
{
	float	norm_x;
	float	norm_y;

	s->index = s->coord.y * fdf->width + s->coord.x;
	norm_x = (2.0f * s->coord.x / (fdf->width - 1)) - 1.0f;
	norm_y = (2.0f * s->coord.y / (fdf->height - 1)) - 1.0f;
	s->shape.x = norm_x * scale;
	s->shape.y = norm_y * scale;
	s->shape.z = a * (norm_x * norm_x - norm_y * norm_y) * scale;
	s->shape.z += fdf->points[s->index] * 0.1f;
	s->sp[0] = s->shape.x;
	s->sp[1] = s->shape.y;
	s->sp[2] = s->shape.z;
	s->sp[3] = 1;
	s->dp = (float *)&fdf->transformed_points[s->index];
	matrix4_dot_product(fdf->trans_stack.combined, s->sp, s->dp);
}

void	apply_chips_transformation(t_app *fdf)
{
	t_meta_shape	s;
	float			scale;
	float			a;

	scale = fminf(fdf->width, fdf->height) / 3.0f;
	a = 0.3f;
	s.coord.y = -1;
	while (++s.coord.y < fdf->height)
	{
		s.coord.x = -1;
		while (++s.coord.x < fdf->width)
		{
			transform_chip_point(fdf, &s, scale, a);
		}
	}
}
