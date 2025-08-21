/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mehod.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:15:02 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/02 18:41:56 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include <stdio.h>
#include <string.h>

// Forward declarations for vtable functions
extern void window_destructor(t_window *self);
extern void window_render_impl(t_window *self);
extern void window_clear_impl(t_window *self);
extern void window_add_object_impl(t_window *self, t_object *obj, int z_index);
extern void window_remove_object_impl(t_window *self, t_object *obj);
extern void window_set_background_impl(t_window *self, int color);
extern void window_resize_impl(t_window *self, int width, int height);
extern int window_handle_events_impl(t_window *self);

t_window_vtable *get_window_method(void)
{
	static t_window_vtable method = {
		.destroy = window_destructor,
		.render = window_render_impl,
		.clear = window_clear_impl,
		.add_object = window_add_object_impl,
		.remove_object = window_remove_object_impl,
		.set_background = window_set_background_impl,
		.resize = window_resize_impl,
		.handle_events = window_handle_events_impl,
	};
	return &method;
}
