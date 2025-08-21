/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_slerp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:23:28 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 14:27:26 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

static float	quat_dot(const t_quat *a, const t_quat *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w);
}

/**
for efficiency  */
static void	quat_lerp(t_quat *out, const t_quat *a, const t_quat *b, float t)
{
	out->x = a->x + t * (b->x - a->x);
	out->y = a->y + t * (b->y - a->y);
	out->z = a->z + t * (b->z - a->z);
	out->w = a->w + t * (b->w - a->w);
	quat_normalize(out);
}

static void	quat_adjust_sign(float *dot, t_quat *b)
{
	if (*dot < 0.0f)
	{
		*dot = -*dot;
		b->x = -b->x;
		b->y = -b->y;
		b->z = -b->z;
		b->w = -b->w;
	}
}

static void	quat_slerp_interp(t_slerp_interp *interp, float dot, float t)
{
	interp->theta_0 = acosf(dot);
	interp->theta = interp->theta_0 * t;
	interp->sin_theta = sinf(interp->theta);
	interp->sin_theta0 = sinf(interp->theta_0);
	interp->s0 = cosf(interp->theta) - dot * interp->sin_theta
		/ interp->sin_theta0;
	interp->s1 = interp->sin_theta / interp->sin_theta0;
}

/*
** Performs spherical linear interpolation (SLERP)
between two quaternions a and b.
** t in [0,1] interpolates from a (t=0) to b (t=1).
** Usage: quat_slerp(&out, &a, &b, t);
** Expects: All pointers are valid and non-NULL; t in [0,1].
*/
void	quat_slerp(t_quat *out, const t_quat *a, const t_quat *b, float t)
{
	float			dot;
	t_quat			b2;
	t_slerp_interp	interp;

	dot = quat_dot(a, b);
	b2 = *b;
	quat_adjust_sign(&dot, &b2);
	if (dot > 0.9995f)
	{
		quat_lerp(out, a, &b2, t);
		return ;
	}
	quat_slerp_interp(&interp, dot, t);
	out->x = (a->x * interp.s0) + (b2.x * interp.s1);
	out->y = (a->y * interp.s0) + (b2.y * interp.s1);
	out->z = (a->z * interp.s0) + (b2.z * interp.s1);
	out->w = (a->w * interp.s0) + (b2.w * interp.s1);
}
