/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stripes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:25:19 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:25:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static uint32_t	stripe_color(int id)
{
	if (id == 0)
		return (0xFF0000);
	if (id == 1)
		return (0x00FF00);
	return (0x0000FF);
}

static void	stripe_row(t_app *fdf, float w, int y)
{
	int			x;
	int			index;
	float		pos;
	int			id;
	uint32_t	tc;

	x = 0;
	while (x < fdf->width)
	{
		index = y * fdf->width + x;
		pos = (x + y + g_texture.time_accumulator * 20.0f) / w;
		id = (int)pos % 3;
		tc = stripe_color(id);
		fdf->color[index] = blend_colors(g_texture.original_colors[index],
				tc, 0.5f);
		++x;
	}
}

void	apply_stripes_texture(t_app *fdf)
{
	int		y;
	float	stripe_width;

	stripe_width = 6.0f / g_texture.scale_factor;
	y = 0;
	while (y < fdf->height)
	{
		stripe_row(fdf, stripe_width, y);
		++y;
	}
}
