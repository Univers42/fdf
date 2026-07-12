/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * In camera mode transformed_points holds CLIP coordinates (w = view
 * distance). Segments crossing the near plane are clipped in clip space
 * (linear there, curved after the divide), then perspective-divided.
 * w keeps the view distance for fog.
 */

static void	mix4(t_fpoint4 *a, const t_fpoint4 *b, float t)
{
	a->x += (b->x - a->x) * t;
	a->y += (b->y - a->y) * t;
	a->z += (b->z - a->z) * t;
	a->w += (b->w - a->w) * t;
}

void	point_project(t_fpoint4 *p)
{
	float	inv;

	inv = 1.0f / p->w;
	p->x *= inv;
	p->y *= inv;
	p->z *= inv;
}

bool	edge_project(t_fpoint4 *a, t_fpoint4 *b)
{
	float	t;

	if (a->w < CAM_NEAR && b->w < CAM_NEAR)
		return (false);
	if (a->w < CAM_NEAR)
	{
		t = (CAM_NEAR - a->w) / (b->w - a->w);
		mix4(a, b, t);
	}
	else if (b->w < CAM_NEAR)
	{
		t = (CAM_NEAR - b->w) / (a->w - b->w);
		mix4(b, a, t);
	}
	point_project(a);
	point_project(b);
	return (true);
}
