/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_project.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:13:47 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 15:27:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

static void	camera_apply_projection(t_camera *self,
		const t_position *pos, double *px, double *py)
{
	if (self->perspective == CAMERA_ISOMETRIC)
	{
		*px = pos->x - pos->y;
		*py = (pos->x + pos->y) * 0.5 - pos->z;
	}
	else if (self->perspective == CAMERA_TOP)
	{
		*px = pos->x;
		*py = pos->y;
	}
	else if (self->perspective == CAMERA_SIDE)
	{
		*px = pos->x;
		*py = pos->z;
	}
	else
	{
		*px = 0.0;
		*py = 0.0;
	}
}

t_vec2	camera_project_point(t_camera *self, t_point *point)
{
	t_vec2		result;
	t_position	pos;
	double		px;
	double		py;

	result.x = 0;
	result.y = 0;
	if (self == NULL || point == NULL || point->vtable == NULL)
		return (result);
	point->vtable->get_position(point, &pos);
	camera_apply_projection(self, &pos, &px, &py);
	result.x = (int)(px * self->zoom + self->offset_x);
	result.y = (int)(py * self->zoom + self->offset_y);
	return (result);
}
