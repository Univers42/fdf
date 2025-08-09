/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wave_motion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:27 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 17:07:14 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	apply_wave_to_points(t_app *fdf, float amp, float freq)
{
	int						y;
	int						x;
	int						index;
	float					total_wave;
	const t_dance_system	*d = gdance(NULL);

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			total_wave = sinf(d->time_accumulator * freq * 4.0f
					+ (((float)x / fdf->width) + ((float)y / fdf->height))
					* M_PI * 4.0f) * amp;
			total_wave += sinf(d->time_accumulator * freq * 2.5f
					+ ((float)x / fdf->width) * M_PI * 6.0f) * amp * 0.7f;
			total_wave += cosf(d->time_accumulator * freq * 3.2f
					+ ((float)y / fdf->height) * M_PI * 5.0f) * amp * 0.5f;
			fdf->points[index] = d->original_points[index] + total_wave;
			x++;
		}
		y++;
	}
}

void	apply_dance_wave_motion(t_app *fdf)
{
	const t_dance_system	*d = gdance(NULL);
	float					wave_amplitude;
	float					wave_freq;
	float					move_x;
	float					move_z;

	wave_amplitude = 40.0f * d->move_intensity;
	wave_freq = 3.0f * d->rhythm_multiplier;
	move_x = sinf(d->time_accumulator * wave_freq) * 25.0f;
	move_z = sinf(d->time_accumulator * wave_freq * 2.0f) * 15.0f;
	trans_stack_translate(&fdf->trans_stack, move_x * 0.1f,
		0, move_z * 0.1f);
	apply_wave_to_points(fdf, wave_amplitude, wave_freq);
}
