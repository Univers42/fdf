/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:27:12 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:27:13 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdint.h>

// Example: 9 background color themes (ARGB format)
const uint32_t g_bg_colors[9] = {
	0x00101010, // Default dark
	0x00FFFFFF, // White
	0x00FF0000, // Red
	0x0000FF00, // Green
	0x000000FF, // Blue
	0x00FFFF00, // Yellow
	0x0000FFFF, // Cyan
	0x00FF00FF, // Magenta
	0x00202020  // Dark gray
};

static int g_current_bg = 0;

void	set_background_theme(int theme)
{
	if (theme >= 0 && theme < 9)
		g_current_bg = theme;
}

uint32_t	get_background_color(void)
{
	return 0x00000000; // Force pure black background
}
