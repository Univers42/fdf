/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:08:44 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/03 16:06:11 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void    set_background(t_window *self, int color)
{
	if (!self)
		return ;
	self->bg_color = color;
}

void	set_size(t_window *self, int width, int height)
{
	if (!self)
		return ;
	self->width = width;
	self->height = height;
	if (self->img_ptr)
		mlx_destroy_image(self->mlx_ptr, self->img_ptr);
	self->img_ptr = mlx_new_image(self->img_ptr, width, height);
	if (self->img_ptr)
	self->img_data = mlx_get_data_addr(self->img_ptr, &self->bpp,
										&self->size_line, &self->endian);
}

