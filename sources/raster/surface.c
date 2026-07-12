/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * Solid-surface renderer: every (strided) grid cell becomes two flat
 * triangles. Color = average of the three vertex colors scaled by the
 * precomputed Lambert shade; at grid density each triangle covers only
 * a few pixels, so flat shading is visually equivalent to Gouraud.
 * Off-screen triangles die in tri_setup's empty clamped bounding box.
 */

static uint32_t	tri_color(t_app *f, const int v[3])
{
	float		s;
	uint32_t	c[3];
	float		*sh;

	sh = gshade(f);
	s = 1.0f;
	if (sh)
		s = (sh[v[0]] + sh[v[1]] + sh[v[2]]) * 0.3333f;
	c[0] = ((f->color[v[0]] >> 16 & 0xFF) + (f->color[v[1]] >> 16 & 0xFF)
			+ (f->color[v[2]] >> 16 & 0xFF)) / 3;
	c[1] = ((f->color[v[0]] >> 8 & 0xFF) + (f->color[v[1]] >> 8 & 0xFF)
			+ (f->color[v[2]] >> 8 & 0xFF)) / 3;
	c[2] = ((f->color[v[0]] & 0xFF) + (f->color[v[1]] & 0xFF)
			+ (f->color[v[2]] & 0xFF)) / 3;
	return (((uint32_t)(c[0] * s) << 16) | ((uint32_t)(c[1] * s) << 8)
		| (uint32_t)(c[2] * s));
}

/*
 * Guard band: a vertex hardly in front of the near plane projects to a
 * huge NDC value; its clamped bbox covers the whole screen and the fill
 * walk melts. Triangles reaching past +-3 NDC are culled (only extreme
 * close-up geometry, at worst a small hole at the screen border).
 */
static bool	tri_project(t_fpoint4 *p)
{
	int	i;

	if (!gcam()->active)
		return (true);
	if (p[0].w < CAM_NEAR || p[1].w < CAM_NEAR || p[2].w < CAM_NEAR)
		return (false);
	i = -1;
	while (++i < 3)
	{
		point_project(&p[i]);
		if (p[i].x < -3.0f || p[i].x > 3.0f
			|| p[i].y < -3.0f || p[i].y > 3.0f)
			return (false);
	}
	return (true);
}

/* Sub-pixel triangle: one z-tested pixel, skip the whole raster setup. */
static void	plot_tri_point(t_app *f, t_tri *t, uint32_t color)
{
	float	*zb;
	long	i;

	zb = gzbuf();
	if (!zb || (unsigned int)t->x[0] >= WIN_WIDTH
		|| (unsigned int)t->y[0] >= WIN_HEIGHT)
		return ;
	i = (long)t->y[0] * WIN_WIDTH + t->x[0];
	if (t->z[0] < zb[i])
	{
		zb[i] = t->z[0];
		((uint32_t *)f->renderer.data)[i] = color;
	}
}

static void	emit_tri(t_app *f, const int v[3])
{
	t_fpoint4	p[3];
	t_tri		t;
	int			i;

	p[0] = f->transformed_points[v[0]];
	p[1] = f->transformed_points[v[1]];
	p[2] = f->transformed_points[v[2]];
	if (!tri_project(p))
		return ;
	i = -1;
	while (++i < 3)
	{
		t.x[i] = ndc_to_screen_x(p[i].x);
		t.y[i] = ndc_to_screen_y(p[i].y);
		t.z[i] = p[i].z;
	}
	if (imax3(t.x[0], t.x[1], t.x[2]) - imin3(t.x[0], t.x[1], t.x[2]) <= 1
		&& imax3(t.y[0], t.y[1], t.y[2])
		- imin3(t.y[0], t.y[1], t.y[2]) <= 1)
		return (plot_tri_point(f, &t, tri_color(f, v)));
	t.color = tri_color(f, v);
	if (gcam()->active)
		t.color = fog_color(t.color, (p[0].w + p[1].w + p[2].w) * 0.334f,
				fmaxf(f->width, f->height));
	raster_triangle(f, &t);
}

void	fdf_draw_surface(t_app *f)
{
	int	v[3];
	int	k[2];
	int	x;
	int	y;

	y = 0;
	while (y < f->height - 1)
	{
		k[0] = fdf_row_stride(f, y, 3.0f, 0);
		k[1] = fdf_row_stride(f, y, 3.0f, 1);
		x = 0;
		while (x < f->width - 1)
		{
			v[0] = y * f->width + x;
			v[1] = y * f->width + imin2(x + k[0], f->width - 1);
			v[2] = imin2(y + k[1], f->height - 1) * f->width + x;
			emit_tri(f, v);
			v[0] = v[1];
			v[1] = imin2(y + k[1], f->height - 1) * f->width
				+ imin2(x + k[0], f->width - 1);
			emit_tri(f, v);
			x += k[0];
		}
		y += k[1];
	}
}
