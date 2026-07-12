/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_extra1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/* Mobius strip: x walks the loop, y walks across the half-twisted band. */
void	pos_mobius(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	float	u;
	float	s;
	float	r;
	float	w;

	r = fminf(f->width, f->height) / 3.0f;
	w = r * 0.4f;
	u = (2.0f * M_PI * (float)p->x) / (float)(f->width - 1);
	s = (2.0f * (float)p->y) / (float)(f->height - 1) - 1.0f;
	o->x = (r + s * w * cosf(u * 0.5f)) * cosf(u);
	o->y = (r + s * w * cosf(u * 0.5f)) * sinf(u);
	o->z = s * w * sinf(u * 0.5f) + orig_z(f, p) * 0.05f;
}

/*
 * Trefoil torus knot (p=2, q=3) with a tube around it; the tube's radial
 * direction in XY is simply (cos 2t, sin 2t), so no Frenet frame needed.
 * Map height modulates the tube thickness.
 */
void	pos_knot(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	float	t;
	float	phi;
	float	a;
	float	r;

	a = fminf(f->width, f->height) / 6.5f;
	t = (2.0f * M_PI * (float)p->x) / (float)(f->width - 1);
	phi = (2.0f * M_PI * (float)p->y) / (float)(f->height - 1);
	r = a * 0.35f + orig_z(f, p) * 0.02f;
	o->x = a * (2.0f + cosf(3.0f * t)) * cosf(2.0f * t)
		+ r * cosf(phi) * cosf(2.0f * t);
	o->y = a * (2.0f + cosf(3.0f * t)) * sinf(2.0f * t)
		+ r * cosf(phi) * sinf(2.0f * t);
	o->z = a * sinf(3.0f * t) + r * sinf(phi);
}

/* Spiral galaxy: y is the radius, x the angle; arms twist toward center. */
void	pos_galaxy(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	float	s;
	float	r;
	float	th;
	float	rr;

	s = fminf(f->width, f->height);
	r = (float)p->y / (float)(f->height - 1);
	th = (4.0f * M_PI * (float)p->x) / (float)(f->width - 1) + 6.0f * r;
	rr = s * 0.55f * (0.05f + 0.95f * r);
	o->x = rr * cosf(th);
	o->y = rr * sinf(th);
	o->z = (1.0f - r) * (1.0f - r) * s * 0.12f
		+ orig_z(f, p) * 0.1f * (1.0f - 0.5f * r);
}
