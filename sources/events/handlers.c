/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:02:13 by dmontesd          #+#    #+#             */
/*   Updated: 2025/08/08 00:23:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdio.h>
#include <math.h>

#define ROTATE_FACTOR 0.03f

int	motion_handler(int x, int y, t_app *fdf)
{
	t_projection_ctl	*proj;
	float				ndcx;
	float				ndcy;

	ndcx = ((float)x - (float)fdf->drag_start[0]) / WIN_WIDTH;
	ndcy = ((float)fdf->drag_start[1] - (float)y) / WIN_HEIGHT;
	proj = &fdf->trans_stack.projection;
	if (fdf->input_state == INPUT_STATE_DRAGGING)
	{
		trans_stack_pan(&fdf->trans_stack,
			ndcx * (proj->l - proj->r), ndcy * (proj->b - proj->t));
		fdf->drag_start[0] = x;
		fdf->drag_start[1] = y;
	}
	else if (fdf->input_state == INPUT_STATE_ROTATING)
	{
		trans_stack_rotate_x(&fdf->trans_stack,
			ndcy * (proj->b - proj->t) * ROTATE_FACTOR);
		trans_stack_rotate_y(&fdf->trans_stack,
			ndcx * (proj->r - proj->l) * ROTATE_FACTOR);
		fdf->drag_start[0] = x;
		fdf->drag_start[1] = y;
	}
	return (0);
}

int	button_press_handler(int button, int x, int y, t_app *fdf)
{
	int	i;

	i = -1;
	if (button == Button4)
		while (++i < (int)gcamera_speed(0))
			trans_stack_zoom(&fdf->trans_stack, -1);
	i = -1;
	if (button == Button5)
		while (++i < (int)gcamera_speed(0))
			trans_stack_zoom(&fdf->trans_stack, +1);
	if (button == Button1 && fdf->input_state == INPUT_STATE_IDLE)
	{
		fdf->drag_start[0] = x;
		fdf->drag_start[1] = y;
		fdf->input_state = INPUT_STATE_DRAGGING;
	}
	if (button == Button3 && fdf->input_state == INPUT_STATE_IDLE)
	{
		fdf->drag_start[0] = x;
		fdf->drag_start[1] = y;
		fdf->input_state = INPUT_STATE_ROTATING;
	}
	return (0);
}

int	button_release_handler(int button, int x, int y, t_app *fdf)
{
	(void)x;
	(void)y;
	if ((button == Button1 || button == Button3)
		&& (fdf->input_state == INPUT_STATE_DRAGGING
			|| fdf->input_state == INPUT_STATE_ROTATING))
		fdf->input_state = INPUT_STATE_IDLE;
	return (0);
}

bool	is_auto_rotate_active(t_app *fdf)
{
	return (fdf->auto_rotate);
}

void	auto_rotate_update(t_app *fdf)
{
	static float	rotation_angle = 0.0f;
	const float		rotation_speed = 0.008f;
	float			subtle_x;
	float			subtle_z;

	if (!fdf->auto_rotate)
		return ;
	rotation_angle += rotation_speed;
	trans_stack_rotate_y(&fdf->trans_stack, rotation_speed);
	subtle_x = sinf(rotation_angle * 0.3f) * 0.002f;
	subtle_z = cosf(rotation_angle * 0.7f) * 0.001f;
	trans_stack_rotate_x(&fdf->trans_stack, subtle_x);
	trans_stack_rotate_z(&fdf->trans_stack, subtle_z);
}
