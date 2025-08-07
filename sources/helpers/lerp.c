/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:45:52 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 13:48:56 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
performs linear interpolation between two colors and return the result.
This function adds a bound checking for `t` called clamping to handle out
of range `t`values
*/
uint32_t lerp_color(uint32_t c1, uint32_t c2, float t)
{
	if (t <= 0.0f) return c1;
	if (t >= 1.0f) return c2;
	
	uint8_t r1 = (c1 >> 16) & 0xFF, g1 = (c1 >> 8) & 0xFF, b1 = c1 & 0xFF;
	uint8_t r2 = (c2 >> 16) & 0xFF, g2 = (c2 >> 8) & 0xFF, b2 = c2 & 0xFF;
	uint8_t r = r1 + (uint8_t)((r2 - r1) * t);
	uint8_t g = g1 + (uint8_t)((g2 - g1) * t);
	uint8_t b = b1 + (uint8_t)((b2 - b1) * t);
	
	return (r << 16) | (g << 8) | b;
}



