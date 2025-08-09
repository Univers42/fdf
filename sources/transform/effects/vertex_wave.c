/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_wave.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:34:42 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:55:29 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	apply_vertex_wave_effect(t_app *fdf)
{
	const t_object_effects_system	*oe = gobjfx(NULL);
	int								y;
	int								x;
	int								idx;
	float							w;

	if (!oe->original_points)
		return ;
	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			idx = y * fdf->width + x;
			w = sinf((float)x * 0.2f + oe->time_accumulator * 2.0f)
				* cosf((float)y * 0.15f + oe->time_accumulator * 1.5f);
			fdf->points[idx] = oe->original_points[idx] + w * 20.0f * oe->intensity;
			++x;
		}
		++y;
	}
}
