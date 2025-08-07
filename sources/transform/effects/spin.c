/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:12 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 23:03:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	apply_spin_to_points(t_app *fdf)
{
	int		y;
	int		x;
	int		index;
	float	spiral_effect;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			spiral_effect = sinf(sqrtf(powf((float)x / fdf->width, 2)
						+ powf((float)y / fdf->height, 2)) * 8.0f
					+ g_dance.time_accumulator * 5.0f);
			spiral_effect *= 30.0f * g_dance.move_intensity;
			fdf->points[index] = g_dance.original_points[index] + spiral_effect;
			x++;
		}
		y++;
	}
}

void	apply_dance_spin(t_app *fdf)
{
	float	spin_speed;

	spin_speed = 0.15f * g_dance.rhythm_multiplier;
	trans_stack_rotate_y(&fdf->trans_stack, spin_speed);
	trans_stack_rotate_x(&fdf->trans_stack, spin_speed * 0.7f);
	trans_stack_rotate_z(&fdf->trans_stack, spin_speed * 0.3f);
	apply_spin_to_points(fdf);
}
