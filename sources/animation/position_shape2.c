/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_shape2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:15:09 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 16:40:50 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static inline float	orig_z(t_app *f, t_point2 *p)
{
	t_transition_state	*st;
	int					i;

	st = gtransition(NULL);
	if (!st || !st->original_positions)
		return (0.0f);
	i = p->y * f->width + p->x;
	if (i < 0 || i >= f->width * f->height)
		return (0.0f);
	return (st->original_positions[i * 3 + 2]);
}

void	pos_chips(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	float	s;
	float	nx;
	float	ny;

	s = fminf(f->width, f->height) / 3.0f;
	nx = (2.0f * (float)p->x / (float)(f->width - 1)) - 1.0f;
	ny = (2.0f * (float)p->y / (float)(f->height - 1)) - 1.0f;
	o->x = nx * s;
	o->y = ny * s;
	o->z = 0.3f * (nx * nx - ny * ny) * s + orig_z(f, p) * 0.1f;
}

void	pos_wave(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	float	a;
	float	b;
	float	nx;
	float	ny;

	a = fminf(f->width, f->height) / 6.0f;
	b = fminf(f->width, f->height) / 3.0f;
	nx = (2.0f * (float)p->x / (float)(f->width - 1)) - 1.0f;
	ny = (2.0f * (float)p->y / (float)(f->height - 1)) - 1.0f;
	o->x = nx * b;
	o->y = ny * b;
	o->z = a * sinf(nx * 3.0f * M_PI) * cosf(ny * 3.0f * M_PI)
		+ orig_z(f, p) * 0.1f;
}
