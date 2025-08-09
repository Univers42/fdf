/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pulse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:49:47 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:47:31 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	apply_geometric_pulse_effect(t_app *fdf)
{
	const t_object_effects_system *oe = gobjfx(NULL);
	float	pulse;
	int		y, x, index;

	if (!oe->original_points)
		return;
	pulse = 1.0f + 0.3f * sinf(oe->time_accumulator * 3.0f) * oe->intensity;
	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			fdf->points[index] = oe->original_points[index] * pulse;
			++x;
		}
		++y;
	}
}
