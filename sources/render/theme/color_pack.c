/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_pack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:39:59 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/21 15:41:31 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	color_interp_t(const t_bresenham_state *bs, int step);

static void	color_base_rgb(int color, int out[3])
{
	out[0] = (color >> 16) & 0xFF;
	out[1] = (color >> 8) & 0xFF;
	out[2] = color & 0xFF;
}

static int	clamp_byte(int v)
{
	if (v < 0)
		return (0);
	if (v > 255)
		return (255);
	return (v);
}

static int	apply_delta(int base, float delta, float t)
{
	int	v;

	v = base + (int)(delta * t);
	return (clamp_byte(v));
}

static uint32_t	pack_rgb3(const int c[3])
{
	return (((uint32_t)c[0] << 16) | ((uint32_t)c[1] << 8) | (uint32_t)c[2]);
}

uint32_t	pack_color(t_bresenham_state *bs, int step)
{
	float	t;
	int		base[3];
	int		out[3];

	if (!bs)
		return (0);
	t = color_interp_t(bs, step);
	color_base_rgb((int)bs->color1, base);
	out[0] = apply_delta(base[0], bs->color_r_delta, t);
	out[1] = apply_delta(base[1], bs->color_g_delta, t);
	out[2] = apply_delta(base[2], bs->color_b_delta, t);
	return (pack_rgb3(out));
}
