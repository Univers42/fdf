/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dancing_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:27:52 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/23 13:57:18 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "theme.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/* Skip disabled moves (NULL entries in the table) */
void	ds_update_timing_and_sequence(t_dance_system *d)
{
	int	next_move;

	ds_advance_counters(d);
	if (!ds_should_start_transition(d))
		return ;
	next_move = ds_find_next_move_basic(d->current_move);
	next_move = ds_skip_disabled_moves(next_move);
	d->next_move = (t_dance_move)next_move;
}

void	ds_handle_transition(t_dance_system *d)
{
	float	progress;

	if (!d->transitioning)
	{
		d->move_intensity = 1.5f;
		return ;
	}
	progress = (float)d->move_frame / DANCE_TRANSITION_FRAMES;
	if (progress >= 1.0f)
	{
		d->current_move = d->next_move;
		d->transitioning = false;
		d->move_frame = 0;
	}
	else
		d->move_intensity = sinf(progress * M_PI) * 0.5f + 0.5f;
}

void	ds_apply_current_move(t_app *fdf, const t_dance_system *d)
{
	int		idx;
	void	(**fn_table)(t_app *fdf);

	idx = (int)d->current_move;
	fn_table = dance_move_fn();
	if (idx < 0 || idx >= DANCE_MOVE_COUNT)
		return ;
	if (fn_table[idx] != NULL)
		fn_table[idx](fdf);
}

// Store original geometry for dance moves
void	store_original_dance_points(t_app *fdf)
{
	t_dance_system	*d;
	int				i;

	d = gdance(NULL);
	if (d->initialized)
		return ;
	d->total_points = fdf->width * fdf->height;
	if (d->original_points)
		free(d->original_points);
	d->original_points = malloc(sizeof(float) * d->total_points);
	if (!d->original_points)
		return ;
	i = -1;
	while (++i < d->total_points)
		d->original_points[i] = fdf->points[i];
	d->initialized = true;
}

// Main dance system update function
void	dance_system_update(t_app *fdf)
{
	t_dance_system	*d;

	d = gdance(NULL);
	if (!d->active)
		return ;
	store_original_dance_points(fdf);
	if (!d->original_points)
		return ;
	ds_update_timing_and_sequence(d);
	ds_handle_transition(d);
	ds_apply_current_move(fdf, d);
}
