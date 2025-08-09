/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_shadow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 02:05:02 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 02:18:46 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ambient_pass(t_app *f)
{
	int		y;
	int		x;
	int		i;
	float	z0;
	float	occ;

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
			occ = ao_accumulate(f, i, z0);
			ao_apply(f, i, occ);
			++x;
		}
		++y;
	}
}

/* ---------------- Public Shadow Interface -------------------------- */

void	apply_shadow_effects(t_app *fdf, bool depth_shadows,
			bool ambient_shadows)
{
	if (!fdf)
		return ;
	if (depth_shadows)
		depth_pass(fdf);
	if (ambient_shadows)
		ambient_pass(fdf);
}

void	toggle_shadow_mode(t_app *fdf)
{
	fdf->shadow_mode = (fdf->shadow_mode + 1) % 4;
}

void	update_shadow_effects(t_app *fdf)
{
	bool	depth;
	bool	ambient;

	if (fdf->shadow_mode == 1)
		return ;
	depth = (fdf->shadow_mode == 1 || fdf->shadow_mode == 3);
	ambient = (fdf->shadow_mode == 2 || fdf->shadow_mode == 3);
	apply_shadow_effects(fdf, depth, ambient);
}
