/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:48:01 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 16:48:03 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	pos_cone(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	float	max_r;
	float	ang;
	float	h;
	float	hl;
	float	r;

	max_r = fminf(f->width, f->height) / 4.0f;
	ang = ((float)p->x / (float)f->width) * 2.0f * M_PI;
	h = (float)p->y - (float)f->height / 2.0f;
	hl = (float)f->height * 0.5f;
	if (fabsf(h) < hl)
	{
		r = max_r * (1.0f - fabsf(h) / hl);
		o->x = r * cosf(ang);
		o->y = h;
		o->z = r * sinf(ang);
	}
	else
	{
		o->x = 0.0f;
		o->y = h;
		o->z = 0.0f;
	}
}
