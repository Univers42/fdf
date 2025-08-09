/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_heart.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:47:16 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 17:52:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	heart_upper_lobes(float s, t_fpoint2 n, t_fpoint3 *o)
{
	float	dist1;
	float	dist2;

	dist1 = sqrtf((n.x + 0.5f) * (n.x + 0.5f)
			+ (n.y - 0.3f) * (n.y - 0.3f));
	dist2 = sqrtf((n.x - 0.5f) * (n.x - 0.5f)
			+ (n.y - 0.3f) * (n.y - 0.3f));
	if (dist1 < 0.6f || dist2 < 0.6f)
		o->z = s * 0.3f;
	else
		o->z = 0.0f;
}

void	heart_lower_point(float s, t_fpoint2 n, t_fpoint3 *o)
{
	float	point_factor;

	point_factor = 1.0f + n.y;
	if (point_factor > 0.0f && fabsf(n.x) < point_factor * 0.8f)
		o->z = s * 0.2f * point_factor;
	else
		o->z = 0.0f;
}

t_fpoint2	heart_norm(t_app *f, t_point2 *p)
{
	t_fpoint2	n;

	n.x = (2.0f * (float)p->x / (float)(f->width - 1)) - 1.0f;
	n.y = -((2.0f * (float)p->y / (float)(f->height - 1)) - 1.0f);
	return (n);
}
