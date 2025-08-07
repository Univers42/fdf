/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spiral_twist_effect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:15 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 23:08:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	apply_twist_to_points(t_app *fdf, float twist_strength)
{
	int		y;
	int		x;
	int		index;
	float	twist_effect;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			twist_effect = sinf((sqrtf(powf(x - fdf->width / 2.0f, 2)
							+ powf(y - fdf->height / 2.0f, 2)) * 0.1f
						+ g_obj_effects.time_accumulator) * twist_strength);
			twist_effect *= 30.0f;
			fdf->points[index] = g_obj_effects.original_points[index]
				+ twist_effect;
			x++;
		}
		y++;
	}
}

void	apply_spiral_twist_effect(t_app *fdf)
{
	float	twist_strength;

	if (!g_obj_effects.original_points)
		return ;
	twist_strength = 2.0f * g_obj_effects.intensity;
	apply_twist_to_points(fdf, twist_strength);
}
