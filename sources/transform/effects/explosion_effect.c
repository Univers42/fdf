/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explosion_effect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:55:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 18:10:17 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	apply_explosion_to_points(t_app *fdf)
{
	t_object_effects_system	*oe;
	int						i;
	float					t;
	float					distance;
	float					explosion_factor;

	oe = gobjfx(NULL);
	if (!oe->original_points || !fdf->points)
		return ;
	t = oe->time_accumulator;
	explosion_factor = sinf(t * 2.0f) * 0.5f + 0.5f;
	explosion_factor *= oe->intensity;
	i = -1;
	while (++i < oe->total_points)
	{
		if (i >= fdf->width * fdf->height)
			break ;
		distance = sqrtf((float)(i % fdf->width - fdf->width / 2)
				* (i % fdf->width - fdf->width / 2)
				+ (float)(i / fdf->width - fdf->height / 2)
				* (i / fdf->width - fdf->height / 2));
		fdf->points[i] = oe->original_points[i]
			+ distance * explosion_factor * 10.0f;
	}
}

void	apply_vertex_explosion_effect(t_app *fdf)
{
	t_object_effects_system	*oe;

	oe = gobjfx(NULL);
	if (oe->current_effect != OBJ_EFFECT_VERTEX_EXPLOSION)
		return ;
	store_original_object_points(fdf);
	if (!oe->original_points)
		return ;
	apply_explosion_to_points(fdf);
}
