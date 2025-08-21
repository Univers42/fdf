/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trackball_rotate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:08:18 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 15:03:17 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

void	trackball_rotate(float q[4], t_fpoint2 p1, t_fpoint2 p2)
{
	float	p1v[3];
	float	p2v[3];
	float	tmp[3];
	float	t;
	float	phi;

	if (p1.x == p2.x && p1.y == p2.y)
	{
		q[0] = 0.0f;
		q[1] = 0.0f;
		q[2] = 0.0f;
		q[3] = 1.0f;
		return ;
	}
	vset(p1v, p1.x, p1.y, tb_project_to_sphere(TRACKBALLSIZE, p1));
	vset(p2v, p2.x, p2.y, tb_project_to_sphere(TRACKBALLSIZE, p2));
	vsub(p1v, p2v, tmp);
	t = vlength(tmp) / (2.0f * TRACKBALLSIZE);
	if (t > 1.0f)
		t = 1.0f;
	if (t < -1.0f)
		t = -1.0f;
	phi = 2.0f * asinf(t);
	vcross(p2v, p1v, tmp);
	axis_to_quat(tmp, phi, q);
}
