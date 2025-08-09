/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_contract.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:40 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 17:18:14 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	apply_height_oscillation_effect(t_app *fdf)
{
	const t_object_effects_system	*oe = gobjfx(NULL);
	int								y;
	int								x;
	int								index;
	float							oscillation;

	if (!oe->original_points)
		return ;
	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			oscillation = sinf(oe->time_accumulator * 3.0f
					+ (oe->original_points[index] / 100.0f)) * 15.0f;
			fdf->points[index] = oe->original_points[index]
				+ oscillation * oe->intensity;
			++x;
		}
		++y;
	}
}
