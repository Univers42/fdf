/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/*
 * axis 0 = forward/back, 1 = strafe, 2 = world up/down.
 * Forward moves along the look direction (true free-fly).
 */
void	camera_move(t_app *f, int axis, float sign)
{
	t_camera	*c;
	float		step;

	c = gcam();
	step = sign * CAM_STEP * fminf(f->width, f->height);
	if (axis == 0)
	{
		c->pos[0] += step * sinf(c->yaw) * cosf(c->pitch);
		c->pos[1] += step * cosf(c->yaw) * cosf(c->pitch);
		c->pos[2] += step * sinf(c->pitch);
	}
	else if (axis == 1)
	{
		c->pos[0] += step * cosf(c->yaw);
		c->pos[1] += step * -sinf(c->yaw);
	}
	else
		c->pos[2] += step;
	f->needs_redraw = true;
}

void	camera_look(t_app *f, float dyaw, float dpitch)
{
	t_camera	*c;

	c = gcam();
	c->yaw += dyaw;
	c->pitch += dpitch;
	if (c->pitch > 1.5f)
		c->pitch = 1.5f;
	if (c->pitch < -1.5f)
		c->pitch = -1.5f;
	f->needs_redraw = true;
}

void	cam_up_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	if (gcam()->active)
		camera_move(fdf, 2, 1.0f);
}

void	cam_down_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	if (gcam()->active)
		camera_move(fdf, 2, -1.0f);
}

/* Distance fog toward the horizon color: sells depth in camera mode. */
uint32_t	fog_color(uint32_t c, float dist, float extent)
{
	float	t;

	t = (dist - 0.35f * extent) / (2.0f * extent);
	if (t <= 0.0f)
		return (c);
	if (t > 1.0f)
		t = 1.0f;
	return (lerp_color(c, SKY_HORIZON & 0xFFFFFF, t));
}
