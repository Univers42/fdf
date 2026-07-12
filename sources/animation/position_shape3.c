/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_shape3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:13:25 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 16:09:31 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/**
 * @brief Retrieves the original Z value for a grid point.
 *
 * Gets the original Z coordinate from the stored original positions.
 *
 * @param f Pointer to the main application structure.
 * @param p Pointer to the input grid point.
 * @return The original Z value, or 0.0f if invalid.
 */
float	orig_z(t_app *f, t_point2 *p)
{
	int	i;

	i = p->y * f->width + p->x;
	if (i < 0 || i >= f->width * f->height)
		return (0.0f);
	return (f->points[i]);
}

// Prototypes for functions used in shape_pos_tbl
void	pos_original(t_app *f, t_point2 *p, t_fpoint3 *o);
void	pos_torus(t_app *f, t_point2 *p, t_fpoint3 *o);
void	pos_sphere(t_app *f, t_point2 *p, t_fpoint3 *o);
void	pos_cube(t_app *f, t_point2 *p, t_fpoint3 *o);
void	pos_dna(t_app *f, t_point2 *p, t_fpoint3 *o);
void	pos_chips(t_app *f, t_point2 *p, t_fpoint3 *o);
void	pos_wave(t_app *f, t_point2 *p, t_fpoint3 *o);
void	pos_heart(t_app *f, t_point2 *p, t_fpoint3 *o);
void	pos_cone(t_app *f, t_point2 *p, t_fpoint3 *o);
void	pos_tube(t_app *f, t_point2 *p, t_fpoint3 *o);
void	pos_mobius(t_app *f, t_point2 *p, t_fpoint3 *o);
void	pos_knot(t_app *f, t_point2 *p, t_fpoint3 *o);
void	pos_galaxy(t_app *f, t_point2 *p, t_fpoint3 *o);
void	pos_helix(t_app *f, t_point2 *p, t_fpoint3 *o);
void	pos_klein(t_app *f, t_point2 *p, t_fpoint3 *o);
void	pos_vortex(t_app *f, t_point2 *p, t_fpoint3 *o);

/**
 * @brief Computes the pyramid shape position.
 *
 * Maps the grid point to a position on a pyramid surface.
 *
 * @param f Pointer to the main application structure.
 * @param p Pointer to the input grid point.
 * @param o Pointer to the output 3D position.
 */
void	pos_pyramid(t_app *f, t_point2 *p, t_fpoint3 *o)
{
	float	base;
	float	nx;
	float	ny;
	float	dist;

	base = fminf(f->width, f->height) / 3.0f;
	nx = (2.0f * (float)p->x / (float)(f->width - 1)) - 1.0f;
	ny = (2.0f * (float)p->y / (float)(f->height - 1)) - 1.0f;
	dist = fmaxf(fabsf(nx), fabsf(ny));
	o->x = nx * base / 2.0f;
	o->y = ny * base / 2.0f;
	if (dist <= 1.0f)
		o->z = base * (1.0f - dist) + orig_z(f, p) * 0.05f;
	else
		o->z = orig_z(f, p) * 0.05f;
}

/**
 * @brief Returns the singleton function-pointer table for shape positions.
 *
 * Provides a static table of functions to compute positions for each shape.
 *
 * @return Pointer to the array of shape position functions.
 */
t_shape_pos_fn	*shape_pos_tbl(void)
{
	static t_shape_pos_fn	tbl[SHAPE_COUNT] = {
		pos_original, /* SHAPE_ORIGINAL */
		pos_torus,
		pos_sphere,
		pos_cube,
		pos_pyramid,
		pos_dna,
		pos_chips,
		pos_wave,
		pos_heart,
		pos_cone,
		pos_tube,
		pos_mobius,
		pos_knot,
		pos_galaxy,
		pos_helix,
		pos_klein,
		pos_vortex
	};

	return (tbl);
}
