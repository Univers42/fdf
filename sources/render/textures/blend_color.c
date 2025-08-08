/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:48:47 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:12:44 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Helper function for color blending
//can be replace by lerp_color
uint32_t	blend_colors(uint32_t base_color, uint32_t texture_color,
				float blend_factor)
{
	return (lerp_color(base_color, texture_color, blend_factor));
}
