/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:36:16 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/21 15:38:52 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		return (0);
	if (fdf->palette_state.current < 0
		|| fdf->palette_state.current >= fdf->palette_state.count)
		fdf->palette_state.current = 0;
	theme_make_preset(fdf->palette_state.current, &theme);
	return (theme.background);
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

void	apply_palette_to_points(t_app *fdf, t_pivot *color, float range)
{
	int		i;
	float	z;
	float	t;

	i = -1;
	while (++i < fdf->width * fdf->height)
	{
		z = fdf->points[i];
		t = (z - fdf->min_z) / range;
		fdf->color[i] = get_palette_color(color, t);
	}
}
