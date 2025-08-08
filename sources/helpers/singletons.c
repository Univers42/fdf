/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:40:23 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 17:38:00 by dlesieur         ###   ########.fr       */
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
