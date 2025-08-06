/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_wave.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:57 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/06 21:34:01 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static float	wave_interference(float norm_x, float norm_y, float amplitude)
{
	float	freq1, freq2, freq3;
	float	wave1, wave2, wave3;

	freq1 = 3.0f;
	freq2 = 5.0f;
	freq3 = 7.0f;
	wave1 = sinf(norm_x * freq1 * M_PI) * cosf(norm_y * freq1 * M_PI);
	wave2 = sinf(norm_x * freq2 * M_PI + M_PI/4) * cosf(norm_y * freq2 * M_PI);
	wave3 = sinf(sqrtf(norm_x*norm_x + norm_y*norm_y) * freq3 * M_PI);
	return (amplitude * (0.5f * wave1 + 0.3f * wave2 + 0.2f * wave3));
}

static float	wave_radial(float norm_x, float norm_y, float amplitude)
{
	float	dist_from_center;
	float	radial_wave;

	dist_from_center = sqrtf(norm_x * norm_x + norm_y * norm_y);
	radial_wave = sinf(dist_from_center * 8.0f * M_PI) * expf(-dist_from_center * 2.0f);
	return (amplitude * 0.4f * radial_wave);
}

static void	calc_wave_point(t_meta_shape *s, t_app *fdf)
{
	s->s_vec.u = (2.0f * s->coord.x / (fdf->width - 1)) - 1.0f;
	s->s_vec.v = (2.0f * s->coord.y / (fdf->height - 1)) - 1.0f;
	s->shape.x = s->s_vec.u * s->max_radius;
	s->shape.y = s->s_vec.v * s->max_radius;
	s->shape.z = wave_interference(s->s_vec.u, s->s_vec.v, s->max_radius / 2.0f);
	s->shape.z += wave_radial(s->s_vec.u, s->s_vec.v, s->max_radius / 2.0f);
	s->shape.z += fdf->points[s->index] * 0.1f;
}

void	apply_wave_transformation(t_app *fdf)
{
	t_meta_shape	s;

	s.max_radius = fminf(fdf->width, fdf->height) / 3.0f;
	s.coord.y = -1;
	while (++s.coord.y < fdf->height)
	{
		s.coord.x = -1;
		while (++s.coord.x < fdf->width)
		{
			s.index = s.coord.y * fdf->width + s.coord.x;
			calc_wave_point(&s, fdf);
			s.sp[0] = s.shape.x;
			s.sp[1] = s.shape.y;
			s.sp[2] = s.shape.z;
			s.sp[3] = 1;
			s.dp = (float *)&fdf->transformed_points[s.index];
			matrix4_dot_product(fdf->transformation_stack.combined, s.sp, s.dp);
		}
	}
}
