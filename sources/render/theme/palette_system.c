/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 04:34:38 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 04:34:47 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	init_palette_system(t_app *fdf)
{
	if (!fdf)
		return ;
	fdf->palette_state.count = theme_preset_count();
	fdf->palette_state.current = 0;
	fdf->palette_state.funcs = NULL;
}

void	set_palette_index(int idx, t_app *fdf)
{
	t_theme	theme;

	if (!fdf)
		return ;
	if (fdf->palette_state.count == 0)
		init_palette_system(fdf);
	if (idx < 0)
		idx = 0;
	if (idx >= fdf->palette_state.count)
		idx = fdf->palette_state.count - 1;
	fdf->palette_state.current = idx;
	theme_make_preset(idx, &theme);
	apply_theme_to_map(fdf, &theme);
}

uint32_t	get_background_color(t_app *fdf)
{
	t_theme	theme;

	if (!fdf || fdf->palette_state.count == 0)
		return (pack_rgba(0, 0, 0, 255));
	if (fdf->palette_state.current < 0
		|| fdf->palette_state.current >= fdf->palette_state.count)
		fdf->palette_state.current = 0;
	theme_make_preset(fdf->palette_state.current, &theme);
	return (theme.background);
}

// Compatibility function for bresenham algorithm
uint32_t	pack_color(t_bresenham_state *bs, int step)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b_val;
	float	t;

	if (!bs)
		return (0xFF000000);
	if (bs->error_count <= 0)
		t = 0.0f;
	else
		t = (float)step / (float)bs->error_count;
	r = (uint8_t)((bs->color1 >> 24) + t * bs->color_r_delta);
	g = (uint8_t)(((bs->color1 >> 16) & 0xFF) + t * bs->color_g_delta);
	b_val = (uint8_t)(((bs->color1 >> 8) & 0xFF) + t * bs->color_b_delta);
	return (pack_rgba(r, g, b_val, 255));
}

void	apply_current_palette(t_app *fdf)
{
	int		i;
	int		total_points;
	float	z_norm;
	float	z_value;

	if (!fdf || !fdf->points || !fdf->color)
		return ;
	total_points = fdf->width * fdf->height;
	if (total_points <= 0)
		return ;
	i = -1;
	while (++i < total_points)
	{
		z_value = fdf->points[i];
		if (fdf->max_z != fdf->min_z)
			z_norm = (z_value - (float)fdf->min_z)
				/ (float)(fdf->max_z - fdf->min_z);
		else
			z_norm = 0.5f;
		fdf->color[i] = get_color_for_height(fdf, z_norm);
	}
}
