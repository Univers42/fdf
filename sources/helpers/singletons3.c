/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:01:12 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/23 18:01:25 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_texture_system	*gtexture(t_texture_system *set)
{
	static t_texture_system	s = {
		.current_texture = TEXTURE_NONE,
		.active = false,
		.time_accumulator = 0.0f,
		.scale_factor = 1.0f,
		.initialized = false,
		.original_colors = NULL,
		.total_points = 0,
		.animation_speed = 1.0f
	};

	if (set)
		s = *set;
	return (&s);
}

t_dynamic_bg_system	*gdynbg(t_dynamic_bg_system *set)
{
	static t_dynamic_bg_system	s = {
		.current_bg = DYNAMIC_BG_STATIC,
		.active = false,
		.time_accumulator = 0.0f,
		.intensity = 1.0f,
		.initialized = false,
		.bg_buffer = NULL,
		.animation_speed = 1.0f,
		.frame_counter = 0
	};

	if (set)
		s = *set;
	return (&s);
}

t_particle_transition	*gparticles(t_particle_transition *set)
{
	static t_particle_transition	s = {
		.frame = 0,
		.max_frames = PARTICLE_TRANSITION_FRAMES,
		.active = false,
		.current_type = PARTICLE_NONE,
		.target_type = PARTICLE_NONE,		// PAFJKSAFJDSAL
		// particles array zero-initialized
		.initialized = false,
		.time_accumulator = 0.0f
	};

	if (set)
		s = *set;
	return (&s);
}

t_object_effects_system	*gobjfx(t_object_effects_system *set)
{
	static t_object_effects_system	s = {
		.current_effect = OBJ_EFFECT_NONE,
		.active = false,
		.time_accumulator = 0.0f,
		.intensity = 1.0f,
		.initialized = false,
		.original_points = NULL,
		.total_points = 0
	};

	if (set)
		s = *set;
	return (&s);
}
