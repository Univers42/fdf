/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:13:20 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/02 18:39:07 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

// Public API implementations
t_window *window_new(int width, int height, char *title, int bg_color)
{
    return g_window_vtable.new(width, height, title, bg_color);
}

void window_destroy(t_window *self)
{
    if (self && self->vtable)
        self->vtable->destroy(self);
}

void window_render(t_window *self)
{
    if (self && self->vtable)
        self->vtable->render(self);
}

void window_clear(t_window *self)
{
    if (self && self->vtable)
        self->vtable->clear(self);
}

void window_add_object(t_window *self, t_object *obj, int z_index)
{
    if (self && self->vtable)
        self->vtable->add_object(self, obj, z_index);
}

void window_remove_object(t_window *self, t_object *obj)
{
    if (self && self->vtable)
        self->vtable->remove_object(self, obj);
}

void window_set_background(t_window *self, int color)
{
    if (self && self->vtable)
        self->vtable->set_background(self, color);
}

void window_resize(t_window *self, int width, int height)
{
    if (self && self->vtable)
        self->vtable->resize(self, width, height);
}

int window_handle_events(t_window *self)
{
    if (self && self->vtable)
        return self->vtable->handle_events(self);
    return 0;
}
