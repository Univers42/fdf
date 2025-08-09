/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_dna.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:25:35 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 18:41:26 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

static float	get_dna_phase(t_meta_shape *s)
{
	if (s->s_coord.x % 2 == 0)
		return (0.0f);
	return (M_PI);
}

static float	get_dna_radius(float radius_base, float z, float norm_y)
{
	float	radius;
	float	end_factor;

	radius = radius_base * 0.5f + z * 0.2f;
	end_factor = 1.0f - fabsf(norm_y);
	if (end_factor < 0.2f)
		end_factor = 0.2f;
	return (radius * end_factor);
}

static void	transform_dna_point(t_app *fdf, t_meta_shape *s, float radius_base)
{
	int		index;
	float	norm_y;
	float	twist_angle;
	float	phase;
	float	radius;

	index = get_dna_index(fdf, s);
	s->index = index;
	norm_y = get_dna_norm_y(fdf, s);
	twist_angle = norm_y * 4.0f * M_PI;
	phase = get_dna_phase(s);
	radius = get_dna_radius(radius_base, fdf->points[index], norm_y);
	s->s_shape.x = radius * cosf(twist_angle + phase);
	s->s_shape.y = norm_y * fdf->height * 0.4f;
	s->s_shape.z = radius * sinf(twist_angle + phase);
	s->s_shape.z += fdf->points[index] * 0.05f;
	s->sp[0] = s->s_shape.x;
	s->sp[1] = s->s_shape.y;
	s->sp[2] = s->s_shape.z;
	s->sp[3] = 1;
	s->dp = (float *)&fdf->transformed_points[index];
	matrix4_dot_product(fdf->trans_stack.combined, s->sp, s->dp);
}

void	apply_dna_transformation(t_app *fdf)
{
	t_meta_shape	s;
	float			radius_base;

	radius_base = fminf(fdf->width, fdf->height) / 6.0f;
	s.s_coord.y = -1;
	while (++s.s_coord.y < fdf->height)
	{
		s.s_coord.x = -1;
		while (++s.s_coord.x < fdf->width)
		{
			transform_dna_point(fdf, &s, radius_base);
		}
	}
}
