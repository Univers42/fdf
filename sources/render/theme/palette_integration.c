/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette_integration.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 00:28:06 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 00:15:17 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include "theme.h"
#include <stdio.h>
#include <math.h>

uint32_t	get_color_for_z(t_app *fdf, int z)
{
	int		range;
	float	norm;

	range = (fdf->max_z - fdf->min_z);
	if (range == 0)
		norm = 0.5f;
	else
		norm = (float)(z - fdf->min_z) / (float)range;
	return get_color_for_height(fdf, norm);
}

void	update_background_from_palette(t_app *fdf)
{
	ft_printf("DEBUG: update_background_from_palette called (no-op for now)\n");
	(void)fdf;  // For now, just make this a no-op to avoid segfault
	// Background will be handled in the main render loop
}

void	clear_screen_with_palette_bg(t_app *fdf)
{
	ft_printf("DEBUG: clear_screen_with_palette_bg called (no-op for now)\n");
	(void)fdf;  // For now, just make this a no-op to avoid segfault
	// Background will be handled in the main render loop
}