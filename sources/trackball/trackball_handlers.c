/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trackball_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:40 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 19:03:57 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>
#include "quaternion.h"

// Local static implementation to resolve linker errors
bool	is_trackball_active(void)
{
	t_trackball_state	*t;

	t = gtrack();
	return (t->active);
}

void trackball_update_rotation(float rq[4], float *p)
{
	t_fpoint2 p1;
	t_fpoint2 p2;

	// p[0], p[1] = start point; p[2], p[3] = end point
	p1.x = p[0];
	p1.y = p[1];
	p2.x = p[2];
	p2.y = p[3];
	trackball_rotate(rq, p1, p2);
}

// Enhanced mouse handlers with trackball support
int	trackball_button_press_handler(int button, int x, int y, t_app *fdf)
{
	int	result;

	result = button_press_handler(button, x, y, fdf);
	if (button == Button2 && fdf->input_state == INPUT_STATE_IDLE)
	{
		trackball_start_rotation(x, y);
		fdf->input_state = INPUT_STATE_ROTATING;
	}
	return (result);
}

int	trackball_button_release_handler(int button, int x, int y, t_app *fdf)
{
	int	result;

	result = button_release_handler(button, x, y, fdf);
	if (button == Button2 && fdf->input_state == INPUT_STATE_ROTATING)
	{
		trackball_end_rotation();
		fdf->input_state = INPUT_STATE_IDLE;
	}
	return (result);
}
