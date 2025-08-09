/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_heart.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:54:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 16:54:44 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	heart_scale(t_app *f)
{
	return (fminf(f->width, f->height) / 4.0f);
}

void	heart_set_xy(t_fpoint3 *o, t_fpoint2 n, float s)
{
	o->x = n.x * s;
	o->y = n.y * s;
}

void	pos_heart(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	float		s;
	t_fpoint2	n;

	s = heart_scale(f);
	n = heart_norm(f, p);
	heart_set_xy(o, n, s);
	if (n.y > 0.0f)
		heart_upper_lobes(s, n, o);
	else
		heart_lower_point(s, n, o);
	o->z += orig_z(f, p) * 0.02f;
}
