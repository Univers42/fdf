/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_effects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 21:30:18 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 02:18:15 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

int	*shadow_mode_slot(void)
{
	static int	mode = 0;

	return (&mode);
}

/* ---------------- Depth Pass Helpers (was too long) ---------------- */

static float	depth_factor(float v, float range)
{
	float	t;

	t = v / range;
	if (t < 0.5f)
		t = 0.6f + 0.4f * (t / 0.5f);
	else
		t = fminf(1.1f, 1.0f + 0.2f * ((t - 0.5f) / 0.5f));
	return (t);
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
		t = depth_factor(f->points[i] - f->min_z, range);
		c = f->color[i];
		f->color[i] = ((int)(((c >> 16) & 0xFF) * t) << 16)
			| ((int)(((c >> 8) & 0xFF) * t) << 8)
			| ((int)((c & 0xFF) * t));
		++i;
	}
}

/* ---------------- Ambient Occlusion (split into helpers) ------------ */

static float	ao_accumulate(t_app *f, int i, float z0)
{
	float	occ;

	occ = 0.0f;
	if (f->points[i - 1] > z0)
		occ += f->points[i - 1] - z0;
	if (f->points[i + 1] > z0)
		occ += f->points[i + 1] - z0;
	if (f->points[i - f->width] > z0)
		occ += f->points[i - f->width] - z0;
	if (f->points[i + f->width] > z0)
		occ += f->points[i + f->width] - z0;
	return (fminf(0.5f, occ / 20.0f));
}

static void	ao_apply(t_app *f, int i, float occ)
{
	float	fct;
	int		c;

	if (occ <= 0.0f)
		return ;
	fct = 1.0f - occ;
	c = f->color[i];
	f->color[i] = ((int)(((c >> 16) & 0xFF) * fct) << 16)
		| ((int)(((c >> 8) & 0xFF) * fct) << 8)
		| ((int)((c & 0xFF) * fct));
}
