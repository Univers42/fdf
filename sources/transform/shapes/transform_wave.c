/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_wave.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:57 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 23:03:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

static void	transform_wave_point(t_app *fdf, t_meta_shape *s,
		float base_radius, float wave_amplitude)
{
	float	norm_x;
	float	norm_y;
	float	wave1;
	float	wave2;
	float	wave3;

	norm_x = (2.0f * s->coord.x / ((float)fdf->width - 1.0f)) - 1.0f;
	norm_y = (2.0f * s->coord.y / ((float)fdf->height - 1.0f)) - 1.0f;
	s->shape.x = norm_x * base_radius;
	s->shape.y = norm_y * base_radius;
	wave1 = sinf(norm_x * 3.0f * M_PI) * cosf(norm_y * 3.0f * M_PI);
	wave2 = sinf(norm_x * 5.0f * M_PI + norm_y * 2.0f * M_PI);
	wave3 = cosf(norm_y * 4.0f * M_PI + norm_x * 2.0f * M_PI);
	s->shape.z = wave_amplitude * (wave1 + wave2 + wave3) / 3.0f
		+ fdf->points[s->index] * 0.1f;
	s->sp[0] = s->shape.x;
	s->sp[1] = s->shape.y;
	s->sp[2] = s->shape.z;
	s->sp[3] = 1;
	s->dp = (float *)&fdf->transformed_points[s->index];
	matrix4_dot_product(fdf->trans_stack.combined, s->sp, s->dp);
}

void	apply_wave_transformation(t_app *fdf)
{
	t_meta_shape	s;
	float			base_radius;
	float			wave_amplitude;

	base_radius = fminf(fdf->width, fdf->height) / 3.0f;
	wave_amplitude = fminf(fdf->width, fdf->height) / 6.0f;
	s.coord.y = -1;
	while (++s.coord.y < fdf->height)
	{
		s.coord.x = -1;
		while (++s.coord.x < fdf->width)
		{
			s.index = s.coord.y * fdf->width + s.coord.x;
			transform_wave_point(fdf, &s, base_radius, wave_amplitude);
		}
	}
}
