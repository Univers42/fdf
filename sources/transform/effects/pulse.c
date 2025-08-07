/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pulse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:49:47 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 23:08:37 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	apply_geometric_pulse_effect(t_app *fdf)
{
	float	pulse;
	int		y;
	int		x;
	int		index;

	if (!g_obj_effects.original_points)
		return ;
	pulse = 1.0f + 0.3f * sinf(g_obj_effects.time_accumulator * 3.0f)
		* g_obj_effects.intensity;
	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			fdf->points[index] = g_obj_effects.original_points[index] * pulse;
			x++;
		}
		y++;
	}
}
