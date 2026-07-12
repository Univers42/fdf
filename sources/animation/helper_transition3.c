/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_transition3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:48:58 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 16:13:51 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Checks if a transition is currently active or if a shape is applied.
 *
 * Returns true if a transition is in progress or if the current shape
 * is not the original.
 *
 * @return True if transition is active or shape is applied, false otherwise.
 */
bool	transition_is_active(void)
{
	t_transition_state	*st;

	st = gtransition(NULL);
	return (st->active || st->current_shape != SHAPE_ORIGINAL);
}

/**
 * @brief Singleton accessor for the transition state.
 *
 * Provides access to the global transition state instance.
 * Initializes it on first access.
 *
 * @param set Pointer to a transition state to set (optional, can be NULL).
 * @return Pointer to the global transition state instance.
 */
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
		instance.cloud_src = NULL;
		instance.cloud_dst = NULL;
		initialized = true;
	}
	return (&instance);
}

/**
 * @brief Starts a shape cycle transition.
 *
 * Wrapper function for compatibility with event code. Initiates a
 * transition to the next shape.
 *
 * @param fdf Pointer to the main application structure (unused).
 */
void	transition_start_shape_cycle(t_app *fdf)
{
	(void)fdf;
	transition_start_torus(false);
}

/**
 * @brief Checks if transition is active for the application.
 *
 * Wrapper function for compatibility with render loop.
 * Returns the active status.
 *
 * @param fdf Pointer to the main application structure (unused).
 * @return True if transition is active, false otherwise.
 */
bool	transition_app_is_active(t_app *fdf)
{
	(void)fdf;
	return (transition_is_active());
}

/**
 * @brief Cleans up the transition state.
 *
 * Frees allocated memory and resets the transition state to default values.
 *
 * @param fdf Pointer to the main application structure (unused).
 */
void	transition_cleanup(t_app *fdf)
{
	t_transition_state	*st;

	(void)fdf;
	st = gtransition(NULL);
	free(st->cloud_src);
	free(st->cloud_dst);
	st->cloud_src = NULL;
	st->cloud_dst = NULL;
	st->active = false;
	st->frame = 0;
	st->current_shape = SHAPE_ORIGINAL;
	st->target_shape = SHAPE_ORIGINAL;
}
