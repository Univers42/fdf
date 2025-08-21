#ifndef WINDOW_H
#define WINDOW_H

#include <mlx.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ft_math.h"

// Forward declarations to avoid circular dependencies - use pointers only
typedef struct s_window t_window;
typedef struct s_layer t_layer;
typedef struct s_point3d t_point3d;
typedef struct s_object t_object;
typedef struct s_window_vtable t_window_vtable;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define WIN_WIDTH 500
#define WIN_HEIGHT 500

// Layer structure for z-depth management
typedef struct s_layer
{
	int z_index;
	t_object **objects;
	size_t object_count;
	size_t object_capacity;
	struct s_layer *next;
} t_layer;

// Window vtable - use pointers for all parameters
typedef struct s_window_vtable
{
	t_window *(*new)(int width, int height, char *title, int bg_color);
	void (*destroy)(t_window *self);
	void (*render)(t_window *self);
	void (*clear)(t_window *self);
	void (*add_object)(t_window *self, t_object *obj, int z_index);
	void (*remove_object)(t_window *self, t_object *obj);
	void (*set_background)(t_window *self, int color);
	void (*resize)(t_window *self, int width, int height);
	int (*handle_events)(t_window *self);
} t_window_vtable;

// Window structure - use pointers to avoid dependencies
typedef struct s_window
{
	t_window_vtable *vtable;

	// MLX components - use pointers
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	char *img_data;
	int bpp;
	int size_line;
	int endian;

	// Window properties
	int width;
	int height;
	char *title;
	int bg_color;
	bool should_close;

	// Layer management - use pointer
	t_layer *layers;

	// Custom data and functions - use pointers
	void *user_data;
	int (*event_handler)(t_window *self, int event, void *data);
	void *input_handler;
} t_window;

// Global vtable instance
extern t_window_vtable g_window_vtable;

// Public API
t_window *window_new(int width, int height, char *title, int bg_color);
void window_destroy(t_window *self);
void window_render(t_window *self);
void window_clear(t_window *self);
void window_add_object(t_window *self, t_object *obj, int z_index);
void window_remove_object(t_window *self, t_object *obj);
void window_set_background(t_window *self, int color);
void window_resize(t_window *self, int width, int height);
int window_handle_events(t_window *self);

// Layer management
t_layer *layer_new(int z_index);
void layer_destroy(t_layer *layer);
void layer_add_object(t_layer *layer, t_object *obj);
void layer_remove_object(t_layer *layer, t_object *obj);

// Utility functions
void window_put_pixel(t_window *self, int x, int y, int color);
int window_get_pixel(t_window *self, int x, int y);

// Drawing utilities
void window_draw_line_simple(t_window *window, int x0, int y0, int x1, int y1, int color);
void window_draw_circle_simple(t_window *window, int cx, int cy, int radius, int color);
void window_draw_rectangle_simple(t_window *window, int x, int y, int width, int height, int color);

// Internal implementation functions
t_window_vtable *get_window_method(void);

// Implementation function declarations
void window_render_impl(t_window *self);
void window_clear_impl(t_window *self);
void window_add_object_impl(t_window *self, t_object *obj, int z_index);
void window_remove_object_impl(t_window *self, t_object *obj);
void window_set_background_impl(t_window *self, int color);
void window_resize_impl(t_window *self, int width, int height);
int window_handle_events_impl(t_window *self);

// tester
void test_basic_drawing(t_window *window);

// Visual test function declaration
int visual_test_run(void);

// Don't include object.h - use forward declarations only
// This breaks the circular dependency

#endif
