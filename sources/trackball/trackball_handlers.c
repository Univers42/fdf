/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trackball_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:40 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:26:41 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>

// Enhanced mouse handlers with trackball support
int trackball_button_press_handler(int button, int x, int y, t_app *fdf)
{
	// Call original handler first
	int result = button_press_handler(button, x, y, fdf);
	
	// Add trackball functionality for middle mouse button
	if (button == Button2 && fdf->input_state == INPUT_STATE_IDLE)
	{
		trackball_start_rotation(x, y);
		fdf->input_state = INPUT_STATE_ROTATING;
	}
	
	return result;
}

int trackball_button_release_handler(int button, int x, int y, t_app *fdf)
{
	// Call original handler first
	int result = button_release_handler(button, x, y, fdf);
	
	// End trackball rotation
	if (button == Button2 && fdf->input_state == INPUT_STATE_ROTATING)
	{
		trackball_end_rotation();
		fdf->input_state = INPUT_STATE_IDLE;
	}
	
	return result;
}

int trackball_motion_handler(int x, int y, t_app *fdf)
{
	// Handle trackball rotation
	if (is_trackball_active() && fdf->input_state == INPUT_STATE_ROTATING)
	{
		trackball_update_rotation(x, y);
		return 0;
	}
	
	// Call original motion handler for other interactions
	return motion_handler(x, y, fdf);
}

int trackball_key_press_handler(int keycode, t_app *fdf)
{
	// Call original handler first
	int result = key_press_handler(keycode, fdf);
	
	// Add 'r' key to reset trackball rotation
	if (keycode == XK_r)
	{
		reset_trackball_rotation();
		printf("Trackball rotation reset\n");
	}
	
	return result;
}
