/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_wave.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:34:42 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 23:13:04 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static float	calculate_wave_effect(float norm_x, float norm_y)
{
	float	wave1;
	float	wave2;
	float	wave3;

	wave1 = sinf((norm_x * 8.0f + g_obj_effects.time_accumulator) * M_PI);
	wave2 = sinf((norm_y * 6.0f + g_obj_effects.time_accumulator * 0.7f)
			* M_PI);
	wave3 = sinf(((norm_x + norm_y) * 5.0f + g_obj_effects.time_accumulator
				* 1.2f) * M_PI);
	return ((wave1 + wave2 + wave3) / 3.0f);
}

static void	apply_wave_to_points(t_app *fdf, float wave_amplitude)
{
	int		y;
	int		x;
	int		index;
	float	wave_effect;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			wave_effect = calculate_wave_effect((float)x / fdf->width,
					(float)y / fdf->height);
			fdf->points[index] = g_obj_effects.original_points[index]
				+ wave_effect * wave_amplitude;
			x++;
		}
		y++;
	}
}

void	apply_vertex_wave_effect(t_app *fdf)
{
	float	wave_amplitude;

	if (!g_obj_effects.original_points)
		return ;
	wave_amplitude = 20.0f * g_obj_effects.intensity;
	apply_wave_to_points(fdf, wave_amplitude);
}
