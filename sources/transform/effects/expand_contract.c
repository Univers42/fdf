/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_contract.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:40 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 22:57:59 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	apply_height_oscillation_effect(t_app *fdf)
{
	int		y;
	int		x;
	int		index;
	float	oscillation;

	if (!g_obj_effects.original_points)
		return ;
	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			oscillation = sinf(g_obj_effects.time_accumulator * 3.0f
					+ (g_obj_effects.original_points[index] / 100.0f)) * 15.0f;
			fdf->points[index] = g_obj_effects.original_points[index]
				+ oscillation * g_obj_effects.intensity;
			x++;
		}
		y++;
	}
}
