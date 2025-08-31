/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:48:01 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 16:13:16 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/**
 * @brief Computes the cone shape position.
 *
 * Maps the grid point to a position on a conical surface.
 *
 * @param f Pointer to the main application structure.
 * @param p Pointer to the input grid point.
 * @param o Pointer to the output 3D position.
 */
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
