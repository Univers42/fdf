/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:48:47 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 16:57:18 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Helper function for color blending
uint32_t    blend_colors(uint32_t base_color, uint32_t texture_color, float blend_factor)
{
	uint8_t base_r = (base_color >> 16) & 0xFF;
	uint8_t base_g = (base_color >> 8) & 0xFF;
	uint8_t base_b = base_color & 0xFF;
	
	uint8_t tex_r = (texture_color >> 16) & 0xFF;
	uint8_t tex_g = (texture_color >> 8) & 0xFF;
	uint8_t tex_b = texture_color & 0xFF;
	
	uint8_t final_r = base_r + (uint8_t)((tex_r - base_r) * blend_factor);
	uint8_t final_g = base_g + (uint8_t)((tex_g - base_g) * blend_factor);
	uint8_t final_b = base_b + (uint8_t)((tex_b - base_b) * blend_factor);
	
	return (final_r << 16) | (final_g << 8) | final_b;
}

