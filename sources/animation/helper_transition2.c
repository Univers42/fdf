/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_transition2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:36:02 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 16:14:39 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Updates the transition state and applies transformations.
 *
 * Handles the transition logic, including interpolation
 * during active transitions
 * and applying the current shape when not transitioning.
 *
 * @param fdf Pointer to the main application structure.
 */
void	transition_update(t_app *fdf)
{
	t_transition_state	*st;

	st = gtransition(NULL);
	if (!st->active && st->current_shape == SHAPE_ORIGINAL)
		return ;
	if (st->active && st->frame == 0 && !transition_prepare(fdf))
		return ((void)(st->active = false));
	if (st->active)
	{
		transition_transform(fdf, st->cloud_src, st->cloud_dst,
			ease_in_out((float)st->frame / (float)st->max_frames));
		st->frame++;
		if (st->frame >= st->max_frames)
		{
			st->active = false;
			st->frame = 0;
			st->current_shape = st->target_shape;
		}
	}
	else
		transition_transform(fdf, st->cloud_dst, st->cloud_dst, 0.0f);
}

/**
 * @brief Starts a transition to the next shape.
 *
 * Sets the transition state to active and prepares for
 * transitioning to the next shape.
 *
 * @param to_torus Unused parameter (legacy).
 */
void	transition_start_torus(bool to_torus)
{
	t_transition_state	*st;
	t_shape_type		next;

	(void)to_torus;
	st = gtransition(NULL);
	next = (st->current_shape + 1) % SHAPE_COUNT;
	st->active = true;
	st->frame = 0;
	st->target_shape = next;
}
