/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trackball.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:52:39 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 14:52:47 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

/*
** Project a 2D point onto a virtual trackball (sphere or hyperbolic sheet).
*/
float	tb_project_to_sphere(float r, t_fpoint2 p)
{
	float	d;
	float	t;
	float	z;

	d = sqrtf(p.x * p.x + p.y * p.y);
	if (d < r * 0.70710678118654752440f)
		z = sqrtf(r * r - d * d);
	else
	{
		t = r / 1.41421356237309504880f;
		z = (t * t) / d;
	}
	return (z);
}

/* Refactored trackball: fewer params, ≤5 vars, norm-compliant */
void	trackball(float q[4], t_fpoint2 p1, t_fpoint2 p2)
{
	float	v1[3];
	float	v2[3];
	float	tmp[3];
	float	t;
	float	phi;

	if (p1.x == p2.x && p1.y == p2.y)
	{
		vzero(q);
		q[3] = 1.0f;
		return ;
	}
	vset(v1, p1.x, p1.y, tb_project_to_sphere(TRACKBALLSIZE, p1));
	vset(v2, p2.x, p2.y, tb_project_to_sphere(TRACKBALLSIZE, p2));
	vsub(v1, v2, tmp);
	t = vlength(tmp) / (2.0f * TRACKBALLSIZE);
	if (t > 1.0f)
		t = 1.0f;
	if (t < -1.0f)
		t = -1.0f;
	phi = 2.0f * asinf(t);
	vcross(v2, v1, tmp);
	axis_to_quat(tmp, phi, q);
}
