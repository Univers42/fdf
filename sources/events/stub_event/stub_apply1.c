/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub_apply1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:05:23 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 16:53:41 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* per-shape wrappers (uniform signature) */
void	apply_original_noop(t_app *fdf)
{
	(void)fdf;
}

void	apply_torus_persistent(t_app *fdf)
{
	apply_shape_grid(fdf, SHAPE_TORUS);
}

void	apply_sphere_persistent(t_app *fdf)
{
	apply_shape_grid(fdf, SHAPE_SPHERE);
}

void	apply_cube_persistent(t_app *fdf)
{
	apply_shape_grid(fdf, SHAPE_CUBE);
}

void	apply_pyramid_persistent(t_app *fdf)
{
	apply_shape_grid(fdf, SHAPE_PYRAMID);
}
