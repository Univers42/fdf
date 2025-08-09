/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_circuit_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:07:05 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:45:42 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static uint32_t	circuit_color(
	int h_trace, int v_trace, int junction, int active
)
{
	if (junction)
		return (0xFFD700);
	if ((h_trace || v_trace) && active)
		return (0x00FF00);
	if (h_trace || v_trace)
		return (0x00AA00);
	return (0x006600);
}

static uint32_t	circuit_pixel(int x, int y)
{
	const t_texture_system	*t = gtexture(NULL);
	int						h_trace;
	int						v_trace;
	int						junction;
	int						active;

	h_trace = (y % 8 == 0 || y % 8 == 1);
	v_trace = (x % 12 == 0 || x % 12 == 1);
	junction = ((x % 12) < 3 && (y % 8) < 3);
	active = ((x + y + (int)(t->time_accumulator * 10.0f)) % 20) < 2;
	return (circuit_color(h_trace, v_trace, junction, active));
}

static void	circuit_row(t_app *fdf, int y)
{
	const t_texture_system	*t = gtexture(NULL);
	int						x;
	int						index;
	uint32_t				tc;

	x = 0;
	while (x < fdf->width)
	{
		index = y * fdf->width + x;
		tc = circuit_pixel(x, y);
		fdf->color[index] = blend_colors(t->original_colors[index], tc, 0.6f);
		++x;
	}
}

void	apply_circuit_board_texture(t_app *fdf)
{
	int	y;

	y = 0;
	while (y < fdf->height)
	{
		circuit_row(fdf, y);
		++y;
	}
}
