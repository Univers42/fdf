/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_effects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 21:30:18 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 23:00:28 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

int	*shadow_mode_slot(void)
{
	static int	mode = 0;

	return (&mode);
}

void	depth_pass(t_app *f)
{
	int		i;
	int		total;
	float	range;
	float	t;
	int		c;

	if (!f || !f->points || !f->color)
		return ;
	range = (float)(f->max_z - f->min_z);
	if (range <= 0)
		range = 1.0f;
	total = f->width * f->height;
	i = 0;
	while (i < total)
	{
		t = (f->points[i] - f->min_z) / range;
		if (t < 0.5f)
			t = 0.6f + 0.4f * (t / 0.5f);
		else
			t = fminf(1.1f, 1.0f + 0.2f * ((t - 0.5f) / 0.5f));
		c = f->color[i];
		f->color[i] = ((int)(((c >> 16) & 0xFF) * t) << 16)
			| ((int)(((c >> 8) & 0xFF) * t) << 8)
			| ((int)((c & 0xFF) * t));
		++i;
	}
}

void	ambient_pass(t_app *f)
{
	int		y;
	int		x;
	int		i;
	float	occ;
	float	z0;

	if (!f || !f->points || !f->color || f->width < 3 || f->height < 3)
		return ;
	y = 1;
	while (y < f->height - 1)
	{
		x = 1;
		while (x < f->width - 1)
		{
			i = y * f->width + x;
			z0 = f->points[i];
			occ = 0.0f;
			if (f->points[i - 1] > z0)
				occ += f->points[i - 1] - z0;
			if (f->points[i + 1] > z0)
				occ += f->points[i + 1] - z0;
			if (f->points[i - f->width] > z0)
				occ += f->points[i - f->width] - z0;
			if (f->points[i + f->width] > z0)
				occ += f->points[i + f->width] - z0;
			occ = fminf(0.5f, occ / 20.0f);
			if (occ > 0.0f)
			{
				float fct = 1.0f - occ;
				int c = f->color[i];
				f->color[i] = ((int)(((c >> 16) & 0xFF) * fct) << 16)
					| ((int)(((c >> 8) & 0xFF) * fct) << 8)
					| ((int)((c & 0xFF) * fct));
			}
			++x;
		}
		++y;
	}
}

// Enhanced shadow system with multiple effects
void apply_shadow_effects(t_app *fdf, bool depth_shadows, bool ambient_shadows)
{
	if (!fdf)
		return ;
	if (depth_shadows)
		apply_depth_shadow(fdf);
	if (ambient_shadows)
		apply_ambient_shadows(fdf);
}

static int g_shadow_mode = 0;

void toggle_shadow_mode(void)
{
	g_shadow_mode = (g_shadow_mode + 1) % 4;
}

void update_shadow_effects(t_app *fdf)
{
	bool	depth;
	bool	ambient;

	if (g_shadow_mode == 0)
		return ;
	depth = (g_shadow_mode == 1 || g_shadow_mode == 3);
	ambient = (g_shadow_mode == 2 || g_shadow_mode == 3);
	apply_shadow_effects(fdf, depth, ambient);
}

int get_shadow_mode(void)
{
	return (g_shadow_mode);
}
