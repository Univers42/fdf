/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_dance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:56:23 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/23 13:57:32 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* helpers extracted to reduce function size */
void	ds_advance_counters(t_dance_system *d)
{
	d->time_accumulator += 0.15f;
	d->move_frame++;
}

bool	ds_should_start_transition(t_dance_system *d)
{
	if (!d->auto_sequence || d->transitioning)
		return (false);
	d->hold_frame++;
	if (d->hold_frame < DANCE_HOLD_FRAMES)
		return (false);
	d->transitioning = true;
	d->hold_frame = 0;
	d->move_frame = 0;
	return (true);
}

int	ds_find_next_move_basic(int current)
{
	int	next;

	next = (current + 1) % DANCE_MOVE_COUNT;
	if (next == DANCE_NONE)
		next = DANCE_SPIN;
	return (next);
}

int	ds_skip_disabled_moves(int start)
{
	void	(**fn_table)(t_app *fdf);
	int		next;
	int		tries;

	fn_table = dance_move_fn();
	next = start;
	tries = 0;
	while (fn_table[next] == NULL && tries < DANCE_MOVE_COUNT)
	{
		next = (next + 1) % DANCE_MOVE_COUNT;
		if (next == DANCE_NONE)
			next = DANCE_SPIN;
		tries++;
	}
	return (next);
}
