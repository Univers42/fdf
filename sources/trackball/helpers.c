/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:27:14 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 19:33:45 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

int	trackball_motion_handler(int x, int y, t_app *fdf)
{
	t_trackball_shape_state	*state;
	float					p[4];

	state = gstate_tball();
	p[0] = (float)fdf->drag_start[0];
	p[1] = (float)fdf->drag_start[1];
	p[2] = (float)x;
	p[3] = (float)y;
	trackball_update_rotation(state->current_rotation, p);
	fdf->drag_start[0] = x;
	fdf->drag_start[1] = y;
	return (0);
}

int	trackball_key_press_handler(int keycode, t_app *fdf)
{
	int	result;

	result = key_press_handler(keycode, fdf);
	if (keycode == XK_r)
	{
		reset_trackball_rotation();
		ft_printf("Trackball rotation reset\n");
	}
	return (result);
}

void	reset_trackball_rotation(void)
{
	t_trackball_shape_state	*st;
	int						i;

	init_trackball_system();
	st = gstate_tball();
	st->current_rotation[0] = 0.0f;
	st->current_rotation[1] = 0.0f;
	st->current_rotation[2] = 0.0f;
	st->current_rotation[3] = 1.0f;
	i = 0;
	while (i < 16)
	{
		st->rotation_matrix[i] = 0.0f;
		i++;
	}
	st->rotation_matrix[0] = 1.0f;
	st->rotation_matrix[5] = 1.0f;
	st->rotation_matrix[10] = 1.0f;
	st->rotation_matrix[15] = 1.0f;
	st->is_active = false;
}

void	trackball_start_rotation(int mx, int my)
{
	t_trackball_state	*t;
	int					i;

	t = gtrack();
	if (!t->initialized)
		init_trackball_system();
	t->active = true;
	t->last_mouse_x = mx;
	t->last_mouse_y = my;
	i = 0;
	while (i < 4)
	{
		t->last_quat[i] = t->current_quat[i];
		i++;
	}
}

void	trackball_end_rotation(void)
{
	t_trackball_state	*t;

	t = gtrack();
	t->active = false;
}
