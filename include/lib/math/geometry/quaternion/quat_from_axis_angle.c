/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_from_axis_angle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:54:52 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 14:56:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

/*
** Creates quaternion for rotation of
angle_rad around axis (axis.x,axis.y,axis.z).
*/
void	quat_from_axis_angle(t_quat *q, t_fpoint3 axis, float angle_rad)
{
	float		half;
	float		s;
	float		mag;
	t_fpoint4	id;

	half = angle_rad * 0.5f;
	s = sinf(half);
	mag = sqrtf(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
	if (mag == 0.0f)
	{
		id.x = 0.0f;
		id.y = 0.0f;
		id.z = 0.0f;
		id.w = 1.0f;
		quat_init(q, id);
		return ;
	}
	q->x = axis.x / mag * s;
	q->y = axis.y / mag * s;
	q->z = axis.z / mag * s;
	q->w = cosf(half);
}
