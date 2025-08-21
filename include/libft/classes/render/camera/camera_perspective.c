/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_perspective.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:13:32 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 15:13:35 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	camera_set_perspective(t_camera *self, t_camera_perspective p)
{
	if (self != NULL)
		self->perspective = p;
}

t_camera_perspective	camera_get_perspective(t_camera *self)
{
	if (self == NULL)
		return (CAMERA_ISOMETRIC);
	return (self->perspective);
}

void	camera_move(t_camera *self, double dx, double dy)
{
	if (self == NULL)
		return ;
	self->offset_x += dx;
	self->offset_y += dy;
}
