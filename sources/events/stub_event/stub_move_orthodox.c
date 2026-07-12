/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub_move_orthodox.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:25:34 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>
#include <stdio.h>
#include "mlx.h"

void	move_up(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	if (gcam()->active)
		return (camera_move(fdf, 0, 1.0f));
	move_forward(fdf, 5.0f);
	trans_stack_update(&fdf->trans_stack);
}

void	move_down(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	if (gcam()->active)
		return (camera_move(fdf, 0, -1.0f));
	move_backward(fdf, 5.0f);
	trans_stack_update(&fdf->trans_stack);
}

void	move_left(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	if (gcam()->active)
		return (camera_move(fdf, 1, -1.0f));
	move_left_internal(fdf, 5.0f);
	trans_stack_update(&fdf->trans_stack);
}

void	move_right(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	if (gcam()->active)
		return (camera_move(fdf, 1, 1.0f));
	move_right_internal(fdf, 5.0f);
	trans_stack_update(&fdf->trans_stack);
}
