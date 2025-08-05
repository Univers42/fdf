/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:02:13 by dmontesd          #+#    #+#             */
/*   Updated: 2025/08/06 01:35:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/keysym.h>
#include <X11/Xlib.h>
#include "mlx.h"
#include "fdf.h"
#include "move_rotate.h"
#include "colors_map.h"
#include "switch_color.h"
#include <math.h>
#include <stdio.h>

// --- Add these lines for global trackball state access ---
typedef struct s_trackball_shape_state {
	float current_rotation[4];
	float rotation_matrix[16];
	bool is_active;
} t_trackball_shape_state;

extern t_trackball_shape_state g_trackball_state;
// --- End addition ---

#define ROTATE_FACTOR 0.03f
#define MOVE_FACTOR   2.0f
#define AUTO_ROTATE_SPEED 0.01f // Slower auto-rotation

static bool g_auto_rotate = false;

// Add mouse tracking variables
static int g_mouse_x = WIN_WIDTH / 2;
static int g_mouse_y = WIN_HEIGHT / 2;
static float g_camera_speed = 5.0f;
static bool g_free_roam_mode = true; // Enable by default

// Function to convert mouse position to world direction
static void get_mouse_direction(float *dir_x, float *dir_y, float *dir_z)
{
	// Convert mouse position to normalized coordinates [-1, 1]
	float norm_x = (2.0f * g_mouse_x / WIN_WIDTH) - 1.0f;
	float norm_y = 1.0f - (2.0f * g_mouse_y / WIN_HEIGHT);
	
	// Calculate direction vector based on mouse position
	*dir_x = norm_x;
	*dir_y = 0.0f; // Keep Y movement separate
	*dir_z = -norm_y; // Z follows mouse Y (inverted for intuitive control)
	
	// Normalize the direction vector
	float length = sqrtf((*dir_x) * (*dir_x) + (*dir_z) * (*dir_z));
	if (length > 0.0f)
	{
		*dir_x /= length;
		*dir_z /= length;
	}
}

// Free-roam movement functions
static void move_in_mouse_direction(t_app *fdf, float speed)
{
	float dir_x, dir_y, dir_z;
	get_mouse_direction(&dir_x, &dir_y, &dir_z);
	
	transformation_stack_translate(&fdf->transformation_stack, 
		dir_x * speed, 0.0f, dir_z * speed);
}

static void move_opposite_mouse_direction(t_app *fdf, float speed)
{
	float dir_x, dir_y, dir_z;
	get_mouse_direction(&dir_x, &dir_y, &dir_z);
	
	transformation_stack_translate(&fdf->transformation_stack, 
		-dir_x * speed, 0.0f, -dir_z * speed);
}

static void strafe_left_from_mouse(t_app *fdf, float speed)
{
	float dir_x, dir_y, dir_z;
	get_mouse_direction(&dir_x, &dir_y, &dir_z);
	
	// Calculate perpendicular vector (strafe left)
	float strafe_x = dir_z;
	float strafe_z = -dir_x;
	
	transformation_stack_translate(&fdf->transformation_stack, 
		strafe_x * speed, 0.0f, strafe_z * speed);
}

static void strafe_right_from_mouse(t_app *fdf, float speed)
{
	float dir_x, dir_y, dir_z;
	get_mouse_direction(&dir_x, &dir_y, &dir_z);
	
	// Calculate perpendicular vector (strafe right)
	float strafe_x = -dir_z;
	float strafe_z = dir_x;
	
	transformation_stack_translate(&fdf->transformation_stack, 
		strafe_x * speed, 0.0f, strafe_z * speed);
}

void	init_mlx_handlers(t_app *f)
{
	// Initialize systems
	init_trackball_system();
	init_z_perspective_control(f);
	
	mlx_hook(f->window, Expose, ExposureMask, fdf_render, f);
	mlx_hook(f->window, DestroyNotify, SubstructureNotifyMask, mlx_loop_end, f->mlx);
	mlx_loop_hook(f->mlx, fdf_render, f);
	
	// Use enhanced handlers with z-perspective control
	mlx_hook(f->window, KeyPress, KeyPressMask, z_perspective_key_press_handler, f);
	mlx_hook(f->window, KeyRelease, KeyReleaseMask, z_perspective_key_release_handler, f);
	mlx_hook(f->window, ButtonPress, ButtonPressMask, trackball_button_press_handler, f);
	mlx_hook(f->window, MotionNotify, Button1MotionMask | Button2MotionMask | Button3MotionMask, trackball_motion_handler, f);
	mlx_hook(f->window, ButtonRelease, ButtonReleaseMask, trackball_button_release_handler, f);
}

// Move the function prototype to the top
void	auto_rotate_update(t_app *fdf);

void	transition_start_torus(bool to_torus);

bool	transition_is_active(void);

// Add function prototypes at top
void toggle_parallax_effect(void);
bool is_parallax_active(void);

static void reset_to_original_map(t_app *fdf)
{
	// Reset transition system to original shape
	transition_cleanup();
	
	// Reset trackball rotation
	reset_trackball_rotation();
	
	// Reset transformation stack to isometric view
	make_transformation_stack(&fdf->transformation_stack);
	transformation_stack_origin(&fdf->transformation_stack,
		-((float)fdf->width / 2), -((float)fdf->height / 2),
		-(float)(fdf->min_z + fdf->max_z) / 2.0f);
	transformation_stack_isometric(&fdf->transformation_stack);
	
	// Reset projection
	t_projection_ctl *projection = &fdf->transformation_stack.projection;
	make_projection_ctl(projection, (float)fdf->width, (float)fdf->height,
		(float)(fdf->max_z - fdf->min_z));
	transformation_stack_translate(&fdf->transformation_stack, 0, 0,
		-projection->box[2] / 2.0f);
	projection_reset_params(projection);
	fdf->transformation_stack.dirty[M_PROJECTION] = true;
	transformation_stack_update(&fdf->transformation_stack);
	center_model(&fdf->transformation_stack, (float)fdf->width,
		(float)fdf->height, (float)(fdf->max_z - fdf->min_z));
	
	// Reset z-perspective
	reset_z_perspective(fdf);
	
	// Reset to default color palette (index 0)
	set_palette_index(0, fdf);
	
	// Reset auto-rotation
	g_auto_rotate = false;
	
	printf("Reset to original map with default settings\n");
}

int	key_press_handler(const int keycode, t_app *fdf)
{
	if (keycode == XK_Escape)
		mlx_loop_end(fdf->mlx);
	if (keycode == XK_p)
	{
		transformation_stack_parallel(&fdf->transformation_stack);
		projection_reset_params(&fdf->transformation_stack.projection);
		fdf->transformation_stack.dirty[M_PROJECTION] = true;
		transformation_stack_update(&fdf->transformation_stack);
		center_model(&fdf->transformation_stack, (float)fdf->width,
			(float)fdf->height, (float)(fdf->max_z - fdf->min_z));
	}
	if (keycode == XK_i)
	{
		transformation_stack_isometric(&fdf->transformation_stack);
		projection_reset_params(&fdf->transformation_stack.projection);
		fdf->transformation_stack.dirty[M_PROJECTION] = true;
		transformation_stack_update(&fdf->transformation_stack);
		center_model(&fdf->transformation_stack, (float)fdf->width,
			(float)fdf->height, (float)(fdf->max_z - fdf->min_z));
	}
	
	// Movement controls (always use matrix transformations)
	if (keycode == XK_w)
		move_forward(fdf, MOVE_FACTOR);
	if (keycode == XK_s)
		move_backward(fdf, MOVE_FACTOR);
	if (keycode == XK_a)
		move_left(fdf, MOVE_FACTOR);
	if (keycode == XK_d)
		move_right(fdf, MOVE_FACTOR);

	// --- Restore manual rotation for shapes ---
	if (!transition_is_active())
	{
		// Matrix rotations for default map
		if (keycode == XK_Up)
			rotate_up(fdf, ROTATE_FACTOR);
		if (keycode == XK_Down)
			rotate_down(fdf, ROTATE_FACTOR);
		if (keycode == XK_Left)
			rotate_left(fdf, ROTATE_FACTOR);
		if (keycode == XK_Right)
			rotate_right(fdf, ROTATE_FACTOR);
	}
	else
	{
		// For shapes: use trackball-style manual rotation with arrow keys
		// Simulate small trackball drags for each arrow key
		float delta = 0.08f; // Adjust for desired sensitivity
		extern void trackball_rotate(float q[4], float p1x, float p1y, float p2x, float p2y);
		extern void quaternion_to_matrix4(float q[4], float m[16]);
		extern void set_trackball_shape_dirty(void); // (optional, if you have such a function)
		bool changed = false;
		if (keycode == XK_Up)
		{
			trackball_rotate(g_trackball_state.current_rotation, 0.0f, 0.0f, 0.0f, delta);
			changed = true;
		}
		if (keycode == XK_Down)
		{
			trackball_rotate(g_trackball_state.current_rotation, 0.0f, 0.0f, 0.0f, -delta);
			changed = true;
		}
		if (keycode == XK_Left)
		{
			trackball_rotate(g_trackball_state.current_rotation, 0.0f, 0.0f, -delta, 0.0f);
			changed = true;
		}
		if (keycode == XK_Right)
		{
			trackball_rotate(g_trackball_state.current_rotation, 0.0f, 0.0f, delta, 0.0f);
			changed = true;
		}
		if (changed)
		{
			quaternion_to_matrix4(g_trackball_state.current_rotation, g_trackball_state.rotation_matrix);
			g_trackball_state.is_active = true;
			// Optionally mark transformation stack dirty for shape
			// set_trackball_shape_dirty();
			return (0);
		}
	}
	// --- End manual shape rotation restore ---

	// Enhanced zoom controls with different speeds
	if (keycode == XK_minus || keycode == XK_KP_Subtract)
	{
		// Normal zoom out
		transformation_stack_zoom(&fdf->transformation_stack, +1);
	}
	if (keycode == XK_plus || keycode == XK_KP_Add)
	{
		// Normal zoom in
		transformation_stack_zoom(&fdf->transformation_stack, -1);
	}
	
	// Add fast zoom controls with Shift modifier
	if (keycode == XK_Page_Up)
	{
		// Fast zoom in (5x speed)
		for (int i = 0; i < 5; i++)
			transformation_stack_zoom(&fdf->transformation_stack, -1);
	}
	if (keycode == XK_Page_Down)
	{
		// Fast zoom out (5x speed)
		for (int i = 0; i < 5; i++)
			transformation_stack_zoom(&fdf->transformation_stack, +1);
	}
	
	// Ultra-fast zoom with Ctrl+Shift
	if (keycode == XK_Home)
	{
		// Ultra zoom in (10x speed)
		for (int i = 0; i < 10; i++)
			transformation_stack_zoom(&fdf->transformation_stack, -1);
	}
	if (keycode == XK_End)
	{
		// Ultra zoom out (10x speed)
		for (int i = 0; i < 10; i++)
			transformation_stack_zoom(&fdf->transformation_stack, +1);
	}

	// Auto-rotation toggle (in-place rotation only)
	if (keycode == XK_space)
		g_auto_rotate = !g_auto_rotate;

	// Shape transformation cycling
	if (keycode == XK_t)
		transition_start_torus(false);

	// Theme switching: keys 1-9
	if (keycode >= XK_1 && keycode <= XK_9)
		set_palette_index(keycode - XK_1, fdf);

	// Effects toggles
	if (keycode == XK_l)
		toggle_parallax_effect();
	if (keycode == XK_g)
		toggle_stars();
	if (keycode == XK_h)
		toggle_shadow_mode();

	// Add reset functionality with 'R' key
	if (keycode == XK_r || keycode == XK_R)
	{
		reset_to_original_map(fdf);
		return (0);
	}

	// Enhanced movement controls - free-roam style
	if (g_free_roam_mode)
	{
		// Mouse-directed movement (like FPS games)
		if (keycode == XK_w)
			move_in_mouse_direction(fdf, g_camera_speed);
		if (keycode == XK_s)
			move_opposite_mouse_direction(fdf, g_camera_speed);
		if (keycode == XK_a)
			strafe_left_from_mouse(fdf, g_camera_speed);
		if (keycode == XK_d)
			strafe_right_from_mouse(fdf, g_camera_speed);
		
		// Vertical movement
		if (keycode == XK_q)
			transformation_stack_translate(&fdf->transformation_stack, 0.0f, g_camera_speed, 0.0f);
		if (keycode == XK_e)
			transformation_stack_translate(&fdf->transformation_stack, 0.0f, -g_camera_speed, 0.0f);
	}
	else
	{
		// Original movement controls
		if (keycode == XK_w)
			move_forward(fdf, MOVE_FACTOR);
		if (keycode == XK_s)
			move_backward(fdf, MOVE_FACTOR);
		if (keycode == XK_a)
			move_left(fdf, MOVE_FACTOR);
		if (keycode == XK_d)
			move_right(fdf, MOVE_FACTOR);
	}

	// Speed controls
	if (keycode == XK_Shift_L || keycode == XK_Shift_R)
		g_camera_speed *= 2.0f; // Sprint mode
	if (keycode == XK_Control_L || keycode == XK_Control_R)
		g_camera_speed *= 0.5f; // Slow mode

	// Add unlimited zoom with mouse wheel multiplier
	if (keycode == XK_minus || keycode == XK_KP_Subtract)
	{
		// Zoom speed based on current zoom level
		for (int i = 0; i < (int)(g_camera_speed / 2); i++)
			transformation_stack_zoom(&fdf->transformation_stack, +1);
	}
	if (keycode == XK_plus || keycode == XK_KP_Add)
	{
		// Zoom speed based on current zoom level
		for (int i = 0; i < (int)(g_camera_speed / 2); i++)
			transformation_stack_zoom(&fdf->transformation_stack, -1);
	}
	
	// Ultra-fast zoom
	if (keycode == XK_Page_Up)
	{
		for (int i = 0; i < (int)(g_camera_speed * 3); i++)
			transformation_stack_zoom(&fdf->transformation_stack, -1);
	}
	if (keycode == XK_Page_Down)
	{
		for (int i = 0; i < (int)(g_camera_speed * 3); i++)
			transformation_stack_zoom(&fdf->transformation_stack, +1);
	}
	
	// Toggle free-roam mode
	if (keycode == XK_Tab)
	{
		g_free_roam_mode = !g_free_roam_mode;
		printf("Free-roam mode %s\n", g_free_roam_mode ? "enabled" : "disabled");
	}

	return (0);
}

int	key_release_handler(int keycode, t_app *fdf)
{
	// Reset camera speed when modifier keys are released
	if (keycode == XK_Shift_L || keycode == XK_Shift_R || 
		keycode == XK_Control_L || keycode == XK_Control_R)
		g_camera_speed = 5.0f; // Reset to default speed
	
	(void)fdf;
	return (0);
}

// Track mouse position for directional movement
int	motion_handler(int x, int y, t_app *fdf)
{
	// Update global mouse position for movement direction
	g_mouse_x = x;
	g_mouse_y = y;
	
	// Handle existing drag operations
	t_projection_ctl	*proj;
	float				ndcx;
	float				ndcy;

	ndcx = ((float) x - (float) fdf->drag_start[0]) / WIN_WIDTH;
	ndcy = ((float) fdf->drag_start[1] - (float) y) / WIN_HEIGHT;
	proj = &fdf->transformation_stack.projection;
	if (fdf->input_state == INPUT_STATE_DRAGGING)
	{
		transformation_stack_pan(&fdf->transformation_stack,
			ndcx * (proj->l - proj->r), ndcy * (proj->b - proj->t));
		fdf->drag_start[0] = x;
		fdf->drag_start[1] = y;
	}
	else if (fdf->input_state == INPUT_STATE_ROTATING)
	{
		transformation_stack_rotate_x(&fdf->transformation_stack,
			ndcy * (proj->b - proj->t) * ROTATE_FACTOR);
		transformation_stack_rotate_y(&fdf->transformation_stack,
			ndcx * (proj->r - proj->l) * ROTATE_FACTOR);
		fdf->drag_start[0] = x;
		fdf->drag_start[1] = y;
	}
	return (0);
}

int	button_press_handler(int button, int x, int y, t_app *fdf)
{
	// Enhanced zoom with variable speed
	if (button == Button4)
	{
		for (int i = 0; i < (int)g_camera_speed; i++)
			transformation_stack_zoom(&fdf->transformation_stack, -1);
	}
	else if (button == Button5)
	{
		for (int i = 0; i < (int)g_camera_speed; i++)
			transformation_stack_zoom(&fdf->transformation_stack, +1);
	}
	else if (button == Button1 && fdf->input_state == INPUT_STATE_IDLE)
	{
		fdf->drag_start[0] = x;
		fdf->drag_start[1] = y;
		fdf->input_state = INPUT_STATE_DRAGGING;
	}
	else if (button == Button3 && fdf->input_state == INPUT_STATE_IDLE)
	{
		fdf->drag_start[0] = x;
		fdf->drag_start[1] = y;
		fdf->input_state = INPUT_STATE_ROTATING;
	}
	return (0);
}

int	button_release_handler(int button, int x, int y, t_app *fdf)
{
	(void) x;
	(void) y;
	if ((button == Button1 || button == Button3)
		&& (fdf->input_state == INPUT_STATE_DRAGGING
			|| fdf->input_state == INPUT_STATE_ROTATING))
		fdf->input_state = INPUT_STATE_IDLE;
	return (0);
}

void	auto_rotate_update(t_app *fdf)
{
	static float rotation_angle = 0.0f;
	
	if (!g_auto_rotate)
		return;
	
	// Smooth, predictable in-place rotation
	const float rotation_speed = 0.01f; // Slower for smooth viewing
	
	rotation_angle += rotation_speed;
	
	// Choose rotation type based on current state
	if (transition_is_active())
	{
		// For transformed shapes: use trackball-style rotation
		apply_auto_trackball_rotation(fdf, rotation_speed);
	}
	else
	{
		// For default map: use matrix rotations
		// Primary Y rotation with subtle X and Z for visual interest
		transformation_stack_rotate_y(&fdf->transformation_stack, rotation_speed);
		
		// Add very subtle oscillation on other axes
		float subtle_x = sinf(rotation_angle * 0.3f) * 0.002f;
		float subtle_z = cosf(rotation_angle * 0.7f) * 0.001f;
		
		transformation_stack_rotate_x(&fdf->transformation_stack, subtle_x);
		transformation_stack_rotate_z(&fdf->transformation_stack, subtle_z);
	}
}

// Add a function to check auto-rotate status
bool is_auto_rotate_active(void)
{
	return g_auto_rotate;
}
