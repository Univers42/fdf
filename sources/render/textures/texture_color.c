/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:49:43 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:45:37 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Store original colors for texture blending
void	store_original_texture_colors(t_app *fdf)
{
	t_texture_system	*t;
	int					i;

	t = gtexture(NULL);
	i = -1;
	if (t->initialized)
		return ;
	t->total_points = fdf->width * fdf->height;
	if (t->original_colors)
		free(t->original_colors);
	t->original_colors = malloc(sizeof(uint32_t) * t->total_points);
	if (!t->original_colors)
		return ;
	while (++i < t->total_points)
		t->original_colors[i] = fdf->color[i];
	t->initialized = true;
	ft_printf("🎨 Texture system initialized with %d colors\n", t->total_points);
}
