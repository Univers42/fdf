/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spiral_twist_effect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:15 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 17:16:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	apply_twist_to_points(t_app *fdf, float twist_strength)
{
	const t_object_effects_system	*oe = gobjfx(NULL);
	int								y;
	int								x;
	int								index;
	float							twist_effect;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			twist_effect = sinf((sqrtf(powf(x - fdf->width / 2.0f, 2)
							+ powf(y - fdf->height / 2.0f, 2)) * 0.1f
						+ oe->time_accumulator) * twist_strength);
			twist_effect *= 30.0f;
			fdf->points[index] = oe->original_points[index]
				+ twist_effect;
			x++;
		}
		y++;
	}
}

void	apply_spiral_twist_effect(t_app *fdf)
{
	const t_object_effects_system	*oe = gobjfx(NULL);
	float							twist_strength;

	if (!oe->original_points)
		return ;
	twist_strength = 0.5f + 0.5f * sinf(oe->time_accumulator * 1.5f);
	twist_strength *= oe->intensity;
	apply_twist_to_points(fdf, twist_strength);
}
