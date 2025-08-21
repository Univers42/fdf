/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:45:52 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/21 15:50:40 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_math.h"

static int	lerp_channel_shift(uint32_t c1, uint32_t c2, float t, int s)
{
	int	a;
	int	b;
	int	v;

	a = (int)((c1 >> s) & 0xFF);
	b = (int)((c2 >> s) & 0xFF);
	v = a + (int)((b - a) * t);
	if (v < 0)
		v = 0;
	if (v > 255)
		v = 255;
	return (v);
}

uint32_t	lerp_color(uint32_t c1, uint32_t c2, float t)
{
	int	r;
	int	g;
	int	b;

	if (t <= 0.0f)
		return (c1);
	if (t >= 1.0f)
		return (c2);
	r = lerp_channel_shift(c1, c2, t, 16);
	g = lerp_channel_shift(c1, c2, t, 8);
	b = lerp_channel_shift(c1, c2, t, 0);
	return (((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b);
}
