/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contract.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:06:28 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 17:33:17 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

float	calculate_wobble_component(float freq, float multiplier, float scale)
{
	const t_dance_system	*d = gdance(NULL);
	float					component;

	component = sinf(d->time_accumulator * freq * multiplier) * scale;
	return (component);
}

static void	apply_expand_to_points(t_app *fdf, float scale_factor)
{
	t_point2				coord;
	int						index;
	float					dist_factor;
	float					local_scale;
	const t_dance_system	*d = gdance(NULL);

	coord.y = -1;
	while (coord.y < fdf->height)
	{
		coord.x = 0;
		while (coord.x < fdf->width)
		{
			index = coord.y * fdf->width + coord.x;
			dist_factor = sqrtf(powf((coord.x - fdf->width / 2.0f)
						/ (fdf->width / 2.0f), 2)
					+ powf((coord.y - fdf->height / 2.0f)
						/ (fdf->height / 2.0f), 2));
			local_scale = scale_factor * (1.0f + dist_factor * 0.5f);
			fdf->points[index] = d->original_points[index] * local_scale;
		}
	}
}

void	apply_dance_expand_contract(t_app *fdf)
{
	const t_dance_system	*d = gdance(NULL);
	float					pulse_freq;
	float					scale_amplitude;
	float					scale_factor;
	float					breath_rotation;

	pulse_freq = 6.0f * d->rhythm_multiplier;
	scale_amplitude = 0.8f;
	scale_factor = 1.0f + sinf(d->time_accumulator * pulse_freq)
		* scale_amplitude * d->move_intensity;
	apply_expand_to_points(fdf, scale_factor);
	breath_rotation = sinf(d->time_accumulator * pulse_freq) * 0.05f;
	trans_stack_rotate_y(&fdf->trans_stack, breath_rotation);
	trans_stack_rotate_x(&fdf->trans_stack, breath_rotation * 0.7f);
}
