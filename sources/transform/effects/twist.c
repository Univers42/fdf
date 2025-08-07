/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:04:35 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 23:09:11 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	apply_twist_to_points(t_app *fdf, float speed, float amplitude)
{
	int		y;
	int		x;
	int		index;
	float	twist_factor;
	float	twist_effect;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			twist_factor = sqrtf(powf(x - fdf->width / 2.0f, 2)
					+ powf(y - fdf->height / 2.0f, 2)) * 0.2f
				+ g_dance.time_accumulator * speed * 20.0f;
			twist_effect = sinf(twist_factor) * amplitude;
			twist_effect += cosf(twist_factor * 1.7f
					+ g_dance.time_accumulator * 3.0f) * amplitude * 0.6f;
			fdf->points[index] = g_dance.original_points[index] + twist_effect;
			x++;
		}
		y++;
	}
}

void	apply_dance_twist(t_app *fdf)
{
	float	twist_speed;
	float	twist_amplitude;

	twist_speed = 0.2f * g_dance.rhythm_multiplier;
	twist_amplitude = 60.0f * g_dance.move_intensity;
	trans_stack_rotate_y(&fdf->trans_stack, twist_speed);
	trans_stack_rotate_x(&fdf->trans_stack, twist_speed * 0.8f);
	trans_stack_rotate_z(&fdf->trans_stack, twist_speed * 0.6f);
	apply_twist_to_points(fdf, twist_speed, twist_amplitude);
}
