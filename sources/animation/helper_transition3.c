/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_transition3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:48:58 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 16:48:59 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	transition_is_active(void)
{
	t_transition_state	*st;

	st = gtransition(NULL);
	return (st->active || st->current_shape != SHAPE_ORIGINAL);
}

/* Singleton accessor for transition state */
t_transition_state	*gtransition(t_transition_state *set)
{
	static t_transition_state	instance = {0};
	static bool					initialized = false;

	if (set)
		instance = *set;
	if (!initialized)
	{
		instance.frame = 0;
		instance.max_frames = TRANSITION_FRAMES;
		instance.active = false;
		instance.current_shape = SHAPE_ORIGINAL;
		instance.target_shape = SHAPE_ORIGINAL;
		instance.original_positions = NULL;
		instance.initialized = false;
		initialized = true;
	}
	return (&instance);
}

// Wrapper kept for compatibility with event code
void	transition_start_shape_cycle(t_app *fdf)
{
	(void)fdf;
	transition_start_torus(false);
}

// Wrapper kept for compatibility with render loop
bool	transition_app_is_active(t_app *fdf)
{
	(void)fdf;
	return (transition_is_active());
}

void	transition_cleanup(t_app *fdf)
{
	t_transition_state	*st;

	(void)fdf;
	st = gtransition(NULL);
	if (st->original_positions)
	{
		free(st->original_positions);
		st->original_positions = NULL;
	}
	st->initialized = false;
	st->active = false;
	st->frame = 0;
	st->current_shape = SHAPE_ORIGINAL;
	st->target_shape = SHAPE_ORIGINAL;
}
