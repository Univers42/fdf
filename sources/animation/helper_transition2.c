/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_transition2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:36:02 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 14:40:48 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* generic applicator: compute target shape positions and apply transform */
static void	apply_shape_grid(t_app *fdf, t_shape_type shape)
{
	int		y;
	int		x;
	int		index;
	float	sp[4];
	float	*dp;
	float	sx, sy, sz;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			get_shape_position_coords(shape, fdf, x, y, &sx, &sy, &sz);
			sp[0] = sx;
			sp[1] = sy;
			sp[2] = sz;
			sp[3] = 1.0f;
			dp = (float *)&fdf->transformed_points[index];
			matrix4_dot_product(fdf->trans_stack.combined, sp, dp);
			++x;
		}
		++y;
	}
}

/* per-shape wrappers (uniform signature) */
static void	apply_original_noop(t_app *fdf) { (void)fdf; }
static void	apply_torus_persistent(t_app *fdf) { apply_shape_grid(fdf, SHAPE_TORUS); }
static void	apply_sphere_persistent(t_app *fdf) { apply_shape_grid(fdf, SHAPE_SPHERE); }
static void	apply_cube_persistent(t_app *fdf) { apply_shape_grid(fdf, SHAPE_CUBE); }
static void	apply_pyramid_persistent(t_app *fdf) { apply_shape_grid(fdf, SHAPE_PYRAMID); }
static void	apply_dna_persistent(t_app *fdf) { apply_shape_grid(fdf, SHAPE_DNA); }
static void	apply_chips_persistent(t_app *fdf) { apply_shape_grid(fdf, SHAPE_CHIPS); }
static void	apply_wave_persistent(t_app *fdf) { apply_shape_grid(fdf, SHAPE_WAVE); }
static void	apply_heart_persistent(t_app *fdf) { apply_shape_grid(fdf, SHAPE_HEART); }
static void	apply_cone_persistent(t_app *fdf) { apply_shape_grid(fdf, SHAPE_CONE); }
static void	apply_tube_persistent(t_app *fdf) { apply_shape_grid(fdf, SHAPE_TUBE); }

/* singleton function-pointer table (exported) */
t_shape_apply_fn	*shape_apply_tbl(void)
{
	static t_shape_apply_fn	tbl[SHAPE_COUNT] = {
		apply_original_noop,
		apply_torus_persistent,
		apply_sphere_persistent,
		apply_cube_persistent,
		apply_pyramid_persistent,
		apply_dna_persistent,
		apply_chips_persistent,
		apply_wave_persistent,
		apply_heart_persistent,
		apply_cone_persistent,
		apply_tube_persistent
	};

	return (tbl);
}

/* public API used by transition_system.c */
void	apply_shape_with_transform(t_app *fdf, t_shape_type shape)
{
	t_shape_apply_fn	*tbl;
	int					idx;

	tbl = shape_apply_tbl();
	idx = (int)shape;
	if (idx < 0 || idx >= (int)SHAPE_COUNT || tbl[idx] == NULL)
		return ;
	tbl[idx](fdf);
}
