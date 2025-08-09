/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_event.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 00:05:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 02:20:59 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdio.h>
#include <math.h>
#include "theme.h"

t_modifier_state	*gmod_state(t_modifier_state *set)
{
	static t_modifier_state	state = {
		.ctrl_pressed = false,
		.shift_pressed = false,
		.alt_pressed = false
	};

	if (set)
		state = *set;
	return (&state);
}

float	gcamera_speed(float set)
{
	static float	speed = 5.0f;

	if (set > 0)
		speed = set;
	return (speed);
}

void	init_mlx_handlers(t_app *f)
{
	ft_printf("DEBUG: init_mlx_handlers called\n");
	if (!f)
	{
		ft_printf("DEBUG: ERROR - fdf is NULL in init_mlx_handlers\n");
		return ;
	}
	ft_printf("DEBUG: fdf structure exists, continuing...\n");
	init_trackball_system();
	init_z_perspective_control(f);
	setup_event_bindings();
	mlx_hook(f->window, KeyPress, KeyPressMask, key_press_handler, f);
	mlx_hook(f->window, KeyRelease, KeyReleaseMask, key_release_handler, f);
	mlx_hook(f->window, ButtonPress, ButtonPressMask, button_press_handler, f);
	mlx_hook(f->window, ButtonRelease, ButtonReleaseMask,
		button_release_handler, f);
	mlx_hook(f->window, MotionNotify, PointerMotionMask, motion_handler, f);
	ft_printf("DEBUG: Initializing palette system\n");
	init_palette_system(f);
	if (f->points && f->color && f->width > 0 && f->height > 0)
	{
		ft_printf("DEBUG: Applying initial palette\n");
		apply_current_palette(f);
	}
	mlx_loop_hook(f->mlx, fdf_render, f);
	ft_printf("Centralized event system initialized with O(1) access\n");
}

int	key_press_handler(const int keycode, t_app *fdf)
{
	unsigned int		modifiers;
	t_modifier_state	*mod_state;

	mod_state = gmod_state(NULL);
	if (keycode == XK_Control_L || keycode == XK_Control_R)
		mod_state->ctrl_pressed = true;
	else if (keycode == XK_Shift_L || keycode == XK_Shift_R)
		mod_state->shift_pressed = true;
	else if (keycode == XK_Alt_L || keycode == XK_Alt_R)
		mod_state->alt_pressed = true;
	modifiers = 0;
	if (mod_state->ctrl_pressed)
		modifiers |= ControlMask;
	if (mod_state->shift_pressed)
		modifiers |= ShiftMask;
	if (mod_state->alt_pressed)
		modifiers |= Mod1Mask;
	handle_key_event(keycode, modifiers, fdf);
	return (0);
}

int	key_release_handler(int keycode, t_app *fdf)
{
	t_modifier_state	*mod_state;

	(void)fdf;
	mod_state = gmod_state(NULL);
	if (keycode == XK_Control_L || keycode == XK_Control_R)
		mod_state->ctrl_pressed = false;
	else if (keycode == XK_Shift_L || keycode == XK_Shift_R)
		mod_state->shift_pressed = false;
	else if (keycode == XK_Alt_L || keycode == XK_Alt_R)
		mod_state->alt_pressed = false;
	if (keycode == XK_Shift_L || keycode == XK_Shift_R
		|| keycode == XK_Control_L || keycode == XK_Control_R)
		gcamera_speed(5.0f);
	return (0);
}
