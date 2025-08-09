/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:12 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:25:10 by dlesieur         ###   ########.fr       */
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
	const t_dance_system	*d = gdance(NULL);

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			spiral_effect = sinf(sqrtf(powf((float)x / fdf->width, 2)
						+ powf((float)y / fdf->height, 2)) * 8.0f
					+ d->time_accumulator * 5.0f);
			spiral_effect *= 30.0f * d->move_intensity;
			fdf->points[index] = d->original_points[index] + spiral_effect;
			x++;
		}
		y++;
	}
}

void	apply_dance_spin(t_app *fdf)
{
	const t_dance_system	*d = gdance(NULL);
	float	spin_speed;

	spin_speed = 0.15f * d->rhythm_multiplier;
	trans_stack_rotate_y(&fdf->trans_stack, spin_speed);
	trans_stack_rotate_x(&fdf->trans_stack, spin_speed * 0.7f);
	trans_stack_rotate_z(&fdf->trans_stack, spin_speed * 0.3f);
	apply_spin_to_points(fdf);
}
