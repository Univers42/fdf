/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inline_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:24:37 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 18:54:54 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

int	get_dna_index(t_app *fdf, t_meta_shape *s)
{
	return (s->coord.y * fdf->width + s->coord.x);
}

float	get_dna_norm_y(t_app *fdf, t_meta_shape *s)
{
	return ((2.0f * s->coord.y / (float)fdf->height) - 1.0f);
}

float	calc_heart_upper_lobes(float norm_x, float norm_y)
{
	float	dist1;
	float	dist2;

	dist1 = sqrtf((norm_x + 0.5f) * (norm_x + 0.5f)
			+ (norm_y - 0.3f) * (norm_y - 0.3f));
	dist2 = sqrtf((norm_x - 0.5f) * (norm_x - 0.5f)
			+ (norm_y - 0.3f) * (norm_y - 0.3f));
	if (dist1 < 0.6f || dist2 < 0.6f)
		return (0.3f);
	return (0.0f);
}

float	get_tube_angle(int x, int width)
{
	return (((float)x / (float)width) * 2.0f * M_PI);
}

float	get_tube_radius(t_app *fdf, t_meta_shape *s, float max_radius)
{
	return (max_radius + fdf->points[s->index] * 0.3f);
}
