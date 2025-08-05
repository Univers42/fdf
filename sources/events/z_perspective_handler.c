/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_perspective_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:27:54 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:27:55 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <stdio.h>

static bool g_ctrl_pressed = false;

// Enhanced key press handler with z-perspective control
int z_perspective_key_press_handler(int keycode, t_app *fdf)
{
	// Track Ctrl key state
	if (keycode == XK_Control_L || keycode == XK_Control_R)
	{
		g_ctrl_pressed = true;
		return 0;
	}
	
	// Handle Ctrl + Arrow combinations for z-perspective
	if (g_ctrl_pressed)
	{
		switch (keycode)
		{
			case XK_Up:
				increase_z_perspective(fdf);
				return 0;
			case XK_Down:
				reduce_z_perspective(fdf);
				return 0;
			case XK_r:
			case XK_R:
				reset_z_perspective(fdf);
				// Also reset appropriate rotation system
				if (transition_is_active())
					reset_trackball_rotation();
				return 0;
		}
	}
	
	// Handle number keys for preset perspective modes
	if (keycode >= XK_F1 && keycode <= XK_F5)
	{
		int mode = keycode - XK_F1;
		set_z_perspective_mode(fdf, mode);
		return 0;
	}
	
	// Call original handler for other keys
	return key_press_handler(keycode, fdf);
}

// Key release handler
int z_perspective_key_release_handler(int keycode, t_app *fdf)
{
	// Track Ctrl key release
	if (keycode == XK_Control_L || keycode == XK_Control_R)
	{
		g_ctrl_pressed = false;
		return 0;
	}
	
	(void)fdf; // Unused parameter
	return 0;
}

// Check if ctrl is currently pressed
bool is_ctrl_pressed(void)
{
	return g_ctrl_pressed;
}
