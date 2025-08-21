/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:00:06 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/30 05:20:01 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"

uint32_t	rgb_to_hex(uint8_t r, uint8_t g, uint8_t b)
{
	return (((uint32_t)0xFF << 24) | ((uint32_t)r << 16)
		| ((uint32_t)g << 8) | (uint32_t)b);
}

void	hex_to_rgb(uint32_t hex, uint8_t *r, uint8_t *g, uint8_t *b)
{
	if (!r || !g || !b)
		return ;
	*r = (hex >> 16) & 0xFF;
	*g = (hex >> 8) & 0xFF;
	*b = hex & 0xFF;
}
