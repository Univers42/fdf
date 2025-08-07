/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub_camera_projection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:27:01 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 23:35:14 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>
#include <stdio.h>
#include "mlx.h"

void	zoom_in(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	trans_stack_zoom(&fdf->trans_stack, -1);
}

void	zoom_out(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	trans_stack_zoom(&fdf->trans_stack, +1);
}

void	projection_iso(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	trans_stack_isometric(&fdf->trans_stack);
	projection_reset_params(&fdf->trans_stack.projection);
	fdf->trans_stack.dirty[M_PROJECTION] = true;
	trans_stack_update(&fdf->trans_stack);
	center_model(&fdf->trans_stack, (float)fdf->width,
		(float)fdf->height, (float)(fdf->max_z - fdf->min_z));
}

void	project_iso(t_app *fdf, int keycode, void *data)
{
	projection_iso(fdf, keycode, data);
}

void	projection_fly(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	trans_stack_parallel(&fdf->trans_stack);
	projection_reset_params(&fdf->trans_stack.projection);
	fdf->trans_stack.dirty[M_PROJECTION] = true;
	trans_stack_update(&fdf->trans_stack);
	center_model(&fdf->trans_stack, (float)fdf->width,
		(float)fdf->height, (float)(fdf->max_z - fdf->min_z));
}
