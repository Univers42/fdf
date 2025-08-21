/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_zoom.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:13:43 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 15:13:45 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	camera_set_zoom(t_camera *self, double zoom, double cx, double cy)
{
	double	old;

	if (self == NULL)
		return ;
	if (zoom < 0.1)
		zoom = 0.1;
	old = self->zoom;
	self->offset_x = cx - (cx - self->offset_x) * (zoom / old);
	self->offset_y = cy - (cy - self->offset_y) * (zoom / old);
	self->zoom = zoom;
}

void	camera_zoom_by(t_camera *self, double factor, double cx, double cy)
{
	double	target;

	if (self == NULL)
		return ;
	target = self->zoom * factor;
	if (target < 0.1)
		target = 0.1;
	camera_set_zoom(self, target, cx, cy);
}
