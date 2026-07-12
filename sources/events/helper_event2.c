/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_event2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 00:28:06 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 21:33:13 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdio.h>
#include <math.h>

void	setup_event_bindings(void)
{
	setup_movement_bindings();
	setup_control_bindings();
	setup_palette_bindings();
	setup_feature_toggle_bindings();
}

void	handle_key_event(int keycode, unsigned int modifiers, t_app *fdf)
{
	t_event_fn	fn;

	fn = find_event_handler(keycode, modifiers);
	if (fn != NULL)
	{
		fn(fdf, keycode, NULL);
	}
}

void	toggle_effects(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	if (!fdf || !fdf->points || fdf->width <= 0 || fdf->height <= 0)
	{
		ft_printf("Cannot toggle object effects: invalid data\n");
		return ;
	}
	transition_start_object_effects(fdf, false);
	ft_printf("Object effects toggled with H key\n");
}

void	register_event_binding(int keycode, unsigned int modifiers,
		t_event_fn handler)
{
	t_event_handler_table	*table;
	int						mapped_keycode;
	int						mod_idx;

	table = get_event_handler_table();
	mapped_keycode = map_keycode(keycode);
	mod_idx = modifier_index(modifiers);
	if (mapped_keycode >= 0 && mapped_keycode < MAX_KEYCODE)
	{
		table->handler_table[mapped_keycode][mod_idx] = handler;
	}
}

t_event_fn	find_event_handler(int keycode, unsigned int modifiers)
{
	t_event_handler_table	*table;
	int						mapped_keycode;
	int						mod_idx;

	table = get_event_handler_table();
	mapped_keycode = map_keycode(keycode);
	if (mapped_keycode >= 0 && mapped_keycode < MAX_KEYCODE)
	{
		mod_idx = modifier_index(modifiers);
		return (table->handler_table[mapped_keycode][mod_idx]);
	}
	return (NULL);
}
