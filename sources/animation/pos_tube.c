/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_tube.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:15:09 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 16:49:06 by dlesieur         ###   ########.fr       */
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

static void	tube_init_vars(t_tube_vars *v, t_app *f, t_point2 *p)
{
	v->br = fminf(f->width, f->height) / 4.0f;
	v->hl = (float)f->height * 0.5f;
	v->ang = ((float)p->x / (float)f->width) * 2.0f * M_PI;
	v->r = v->br + orig_z(f, p) * 0.3f;
	v->h = (float)p->y - (float)f->height / 2.0f;
}

static int	tube_cap_point(t_tube_vars *v, t_app *f, t_point2 *p, t_fpoint3 *o)
{
	v->c.x = (float)f->width / 2.0f;
	v->c.y = (float)f->height / 2.0f;
	v->d.x = (float)p->x - v->c.x;
	if ((float)p->y < v->c.y)
		v->d.y = (float)p->y;
	else
		v->d.y = (float)p->y - (float)(f->height - 1);
	v->gr = sqrtf(v->d.x * v->d.x + v->d.y * v->d.y);
	v->mr = (float)f->width / 2.0f;
	if (v->gr <= v->mr)
	{
		v->cr = (v->gr / v->mr) * v->r;
		o->x = v->cr * cosf(v->ang);
		o->y = v->h;
		o->z = v->cr * sinf(v->ang);
		return (1);
	}
	o->x = 0.0f;
	o->y = v->h;
	o->z = 0.0f;
	return (1);
}

void	pos_tube(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	t_tube_vars	v;

	tube_init_vars(&v, f, p);
	if (fabsf(v.h) >= v.hl * 0.95f)
	{
		if (tube_cap_point(&v, f, p, o))
			return ;
	}
	o->x = v.r * cosf(v.ang);
	o->y = v.h;
	o->z = v.r * sinf(v.ang);
}
