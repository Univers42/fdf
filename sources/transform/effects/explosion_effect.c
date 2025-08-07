/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explosion_effect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:51:55 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 22:57:55 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	apply_explosion_to_points(t_app *fdf, float strength)
{
	int		y;
	int		x;
	int		index;
	float	norm_dist;
	float	explosion_factor;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			norm_dist = sqrtf(powf(x - fdf->width / 2.0f, 2)
					+ powf(y - fdf->height / 2.0f, 2))
				/ sqrtf(powf(fdf->width / 2.0f, 2)
					+ powf(fdf->height / 2.0f, 2));
			explosion_factor = sinf(g_obj_effects.time_accumulator * 2.0f)
				* norm_dist;
			fdf->points[index] = g_obj_effects.original_points[index]
				+ explosion_factor * strength;
			x++;
		}
		y++;
	}
}

void	apply_vertex_explosion_effect(t_app *fdf)
{
	float	explosion_strength;

	if (!g_obj_effects.original_points)
		return ;
	explosion_strength = 50.0f * g_obj_effects.intensity;
	apply_explosion_to_points(fdf, explosion_strength);
}
