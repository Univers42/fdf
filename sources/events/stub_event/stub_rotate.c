/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:23:46 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 23:32:50 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>
#include <stdio.h>
#include "mlx.h"

// Rotate the model up (around X axis)
void	rotate_up(t_app *fdf, float angle)
{
	if (gcam()->active)
		return (camera_look(fdf, 0.0f, CAM_LOOK));
	trans_stack_rotate_x(&fdf->trans_stack, -angle);
	fdf->trans_stack.dirty[M_ROTATION_X] = true;
}

// Rotate the model down (around X axis)
void	rotate_down(t_app *fdf, float angle)
{
	if (gcam()->active)
		return (camera_look(fdf, 0.0f, -CAM_LOOK));
	trans_stack_rotate_x(&fdf->trans_stack, angle);
	fdf->trans_stack.dirty[M_ROTATION_X] = true;
}

// Rotate the model left (around Y axis)
void	rotate_left(t_app *fdf, float angle)
{
	if (gcam()->active)
		return (camera_look(fdf, -CAM_LOOK, 0.0f));
	trans_stack_rotate_y(&fdf->trans_stack, -angle);
	fdf->trans_stack.dirty[M_ROTATION_Y] = true;
}

// Rotate the model right (around Y axis)
void	rotate_right(t_app *fdf, float angle)
{
	if (gcam()->active)
		return (camera_look(fdf, CAM_LOOK, 0.0f));
	trans_stack_rotate_y(&fdf->trans_stack, angle);
	fdf->trans_stack.dirty[M_ROTATION_Y] = true;
}
