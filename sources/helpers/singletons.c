/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:40:23 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 14:40:57 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_z_perspective	gzperspective(t_z_perspective *set)
{
	static t_z_perspective	g_z_control = {
		.scale_factor = 1.0f,
		.original_max_z = 0.0f,
		.original_min_z = 0.0f,
		.initialized = false,
		.original_z_values = NULL,
		.total_points = 0
	};

	if (set)
		g_z_control = *set;
	return (g_z_control);
}

t_core_handlers_state	*get_core_handlers_state(void)
{
	static t_core_handlers_state	instance = {0};

	if (!instance.initialized)
	{
		instance.auto_rotate = false;
		instance.mouse_x = WIN_WIDTH / 2;
		instance.mouse_y = WIN_HEIGHT / 2;
		instance.camera_speed = 5.0f;
		instance.free_roam_mode = true;
		instance.initialized = true;
	}
	return (&instance);
}

t_keycode_map	*gkeycode(void)
{
	static t_keycode_map	map[] = {
	{65307, 1000},
	{65362, 1001},
	{65364, 1002},
	{65361, 1003},
	{65363, 1004},
	{65451, 1005},
	{65453, 1006},
	{4097, 1007},
	{4098, 1008},
	{4099, 1009},
	{0, 0}
	};

	return (map);
}

int	map_keycode(int keycode)
{
	int				i;
	t_keycode_map	*mappings;

	if (keycode >= 0 && keycode < 1000)
		return (keycode);
	mappings = gkeycode();
	i = 0;
	while (mappings[i].x11_keycode != 0)
	{
		if (mappings[i].x11_keycode == keycode)
			return (mappings[i].mapped_keycode);
		i++;
	}
	return (999);
}

t_event_handler_table	*get_event_handler_table(void)
{
	static t_event_handler_table	instance = {0};
	int								i;
	int								j;

	if (!instance.initialized)
	{
		i = 0;
		while (i < MAX_KEYCODE)
		{
			j = 0;
			while (j < MODIFIER_COMBO_COUNT)
			{
				instance.handler_table[i][j] = NULL;
				j++;
			}
			i++;
		}
		instance.initialized = true;
	}
	return (&instance);
}

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
		.target_type = PARTICLE_NONE,
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
