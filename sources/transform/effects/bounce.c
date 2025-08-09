/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounce.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:34 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 17:23:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	apply_squash_to_points(t_app *fdf, float squash_factor)
{
	t_point2				coord;
	int						index;
	float					dist_factor;
	float					final_squash;
	const t_dance_system	*d = gdance(NULL);

	coord.y = -1;
	while (++coord.y < fdf->height)
	{
		coord.x = -1;
		while (++coord.x < fdf->width)
		{
			index = coord.y * fdf->width + coord.x;
			dist_factor = 1.0f - (sqrtf(powf(coord.x - fdf->width / 2.0f, 2)
						+ powf(coord.y - fdf->height / 2.0f, 2))
					/ sqrtf(powf(fdf->width / 2.0f, 2)
						+ powf(fdf->height / 2.0f, 2)));
			final_squash = squash_factor * (1.0f + dist_factor * 2.0f);
			fdf->points[index] = d->original_points[index] * final_squash;
		}
	}
}

void	apply_dance_bounce(t_app *fdf)
{
	const t_dance_system	*d = gdance(NULL);
	float					bounce_freq;
	float					bounce_height;
	float					bounce_y;
	float					squash_factor;

	bounce_freq = 8.0f * d->rhythm_multiplier;
	bounce_height = 50.0f * d->move_intensity;
	bounce_y = sinf(d->time_accumulator * bounce_freq) * bounce_height;
	squash_factor = 1.0f + (sinf(d->time_accumulator
				* bounce_freq * 2.0f) * 0.8f);
	trans_stack_translate(&fdf->trans_stack, 0, bounce_y * 0.2f, 0);
	apply_squash_to_points(fdf, squash_factor);
}
