/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_dna.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:35 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/06 21:17:25 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	dna_helix_point(t_meta_shape *s, t_app *fdf)
{
	float	end_factor;

	s->height = (float)s->coord.y - (fdf->height / 2.0f);
	s->phase = (s->coord.x % 2 == 0) ? 0.0f : M_PI;
	s->angle = s->height * 0.1f;
	s->radius_base = fminf(fdf->width, fdf->height) / 6.0f;
	s->radius = s->radius_base * 0.5f + fdf->points[s->index] * 0.2f;
	if (fabsf(s->height) > fdf->height * 0.9f)
	{
		end_factor = (fdf->height * 0.9f - fabsf(s->height)) / (fdf->height * 0.09f);
		if (end_factor < 0.0f)
			end_factor = 0.0f;
		s->radius *= end_factor;
	}
	s->shape.x = s->radius * cosf(s->angle + s->phase);
	s->shape.y = s->height;
	s->shape.z = s->radius * sinf(s->angle + s->phase);
}

void	apply_dna_transformation(t_app *fdf)
{
	t_meta_shape	s;

	s.coord.y = -1;
	while (++s.coord.y < fdf->height)
	{
		s.coord.x = -1;
		while (++s.coord.x < fdf->width)
		{
			s.index = s.coord.y * fdf->width + s.coord.x;
			dna_helix_point(&s, fdf);
			s.sp[0] = s.shape.x;
			s.sp[1] = s.shape.y;
			s.sp[2] = s.shape.z;
			s.sp[3] = 1;
			s.dp = (float *)&fdf->transformed_points[s.index];
			matrix4_dot_product(fdf->transformation_stack.combined, s.sp, s.dp);
		}
	}
}
