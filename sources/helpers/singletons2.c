/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 03:03:38 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:29:44 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_trackball_shape_state	*gstate_tball(void)
{
	static t_trackball_shape_state	g_trackball_state = {
	{0.0f, 0.0f, 0.0f, 1.0f},
	{1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f},
		false
	};

	return (&g_trackball_state);
}

t_trackball_state	*gtrack(void)
{
	static t_trackball_state	s;

	return (&s);
}

t_dance_system *gdance(t_dance_system *set)
{
	static t_dance_system	s = {
		.active = false,
		.current_move = DANCE_NONE,
		.next_move = DANCE_SPIN,
		.time_accumulator = 0.0f,
		.move_intensity = 1.0f,
		.move_frame = 0,
		.hold_frame = 0,
		.transitioning = false,
		.auto_sequence = true,
		.original_points = NULL,
		.initialized = false,
		.total_points = 0,
		.rhythm_multiplier = 1.0f
	};

	if (set)
		s = *set;
	return (&s);
}
