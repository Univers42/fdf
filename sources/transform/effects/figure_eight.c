/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure_eight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:23:02 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// forward decl for accessor
t_dance_system *gdance(t_dance_system *set);

static void	apply_distortion_to_points(t_app *fdf, float t)
{
	int		y;
	int		x;
	int		index;
	float	distortion;
	const t_dance_system *d = gdance(NULL);

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			distortion = sinf(t + ((float)x / fdf->width) * M_PI * 2.0f)
				* cosf(t * 1.5f + ((float)y / fdf->height) * M_PI * 3.0f);
			distortion *= 25.0f * d->move_intensity;
			fdf->points[index] = d->original_points[index] + distortion;
			x++;
		}
		y++;
	}
}

void	apply_dance_figure_eight(t_app *fdf)
{
	const t_dance_system	*d = gdance(NULL);
	float					orbit_freq;
	float					orbit_size;
	float					t;

	orbit_freq = 2.5f * d->rhythm_multiplier;
	orbit_size = 40.0f * d->move_intensity;
	t = d->time_accumulator * orbit_freq;
	trans_stack_translate(&fdf->trans_stack,
		sinf(t) * orbit_size * 0.05f,
		sinf(t * 2.0f) * orbit_size * 0.8f * 0.05f,
		cosf(t * 1.3f) * orbit_size * 0.6f * 0.05f);
	trans_stack_rotate_x(&fdf->trans_stack,
		sinf(t * 2.2f) * 0.08f);
	trans_stack_rotate_y(&fdf->trans_stack,
		cosf(t * 1.8f) * 0.1f);
	trans_stack_rotate_z(&fdf->trans_stack,
		sinf(t * 3.1f) * 0.06f);
	apply_distortion_to_points(fdf, t);
}
