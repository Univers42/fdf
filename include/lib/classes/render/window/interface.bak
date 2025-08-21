/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:19:53 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/02 20:48:25 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include <stdio.h>
#include <string.h>

// Forward declarations for implementation functions
extern void window_render_impl(t_window *self);
extern void window_clear_impl(t_window *self);
extern void window_add_object_impl(t_window *self, t_object *obj, int z_index);
extern void window_remove_object_impl(t_window *self, t_object *obj);
extern void window_set_background_impl(t_window *self, int color);
extern void window_resize_impl(t_window *self, int width, int height);
extern int window_handle_events_impl(t_window *self);

// Forward declarations for internal functions
static t_window *window_constructor(int width, int height, char *title, int bg_color);
static void window_destructor(t_window *self);
static void init_variables(t_window *win, int width, int height, char *title, int bg_color);
static bool create_image(t_window *self);
static bool init_srv(t_window *win);

// Global window vtable
t_window_vtable g_window_vtable = {
	.new = window_constructor,
	.destroy = window_destructor,
	.render = window_render_impl,
	.clear = window_clear_impl,
	.add_object = window_add_object_impl,
	.remove_object = window_remove_object_impl,
	.set_background = window_set_background_impl,
	.resize = window_resize_impl,
	.handle_events = window_handle_events_impl};

t_window_vtable *get_window_method(void)
{
	return &g_window_vtable;
}

static void init_variables(t_window *win, int width, int height, char *title, int bg_color)
{
	win->bg_color = bg_color;
	win->height = height;
	win->width = width;
	win->title = strdup(title);
	win->should_close = false;
	win->vtable = &g_window_vtable;
	win->layers = NULL;
	win->user_data = NULL;
	win->event_handler = NULL;
}

static bool create_image(t_window *self)
{
	printf("🖼️  Creating MLX image %dx%d...\n", self->width, self->height);

	self->img_ptr = mlx_new_image(self->mlx_ptr, self->width, self->height);
	if (!self->img_ptr)
	{
		printf("❌ mlx_new_image failed!\n");
		return false;
	}
	printf("✅ mlx_new_image succeeded: %p\n", self->img_ptr);

	self->img_data = mlx_get_data_addr(self->img_ptr, &self->bpp,
									   &self->size_line, &self->endian);
	if (!self->img_data)
	{
		printf("❌ mlx_get_data_addr failed!\n");
		return false;
	}

	printf("✅ mlx_get_data_addr succeeded:\n");
	printf("   img_data=%p\n", self->img_data);
	printf("   bpp=%d\n", self->bpp);
	printf("   size_line=%d\n", self->size_line);
	printf("   endian=%d\n", self->endian);
	printf("   Expected buffer size: %d bytes\n", self->size_line * self->height);

	// Test writing to the first pixel to verify buffer access
	if (self->bpp == 32)
	{
		*(unsigned int *)self->img_data = 0xFF0000; // Red test pixel
		printf("✅ Test write to first pixel succeeded\n");
	}
	else
	{
		printf("⚠️  Unexpected bpp: %d (expected 32)\n", self->bpp);
	}

	return true;
}

static bool init_srv(t_window *win)
{
	win->mlx_ptr = mlx_init();
	if (!win->mlx_ptr)
		return false;

	win->win_ptr = mlx_new_window(win->mlx_ptr, win->width, win->height, win->title);
	if (!win->win_ptr)
		return false;

	if (!create_image(win))
		return false;

	return true;
}

static t_window *window_constructor(int width, int height, char *title, int bg_color)
{
	t_window *window = malloc(sizeof(t_window));
	if (!window)
		return NULL;

	memset(window, 0, sizeof(t_window));

	init_variables(window, width, height, title, bg_color);

	if (!init_srv(window))
	{
		if (window->title)
			free(window->title);
		free(window);
		return NULL;
	}

	return window;
}

static void window_destructor(t_window *self)
{
	t_layer *current;
	t_layer *next;

	if (!self)
		return;

	current = self->layers;
	while (current)
	{
		next = current->next;
		layer_destroy(current);
		current = next;
	}

	if (self->img_ptr)
		mlx_destroy_image(self->mlx_ptr, self->img_ptr);
	if (self->win_ptr)
		mlx_destroy_window(self->mlx_ptr, self->win_ptr);

	free(self->title);
	free(self);
}
