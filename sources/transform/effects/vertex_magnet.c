/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_magnet.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:18 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:51:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	apply_magnet_to_points(t_app *fdf, float m1[2], float m2[2])
{
	const t_object_effects_system	*oe = gobjfx(NULL);
	int		y;
	int		x;
	int		index;
	float	dist1;
	float	dist2;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			dist1 = sqrtf(powf(x - m1[0], 2) + powf(y - m1[1], 2)) + 1.0f;
			dist2 = sqrtf(powf(x - m2[0], 2) + powf(y - m2[1], 2)) + 1.0f;
			fdf->points[index] = oe->original_points[index]
				+ ((500.0f / (dist1 * dist1)) + (-300.0f / (dist2 * dist2)))
				* oe->intensity;
			x++;
		}
		y++;
	}
}

void	apply_vertex_magnet_effect(t_app *fdf)
{
	const t_object_effects_system	*oe = gobjfx(NULL);
	float	magnet1[2];
	float	magnet2[2];

	if (!oe->original_points)
		return ;
	magnet1[0] = (sinf(oe->time_accumulator * 0.8f) + 1.0f)
		* fdf->width * 0.5f;
	magnet1[1] = (cosf(oe->time_accumulator * 0.6f) + 1.0f)
		* fdf->height * 0.5f;
	magnet2[0] = (sinf(oe->time_accumulator * 1.2f + M_PI) + 1.0f)
		* fdf->width * 0.5f;
	magnet2[1] = (cosf(oe->time_accumulator * 0.9f + M_PI) + 1.0f)
		* fdf->height * 0.5f;
	apply_magnet_to_points(fdf, magnet1, magnet2);
}
