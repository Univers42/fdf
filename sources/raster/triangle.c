/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * Classic incremental edge-function rasterizer. Vertices are wound CCW
 * by tri_setup; a pixel is inside when all three edge values are >= 0
 * (checked with one OR of the sign bits). Depth interpolates linearly
 * across the plane (dz/dx, dz/dy computed once per triangle).
 */

static void	tri_swap(t_tri *t, int i, int j)
{
	float	fz;
	int		v;

	v = t->x[i];
	t->x[i] = t->x[j];
	t->x[j] = v;
	v = t->y[i];
	t->y[i] = t->y[j];
	t->y[j] = v;
	fz = t->z[i];
	t->z[i] = t->z[j];
	t->z[j] = fz;
}

static int	tri_setup(t_tri *t, t_tri_ctx *c)
{
	int	area;
	int	i;

	area = (t->x[1] - t->x[0]) * (t->y[2] - t->y[0])
		- (t->y[1] - t->y[0]) * (t->x[2] - t->x[0]);
	if (area == 0)
		return (0);
	if (area < 0)
		tri_swap(t, 1, 2);
	c->bb[0] = imax2(imin3(t->x[0], t->x[1], t->x[2]), 0);
	c->bb[1] = imax2(imin3(t->y[0], t->y[1], t->y[2]), 0);
	c->bb[2] = imin2(imax3(t->x[0], t->x[1], t->x[2]), WIN_WIDTH - 1);
	c->bb[3] = imin2(imax3(t->y[0], t->y[1], t->y[2]), WIN_HEIGHT - 1);
	if (c->bb[0] > c->bb[2] || c->bb[1] > c->bb[3])
		return (0);
	i = -1;
	while (++i < 3)
	{
		c->a[i] = t->y[i] - t->y[(i + 1) % 3];
		c->b[i] = t->x[(i + 1) % 3] - t->x[i];
		c->w[i] = (t->x[(i + 1) % 3] - t->x[i]) * (c->bb[1] - t->y[i])
			- (t->y[(i + 1) % 3] - t->y[i]) * (c->bb[0] - t->x[i]);
	}
	return (1);
}

static void	tri_plane(t_tri *t, t_tri_ctx *c)
{
	float	area;

	area = (float)((t->x[1] - t->x[0]) * (t->y[2] - t->y[0])
			- (t->y[1] - t->y[0]) * (t->x[2] - t->x[0]));
	c->dzdx = ((t->z[1] - t->z[0]) * (t->y[2] - t->y[0])
			- (t->z[2] - t->z[0]) * (t->y[1] - t->y[0])) / area;
	c->dzdy = ((t->z[2] - t->z[0]) * (t->x[1] - t->x[0])
			- (t->x[2] - t->x[0]) * (t->z[1] - t->z[0])) / area;
	c->z = t->z[0] + c->dzdx * (c->bb[0] - t->x[0])
		+ c->dzdy * (c->bb[1] - t->y[0]);
}

static void	tri_row(t_tri_ctx *c, uint32_t *fb, float *zb, uint32_t color)
{
	int		w[3];
	float	z;
	int		x;

	w[0] = c->w[0];
	w[1] = c->w[1];
	w[2] = c->w[2];
	z = c->z;
	x = c->bb[0] - 1;
	while (++x <= c->bb[2])
	{
		if ((w[0] | w[1] | w[2]) >= 0 && z < zb[x])
		{
			zb[x] = z;
			fb[x] = color;
		}
		w[0] += c->a[0];
		w[1] += c->a[1];
		w[2] += c->a[2];
		z += c->dzdx;
	}
}

void	raster_triangle(t_app *f, t_tri *t)
{
	t_tri_ctx	c;
	uint32_t	*fb;
	float		*zb;
	int			y;

	if (!tri_setup(t, &c))
		return ;
	tri_plane(t, &c);
	fb = (uint32_t *)f->renderer.data;
	zb = gzbuf();
	if (!zb)
		return ;
	y = c.bb[1] - 1;
	while (++y <= c.bb[3])
	{
		tri_row(&c, fb + (long)y * WIN_WIDTH, zb + (long)y * WIN_WIDTH,
			t->color);
		c.w[0] += c.b[0];
		c.w[1] += c.b[1];
		c.w[2] += c.b[2];
		c.z += c.dzdy;
	}
}
