/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:27:14 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 20:22:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

int	trackball_motion_handler(int x, int y, t_app *fdf)
{
	if (is_trackball_active() && fdf->input_state == INPUT_STATE_ROTATING)
		return (trackball_update_rotation(x, y), 0);
	return (motion_handler(x, y, fdf));
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
