/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 02:23:53 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/30 08:46:39 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

// Singleton accessor for t_app


// Forward declaration for redraw (if not already present)
int redraw(void *param);

// Helper to draw a filled square centered at (x, y) with given size into the image buffer
static void draw_filled_square_to_buffer(t_window *win, int x, int y, int size, uint32_t color)
{
	int bpp, size_line, endian;
	char *buf = win->vtable->get_image_buffer(win, &bpp, &size_line, &endian);
	if (!buf) return;
	int half = size / 2;
	for (int dy = -half; dy <= half; ++dy)
	{
		int py = y + dy;
		if (py < 0 || py >= win->height) continue;
		for (int dx = -half; dx <= half; ++dx)
		{
			int px = x + dx;
			if (px < 0 || px >= win->width) continue;
			int offset = py * size_line + px * (bpp / 8);
			*(uint32_t *)(buf + offset) = color;
		}
	}
}

int redraw(void *param)
{
	t_app *app = (t_app *)param;
	if (!app) { printf("redraw: app is NULL\n"); return 0; }
	if (!app->win) { printf("redraw: app->win is NULL\n"); return 0; }
	if (!app->win->vtable) { printf("redraw: app->win->vtable is NULL\n"); return 0; }
	if (!app->camera) { printf("redraw: app->camera is NULL\n"); return 0; }
	if (!app->camera->vtable) { printf("redraw: app->camera->vtable is NULL\n"); return 0; }

	if (app->win->is_resizing) {
		printf("[DEBUG] redraw: blocked, is_resizing=1\n");
		return (0);
	}

	// Strictly block all logic during resizing
	if (app->win->is_resizing)
		return (0);

	// Only poll and draw if not resizing
	window_poll_resize(app->win);

	int bpp, size_line, endian;
	char *buf = app->win->vtable->get_image_buffer(app->win, &bpp, &size_line, &endian);
	if (buf)
		ft_memset(buf, 0, size_line * app->win->height);

	for (int i = 0; i < NUM_POINTS; ++i)
	{
		t_vec2 coord = app->camera->vtable->project_point(app->camera, app->points[i]);
		t_color col;
		app->points[i]->vtable->get_color(app->points[i], &col); // updated usage
		int size = (int)(app->camera->zoom * 4.0);
		if (size < 1) size = 1;
		draw_filled_square_to_buffer(app->win, coord.x + app->win->draw_offset_x, coord.y + app->win->draw_offset_y, size, col.hex_color);
	}
	app->win->vtable->update_image(app->win);
	return (0);
}

// Add this function to handle window resize events
int on_window_resize(int new_width, int new_height, void *param)
{
	t_app *app = (t_app *)param;
	app->win->vtable->resize(app->win, new_width, new_height);
	redraw(app); // Force redraw after resizing
	return (0);
}

int main(void)
{
	t_app app;
	t_app *app_ptr = &app;

	app_ptr->win = window_new(800, 600, "Camera Demo");
	if (!app_ptr->win) {
		fprintf(stderr, "Failed to create window\n");
		return (1);
	}
	if (!app_ptr->win->mlx) {
		fprintf(stderr, "Failed to initialize MLX\n");
		return (1);
	}
	if (!app_ptr->win->win) {
		fprintf(stderr, "Failed to create MLX window\n");
		return (1);
	}
	if (!app_ptr->win->img) {
		fprintf(stderr, "Failed to create MLX image\n");
		return (1);
	}
	app_ptr->camera = camera_new(CAMERA_ISOMETRIC);
	if (!app_ptr->camera) {
		fprintf(stderr, "Failed to create camera\n");
		return (1);
	}
	t_input_handler *handler = input_handler_new(app_ptr->camera);
	if (!handler) {
		fprintf(stderr, "Failed to create input handler\n");
		return (1);
	}
	for (int i = 0; i < NUM_POINTS; ++i) {
		app_ptr->points[i] = point_new_with_color(100 + i * 100, 100 + i * 50, i * 20, rgb_to_hex(50*i, 100, 200));
		if (!app_ptr->points[i]) {
			fprintf(stderr, "Failed to create point %d\n", i);
			return (1);
		}
	}
	input_handler_register(app_ptr->win, handler);

	// Set the redraw callback and context
	app_ptr->win->redraw_cb = (void (*)(void *))redraw;
	app_ptr->win->redraw_ctx = app_ptr;

	mlx_loop_hook(app_ptr->win->mlx, redraw, app_ptr);
	mlx_loop(app_ptr->win->mlx);
	for (int i = 0; i < NUM_POINTS; ++i)
		point_destroy(app_ptr->points[i]);
	camera_destroy(app_ptr->camera);
	input_handler_destroy(handler);
	app_ptr->win->vtable->destroy(app_ptr->win);
	if (app_ptr->win->mlx) {
		mlx_destroy_display(app_ptr->win->mlx);
		free(app_ptr->win->mlx);
	}
	return 0;
}
