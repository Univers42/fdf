/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 02:19:25 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/06 05:01:24 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>
#include <stdio.h>
#include "mlx.h"

// Move the model forward (along Y axis)
void	move_forward(t_app *fdf, float amount)
{
	transformation_stack_translate(&fdf->transformation_stack, 0, -amount, 0);
	fdf->transformation_stack.dirty[M_TB] = true;
}

// Move the model backward (along Y axis)
void	move_backward(t_app *fdf, float amount)
{
	transformation_stack_translate(&fdf->transformation_stack, 0, amount, 0);
	fdf->transformation_stack.dirty[M_TB] = true;
}

// Move the model left (along X axis) - internal helper
static void	move_left_internal(t_app *fdf, float amount)
{
	transformation_stack_translate(&fdf->transformation_stack, -amount, 0, 0);
	fdf->transformation_stack.dirty[M_TB] = true;
}

// Move the model right (along X axis) - internal helper
static void	move_right_internal(t_app *fdf, float amount)
{
	transformation_stack_translate(&fdf->transformation_stack, amount, 0, 0);
	fdf->transformation_stack.dirty[M_TB] = true;
}

// Rotate the model up (around X axis)
void	rotate_up(t_app *fdf, float angle)
{
	transformation_stack_rotate_x(&fdf->transformation_stack, -angle);
	fdf->transformation_stack.dirty[M_ROTATION_X] = true;
}

// Rotate the model down (around X axis)
void	rotate_down(t_app *fdf, float angle)
{
	transformation_stack_rotate_x(&fdf->transformation_stack, angle);
	fdf->transformation_stack.dirty[M_ROTATION_X] = true;
}

// Rotate the model left (around Y axis)
void	rotate_left(t_app *fdf, float angle)
{
	transformation_stack_rotate_y(&fdf->transformation_stack, -angle);
	fdf->transformation_stack.dirty[M_ROTATION_Y] = true;
}

// Rotate the model right (around Y axis)
void	rotate_right(t_app *fdf, float angle)
{
	transformation_stack_rotate_y(&fdf->transformation_stack, angle);
	fdf->transformation_stack.dirty[M_ROTATION_Y] = true;
}

// Movement handlers with proper amounts
void move_up(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	printf("BEFORE: tx=%.2f, ty=%.2f, tz=%.2f\n", 
		   fdf->transformation_stack.tx, fdf->transformation_stack.ty, fdf->transformation_stack.tz);
	
	move_forward(fdf, 5.0f);  // Larger amount to see change
	transformation_stack_update(&fdf->transformation_stack);
	
	printf("AFTER: tx=%.2f, ty=%.2f, tz=%.2f\n", 
		   fdf->transformation_stack.tx, fdf->transformation_stack.ty, fdf->transformation_stack.tz);
	printf("Matrix [3]=%.2f, [7]=%.2f, [11]=%.2f\n",
		   fdf->transformation_stack.matrices[M_TB][3],
		   fdf->transformation_stack.matrices[M_TB][7],
		   fdf->transformation_stack.matrices[M_TB][11]);
}

void move_down(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	move_backward(fdf, 5.0f);
	transformation_stack_update(&fdf->transformation_stack);
}

void move_left(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	move_left_internal(fdf, 5.0f);
	transformation_stack_update(&fdf->transformation_stack);
}

void move_right(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	move_right_internal(fdf, 5.0f);
	transformation_stack_update(&fdf->transformation_stack);
}

// Add rotation event handlers for arrow keys with proper amounts
void rotate_up_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	printf("ROTATE: Before rx=%.4f\n", fdf->transformation_stack.rx);
	
	rotate_up(fdf, 0.1f);  // Larger rotation to see change
	transformation_stack_update(&fdf->transformation_stack);
	
	printf("ROTATE: After rx=%.4f\n", fdf->transformation_stack.rx);
}

void rotate_down_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	rotate_down(fdf, 0.1f);
	transformation_stack_update(&fdf->transformation_stack);
}

void rotate_left_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	rotate_left(fdf, 0.1f);
	transformation_stack_update(&fdf->transformation_stack);
}

void rotate_right_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	rotate_right(fdf, 0.1f);
	transformation_stack_update(&fdf->transformation_stack);
}

// Zoom handlers
void zoom_in(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	transformation_stack_zoom(&fdf->transformation_stack, -1);
}

void zoom_out(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	transformation_stack_zoom(&fdf->transformation_stack, +1);
}

// Projection handlers
void projection_iso(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	transformation_stack_isometric(&fdf->transformation_stack);
	projection_reset_params(&fdf->transformation_stack.projection);
	fdf->transformation_stack.dirty[M_PROJECTION] = true;
	transformation_stack_update(&fdf->transformation_stack);
	center_model(&fdf->transformation_stack, (float)fdf->width,
		(float)fdf->height, (float)(fdf->max_z - fdf->min_z));
}

void projection_fly(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	transformation_stack_parallel(&fdf->transformation_stack);
	projection_reset_params(&fdf->transformation_stack.projection);
	fdf->transformation_stack.dirty[M_PROJECTION] = true;
	transformation_stack_update(&fdf->transformation_stack);
	center_model(&fdf->transformation_stack, (float)fdf->width,
		(float)fdf->height, (float)(fdf->max_z - fdf->min_z));
}

// Shape transformation with circular buffer
void ch_shape(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data; (void)fdf;
	transition_start_torus(false); // This cycles through shapes
	printf("Shape transformation activated\n");
}

// Particle system handler
void ch_particules(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data; (void)fdf;
	transition_start_particles(false); // This cycles through particle effects
	printf("Particle system activated\n");
}

// Z-perspective control with keycode awareness
void z_perspective_ctrl(t_app *fdf, int keycode, void *data)
{
	(void)data;
	
	printf("Z-perspective control triggered with keycode: %d\n", keycode);
	
	switch (keycode)
	{
		case XK_Up:
		case XK_equal:
		case XK_plus:
			increase_z_perspective(fdf);
			printf("Z-perspective increased\n");
			break;
		case XK_Down:
		case XK_underscore:
		case XK_minus:
			reduce_z_perspective(fdf);
			printf("Z-perspective reduced\n");
			break;
		default:
			printf("Unknown z-perspective control keycode: %d\n", keycode);
			break;
	}
}

// System controls
void reset_state(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	
	// Reset transition system
	transition_cleanup();
	
	// Reset particle system
	particles_cleanup();
	
	// Reset trackball rotation
	reset_trackball_rotation();
	
	// Reset transformation stack
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
	
	// Reset to default color palette
	extern void set_palette_index(int idx, t_app *fdf);
	set_palette_index(0, fdf);
	
	printf("All systems reset to default state\n");
}

void exit_prog(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	printf("Goodbye!\n");
	mlx_loop_end(fdf->mlx);
}

// Mouse handlers (placeholder for mouse events)
void mouse_right(t_app *fdf, int keycode, void *data)
{
	(void)fdf; (void)keycode; (void)data;
	printf("Right mouse button event\n");
}

void mouse_left(t_app *fdf, int keycode, void *data)
{
	(void)fdf; (void)keycode; (void)data;
	printf("Left mouse button event\n");
}

void scroll_mouse(t_app *fdf, int keycode, void *data)
{
	(void)fdf; (void)keycode; (void)data;
	printf("Mouse scroll event\n");
}

// Alias function for project_iso (duplicate removed)
void project_iso(t_app *fdf, int keycode, void *data)
{
	projection_iso(fdf, keycode, data);
}

// Reference to the global auto-rotate state
extern bool g_auto_rotate;

void    auto_rotate(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data; (void)fdf;
	extern bool g_auto_rotate;
	g_auto_rotate = !g_auto_rotate;
	printf("Auto-rotation %s\n", g_auto_rotate ? "ON" : "OFF");
}

// Color palette handlers for keys 1-9
void palette_1_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	set_palette_index(0, fdf);
	printf("Color Palette 1: Planet/Ocean theme\n");
}

void palette_2_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	set_palette_index(1, fdf);
	printf("Color Palette 2: Default theme\n");
}

void palette_3_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	set_palette_index(2, fdf);
	printf("Color Palette 3: Gamma Random V2\n");
}

void palette_4_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	set_palette_index(3, fdf);
	printf("Color Palette 4: Vibrant/Rainbow\n");
}

void palette_5_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	set_palette_index(4, fdf);
	printf("Color Palette 5: Grayscale\n");
}

void palette_6_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	set_palette_index(5, fdf);
	printf("Color Palette 6: Sunset\n");
}

void palette_7_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	set_palette_index(6, fdf);
	printf("Color Palette 7: Matrix/Neon Green\n");
}

void palette_8_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	set_palette_index(7, fdf);
	printf("Color Palette 8: Fire/Lava\n");
}

void palette_9_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode; (void)data;
	set_palette_index(8, fdf);
	printf("Color Palette 9: Ice/Arctic\n");
}