/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:49:43 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 16:57:49 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Store original colors for texture blending
void    store_original_texture_colors(t_app *fdf)
{
	if (g_texture.initialized)
		return;
	
	g_texture.total_points = fdf->width * fdf->height;
	
	if (g_texture.original_colors)
		free(g_texture.original_colors);
	
	g_texture.original_colors = malloc(sizeof(uint32_t) * g_texture.total_points);
	if (!g_texture.original_colors)
		return;
	
	// Store original colors
	for (int i = 0; i < g_texture.total_points; i++)
		g_texture.original_colors[i] = fdf->color[i];
	
	g_texture.initialized = true;
	printf("🎨 Texture system initialized with %d colors\n", g_texture.total_points);
}
