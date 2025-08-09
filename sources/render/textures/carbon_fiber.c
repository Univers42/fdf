/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carbon_fiber.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:15:01 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:45:41 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static uint32_t	select_carbon_color(int weave_x, int weave_y, int is_fiber_a)
{
	int	is_highlight;

	is_highlight = (weave_x == 0 || weave_y == 0);
	if (is_highlight)
		return (0x666666);
	if (is_fiber_a)
		return (0x1a1a1a);
	return (0x000000);
}

static uint32_t	carbon_pixel(int x, int y, float weave_size)
{
	int	weave_x;
	int	weave_y;
	int	is_fiber_a;

	weave_x = (int)(x / weave_size) % 4;
	weave_y = (int)(y / weave_size) % 4;
	is_fiber_a = ((weave_x + weave_y) % 2) == 0;
	return (select_carbon_color(weave_x, weave_y, is_fiber_a));
}

static void	apply_carbon_row(t_app *fdf, float weave_size, int y)
{
	const t_texture_system	*t = gtexture(NULL);
	int						x;
	int						index;
	uint32_t				tc;

	x = 0;
	while (x < fdf->width)
	{
		index = y * fdf->width + x;
		tc = carbon_pixel(x, y, weave_size);
		fdf->color[index] = blend_colors(t->original_colors[index], tc, 0.7f);
		++x;
	}
}

void	apply_carbon_fiber_texture(t_app *fdf)
{
	const t_texture_system	*t = gtexture(NULL);
	int						y;
	float					weave_size;

	weave_size = 4.0f / t->scale_factor;
	y = 0;
	while (y < fdf->height)
	{
		apply_carbon_row(fdf, weave_size, y);
		++y;
	}
}
