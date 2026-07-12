/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_extra2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/* Helix ribbon: y drives three turns up the spiral, x spans the band. */
void	pos_helix(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	float	t;
	float	s;
	float	r;
	float	v;

	r = fminf(f->width, f->height) / 3.0f;
	v = (float)p->y / (float)(f->height - 1);
	t = 6.0f * M_PI * v;
	s = (2.0f * (float)p->x) / (float)(f->width - 1) - 1.0f;
	o->x = (r + s * r * 0.25f) * cosf(t);
	o->y = (r + s * r * 0.25f) * sinf(t);
	o->z = (v - 0.5f) * r * 2.7f + orig_z(f, p) * 0.05f;
}

/* Klein bottle, figure-8 immersion. */
void	pos_klein(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	float	u;
	float	v;
	float	q;
	float	a;

	a = fminf(f->width, f->height) / 6.0f;
	u = (2.0f * M_PI * (float)p->x) / (float)(f->width - 1);
	v = (2.0f * M_PI * (float)p->y) / (float)(f->height - 1);
	q = 2.0f + cosf(u * 0.5f) * sinf(v) - sinf(u * 0.5f) * sinf(2.0f * v);
	o->x = a * q * cosf(u);
	o->y = a * q * sinf(u);
	o->z = a * (sinf(u * 0.5f) * sinf(v) + cosf(u * 0.5f) * sinf(2.0f * v))
		+ orig_z(f, p) * 0.03f;
}

/* Whirlpool funnel: rings tighten and rise toward the center. */
void	pos_vortex(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	float	s;
	float	v;
	float	th;
	float	rr;

	s = fminf(f->width, f->height);
	v = (float)p->y / (float)(f->height - 1);
	th = (2.0f * M_PI * (float)p->x) / (float)(f->width - 1)
		+ (1.0f - v) * 4.0f;
	rr = s * 0.55f * (0.12f + 0.88f * v);
	o->x = rr * cosf(th);
	o->y = rr * sinf(th);
	o->z = (1.0f - v) * (1.0f - v) * s * 0.5f - s * 0.15f
		+ orig_z(f, p) * 0.06f;
}
