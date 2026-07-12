/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_camera	*gcam(void)
{
	static t_camera	cam;

	return (&cam);
}

/* Spawn south of the terrain, slightly above it, looking north (+y). */
void	camera_reset(t_app *f)
{
	t_camera	*c;

	c = gcam();
	c->pos[0] = f->width * 0.5f;
	c->pos[1] = -0.35f * f->height;
	c->pos[2] = (float)f->max_z + 0.15f * fminf(f->width, f->height);
	c->yaw = 0.0f;
	c->pitch = -0.35f;
	c->fov = CAM_FOV;
}

/*
 * Row-major P*V. Clip w = distance along forward (positive in front);
 * z_ndc = 1 - 2*near/dist: -1 at the near plane, ->1 far away, so the
 * existing "smaller z wins" depth test and NDC clip keep working.
 */
static void	camera_rows(float *o, t_cam_basis *b, float *pos)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		o[i] = b->r[i] * b->s[0];
		o[4 + i] = b->u[i] * b->s[1];
		o[8 + i] = b->f[i];
		o[12 + i] = b->f[i];
	}
	o[3] = -(b->r[0] * pos[0] + b->r[1] * pos[1] + b->r[2] * pos[2])
		* b->s[0];
	o[7] = -(b->u[0] * pos[0] + b->u[1] * pos[1] + b->u[2] * pos[2])
		* b->s[1];
	o[15] = -(b->f[0] * pos[0] + b->f[1] * pos[1] + b->f[2] * pos[2]);
	o[11] = o[15] - 2.0f * CAM_NEAR;
}

void	camera_matrix(t_app *f, float *o)
{
	t_camera	*c;
	t_cam_basis	b;

	c = gcam();
	if (c->fov == 0.0f)
		camera_reset(f);
	b.f[0] = sinf(c->yaw) * cosf(c->pitch);
	b.f[1] = cosf(c->yaw) * cosf(c->pitch);
	b.f[2] = sinf(c->pitch);
	b.r[0] = cosf(c->yaw);
	b.r[1] = -sinf(c->yaw);
	b.r[2] = 0.0f;
	b.u[0] = b.r[1] * b.f[2] - b.r[2] * b.f[1];
	b.u[1] = b.r[2] * b.f[0] - b.r[0] * b.f[2];
	b.u[2] = b.r[0] * b.f[1] - b.r[1] * b.f[0];
	b.s[1] = 1.0f / tanf(c->fov * 0.5f);
	b.s[0] = b.s[1] * (float)gviewport()->h / (float)gviewport()->w;
	camera_rows(o, &b, c->pos);
}

void	camera_toggle_handler(t_app *fdf, int keycode, void *data)
{
	t_camera	*c;

	(void)keycode;
	(void)data;
	c = gcam();
	c->active = !c->active;
	if (c->active)
		camera_reset(fdf);
	fdf->needs_redraw = true;
	if (c->active)
		ft_printf("Camera: first person (WASD move, QE up/down, "
			"arrows or right-drag look, F exits)\n");
	else
		ft_printf("Camera: orbit mode\n");
}
