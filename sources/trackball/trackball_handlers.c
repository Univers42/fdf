/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trackball_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:40 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 17:27:29 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>

// Local static implementation to resolve linker errors
bool	is_trackball_active(void)
{
	t_trackball_state	*t;

	t = gtrack();
	return (t->active);
}

void	trackball_update_rotation(int x, int y)
{
	t_trackball_state	*t;
	float				p[4];
	float				rq[4];

	t = gtrack();
	if (!t->active || !t->initialized)
		return ;
	p[0] = (2.0f * t->last_mouse_x - WIN_WIDTH) / WIN_WIDTH;
	p[1] = (WIN_HEIGHT - 2.0f * t->last_mouse_y) / WIN_HEIGHT;
	p[2] = (2.0f * x - WIN_WIDTH) / WIN_WIDTH;
	p[3] = (WIN_HEIGHT - 2.0f * y) / WIN_HEIGHT;
	trackball_rotate(rq, p[0], p[1], p[2], p[3]);
	add_quats(t->last_quat, rq, t->current_quat);
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
