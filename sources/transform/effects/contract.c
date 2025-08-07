/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contract.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:06:28 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 23:13:22 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

float	calculate_wobble_component(float freq, float multiplier,
								float scale)
{
	float	component;

	component = sinf(g_dance.time_accumulator * freq * multiplier) * scale;
	return (component);
}

static void	apply_expand_to_points(t_app *fdf, float scale_factor)
{
	int		y;
	int		x;
	int		index;
	float	dist_factor;
	float	local_scale;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			dist_factor = sqrtf(powf((x - fdf->width / 2.0f)
						/ (fdf->width / 2.0f), 2)
					+ powf((y - fdf->height / 2.0f)
						/ (fdf->height / 2.0f), 2));
			local_scale = scale_factor * (1.0f + dist_factor * 0.5f);
			fdf->points[index] = g_dance.original_points[index] * local_scale;
			x++;
		}
		y++;
	}
}

void	apply_dance_expand_contract(t_app *fdf)
{
	float	pulse_freq;
	float	scale_amplitude;
	float	scale_factor;
	float	breath_rotation;

	pulse_freq = 6.0f * g_dance.rhythm_multiplier;
	scale_amplitude = 0.8f;
	scale_factor = 1.0f + sinf(g_dance.time_accumulator * pulse_freq)
		* scale_amplitude * g_dance.move_intensity;
	apply_expand_to_points(fdf, scale_factor);
	breath_rotation = sinf(g_dance.time_accumulator * pulse_freq) * 0.05f;
	trans_stack_rotate_y(&fdf->trans_stack, breath_rotation);
	trans_stack_rotate_x(&fdf->trans_stack,
		breath_rotation * 0.7f);
}
