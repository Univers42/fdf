/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:45:52 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 00:42:41 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_math.h"
/**
performs linear interpolation between two colors and return the result.
This function adds a bound checking for `t` called clamping to handle out
of range `t`values
*/

uint32_t	lerp_color(uint32_t c1, uint32_t c2, float t)
{
	t_color	color1;
	t_color	color2;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	if (t <= 0.0f)
		return (c1);
	if (t >= 1.0f)
		return (c2);
	color1.u_raw_color.r = (c1 >> 16) & 0xFF;
	color1.u_raw_color.g = (c1 >> 8) & 0xFF;
	color1.u_raw_color.b = c1 & 0xFF;
	color2.u_raw_color.r = (c2 >> 16) & 0xFF;
	color2.u_raw_color.g = (c2 >> 8) & 0xFF;
	color2.u_raw_color.b = c2 & 0xFF;
	r = color1.u_raw_color.r + (uint8_t)((color2.u_raw_color.r
				- color1.u_raw_color.r) * t);
	g = color1.u_raw_color.g + (uint8_t)((color2.u_raw_color.g
				- color1.u_raw_color.g) * t);
	b = color1.u_raw_color.b + (uint8_t)((color2.u_raw_color.b
				- color1.u_raw_color.b) * t);
	return ((r << 16) | (g << 8) | b);
}
