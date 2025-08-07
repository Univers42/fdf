/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:02:13 by dmontesd          #+#    #+#             */
/*   Updated: 2025/08/07 23:03:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/keysym.h>
#include <X11/Xlib.h>
#include "mlx.h"
#include "fdf.h"
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

// Core handlers state singleton
typedef struct s_core_handlers_state {
	bool	auto_rotate;
	int		mouse_x;
	int		mouse_y;
	float	camera_speed;
	bool	free_roam_mode;
	bool	initialized;
} t_core_handlers_state;

static t_core_handlers_state *get_core_handlers_state(void)
{
	static t_core_handlers_state instance = {0};
	
	if (!instance.initialized)
	{
		instance.auto_rotate = false;
		instance.mouse_x = WIN_WIDTH / 2;
		instance.mouse_y = WIN_HEIGHT / 2;
		instance.camera_speed = 5.0f;
		instance.free_roam_mode = true;
		instance.initialized = true;
	}
	return &instance;
}

bool g_auto_rotate = false;

static float g_camera_speed = 5.0f;




void	init_mlx_handlers(t_app *f)
{
	// Initialize the event system
	event_system_init(f);
	
	// Initialize subsystems
	init_trackball_system();
	init_z_perspective_control(f);
	
	// Setup centralized event bindings
	setup_event_bindings();
	
	// Set up MLX event hooks
	mlx_hook(f->window, KeyPress, KeyPressMask, key_press_handler, f);
	mlx_hook(f->window, KeyRelease, KeyReleaseMask, key_release_handler, f);
	mlx_hook(f->window, ButtonPress, ButtonPressMask, button_press_handler, f);
	mlx_hook(f->window, ButtonRelease, ButtonReleaseMask, button_release_handler, f);
	mlx_hook(f->window, MotionNotify, PointerMotionMask, motion_handler, f);
	mlx_loop_hook(f->mlx, fdf_render, f);
	
	printf("Centralized event system initialized with O(1) access\n");
}

// Move the function prototype to the top
void	auto_rotate_update(t_app *fdf);

void	transition_start_torus(bool to_torus);

bool	transition_is_active(void);

// Add function prototypes at top
void toggle_parallax_effect(void);
bool is_parallax_active(void);


// Global modifier state tracking
static struct {
	bool ctrl_pressed;
	bool shift_pressed;
	bool alt_pressed;
} g_modifier_state = {false, false, false};

int	key_press_handler(const int keycode, t_app *fdf)
{
	// Track modifier keys
	if (keycode == XK_Control_L || keycode == XK_Control_R)
	{
		g_modifier_state.ctrl_pressed = true;
		return 0;
	}
	if (keycode == XK_Shift_L || keycode == XK_Shift_R)
	{
		g_modifier_state.shift_pressed = true;
		return 0;
	}
	if (keycode == XK_Alt_L || keycode == XK_Alt_R)
	{
		g_modifier_state.alt_pressed = true;
		return 0;
	}
	
	// Build modifier mask manually
	unsigned int modifiers = 0;
	if (g_modifier_state.ctrl_pressed) modifiers |= ControlMask;
	if (g_modifier_state.shift_pressed) modifiers |= ShiftMask;
	if (g_modifier_state.alt_pressed) modifiers |= Mod1Mask;
	
	// Use the event system with detected modifiers
	handle_key_event(keycode, modifiers, fdf);
	
	return (0);
}

int	key_release_handler(int keycode, t_app *fdf)
{
	t_core_handlers_state *state = get_core_handlers_state();
	
	// Track modifier key releases
	if (keycode == XK_Control_L || keycode == XK_Control_R)
	{
		g_modifier_state.ctrl_pressed = false;
		return 0;
	}
	if (keycode == XK_Shift_L || keycode == XK_Shift_R)
	{
		g_modifier_state.shift_pressed = false;
		return 0;
	}
	if (keycode == XK_Alt_L || keycode == XK_Alt_R)
	{
		g_modifier_state.alt_pressed = false;
		return 0;
	}
	
	// Reset camera speed when modifier keys are released
	if (keycode == XK_Shift_L || keycode == XK_Shift_R || 
		keycode == XK_Control_L || keycode == XK_Control_R)
		state->camera_speed = 5.0f; // Reset to default speed
	
	(void)fdf;
	return (0);
}

// Track mouse position for directional movement
int	motion_handler(int x, int y, t_app *fdf)
{
	t_core_handlers_state *state = get_core_handlers_state();
	
	// Update global mouse position for movement direction
	state->mouse_x = x;
	state->mouse_y = y;
	
	// Handle existing drag operations
	t_projection_ctl	*proj;
	float				ndcx;
	float				ndcy;

	ndcx = ((float) x - (float) fdf->drag_start[0]) / WIN_WIDTH;
	ndcy = ((float) fdf->drag_start[1] - (float) y) / WIN_HEIGHT;
	proj = &fdf->trans_stack.projection;
	if (fdf->input_state == INPUT_STATE_DRAGGING)
	{
		trans_stack_pan(&fdf->trans_stack,
			ndcx * (proj->l - proj->r), ndcy * (proj->b - proj->t));
		fdf->drag_start[0] = x;
		fdf->drag_start[1] = y;
	}
	else if (fdf->input_state == INPUT_STATE_ROTATING)
	{
		trans_stack_rotate_x(&fdf->trans_stack,
			ndcy * (proj->b - proj->t) * ROTATE_FACTOR);
		trans_stack_rotate_y(&fdf->trans_stack,
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
			trans_stack_zoom(&fdf->trans_stack, -1);
	}
	else if (button == Button5)
	{
		for (int i = 0; i < (int)g_camera_speed; i++)
			trans_stack_zoom(&fdf->trans_stack, +1);
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
	
	// Smooth, predictable rotation speed
	const float rotation_speed = 0.008f; // Slightly slower for better viewing
	
	rotation_angle += rotation_speed;
	
	// Apply consistent rotation for both shapes and default map
	if (transition_is_active())
	{
		// For transformed shapes: apply rotation to the transformation matrix
		// This affects how the shapes are transformed, not just the final points
		trans_stack_rotate_y(&fdf->trans_stack, rotation_speed);
		
		// Add subtle multi-axis rotation for visual interest
		float subtle_x = sinf(rotation_angle * 0.3f) * 0.002f;
		float subtle_z = cosf(rotation_angle * 0.7f) * 0.001f;
		
		trans_stack_rotate_x(&fdf->trans_stack, subtle_x);
		trans_stack_rotate_z(&fdf->trans_stack, subtle_z);
	}
	else
	{
		// For default map: use the same matrix rotations
		trans_stack_rotate_y(&fdf->trans_stack, rotation_speed);
		
		// Add very subtle oscillation on other axes
		float subtle_x = sinf(rotation_angle * 0.3f) * 0.002f;
		float subtle_z = cosf(rotation_angle * 0.7f) * 0.001f;
		
		trans_stack_rotate_x(&fdf->trans_stack, subtle_x);
		trans_stack_rotate_z(&fdf->trans_stack, subtle_z);
	}
}

// Add a function to check auto-rotate status
bool is_auto_rotate_active(void)
{
	return g_auto_rotate;
}
