/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_dna.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:49:15 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 16:50:42 by dlesieur         ###   ########.fr       */
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

void	pos_dna(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	float	r;
	float	ny;
	float	ang;
	float	phase;

	r = fminf(f->width, f->height) / 6.0f;
	ny = (2.0f * (float)p->y / (float)(f->height - 1)) - 1.0f;
	ang = ny * 4.0f * M_PI;
	if ((p->x % 2) == 0)
		phase = 0.0f;
	else
		phase = M_PI;
	o->x = r * cosf(ang + phase);
	o->y = ny * f->height * 0.4f;
	o->z = r * sinf(ang + phase) + orig_z(f, p) * 0.02f;
}
