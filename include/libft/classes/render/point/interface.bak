/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 04:58:32 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/04 13:33:16 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"

t_point_vtable	*singleton_vpoint(void)
{
	static t_point_vtable	vpoint = \
	{
		.destroy = point_destroy,
		.get_coordinate = point_get_coordinate,
		.get_position = point_get_position,
		.get_color = point_get_color,
		.set_coordinate = point_set_coordinate,
		.set_position = point_set_position,
		.set_color = point_set_color,
		.set_z_value = point_set_z_value,
		.translate = point_translate,
		.scale = point_scale,
		.clone = point_clone
	};

	return (&vpoint);
}

t_pixel *point_clone(t_pixel *self)
{
	t_pixel *clone;

	if (!self)
		return (NULL);
	clone = point_new_with_color(self->coordinate.x, self->coordinate.y,
			self->world_pos.z, self->color.hex_color);
	if (!clone)
		return (NULL);
	clone->world_pos = self->world_pos;
	return (clone);
}

void	point_destroy(t_pixel *self)
{
	if (self)
		free(self);
}

t_pixel *point_new(int x, int y, int z)
{
	t_pixel *point;

	point = malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	point->coordinate.x = x;
	point->coordinate.y = y;
	point->world_pos.x = x;
	point->world_pos.y = y;
	point->world_pos.z = z;
	point->color.hex_color = 0xFFFFFFFF;
	point->color.u_raw_color.r = 255;
	point->color.u_raw_color.g = 255;
	point->color.u_raw_color.b = 255;
	point->color.u_raw_color.a = 255;
	point->vtable = singleton_vpoint();
	point->speed = 10.0;
	return (point);
}

t_pixel *point_new_with_color(int x, int y, int z, uint32_t color)
{
	t_pixel *point;

	point = point_new(x, y, z);
	if (!point)
		return (NULL);
	point->vtable->set_color(point, color);
	return (point);
}
