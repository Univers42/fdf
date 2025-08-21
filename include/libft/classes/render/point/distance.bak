/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:06:20 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/04 14:26:41 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"
#include "ft_math.h"

double	euclidean_dist(t_pixel *p1, t_pixel *p2)
{
	double	dx;
	double	dy;
	double	dz;

	if (!p1 || !p2)
		return (-1.0);
	dx = p1->world_pos.x - p2->world_pos.x;
	dy = p1->world_pos.y - p2->world_pos.y;
	dz = p1->world_pos.z - p2->world_pos.z;
	return (ft_sqrt(dx * dx + dy * dy + dz * dz));
}

double	manhattan_dist(t_pixel *p1, t_pixel *p2)
{
	if (!p1 || !p2)
		return (-1.0);
	return (ft_fabs(p1->world_pos.x - p2->world_pos.x)
		+ ft_fabs(p1->world_pos.y - p2->world_pos.y)
		+ ft_fabs(p1->world_pos.z - p2->world_pos.z));
}

int	point_translate(t_pixel *self, int dx, int dy)
{
	double	len;
	double	sx;
	double	sy;

	if (!self)
		return (0);
	len = ft_sqrt((double)dx * dx + (double)dy * dy);
	if (len > 0)
	{
		sx = ((dx / len) * self->speed);
		sy = ((dy / len) * self->speed);
		self->world_pos.x += sx;
		self->world_pos.y += sy;
		self->coordinate.x = (int)self->world_pos.x;
		self->coordinate.y = (int)self->world_pos.y;
	}
	return (1);
}

bool	point_equals(t_pixel *p1, t_pixel *p2)
{
	if (!p1 || !p2)
		return (false);
	return (p1->coordinate.x == p2->coordinate.x
		&& p1->coordinate.y == p2->coordinate.y);
}
