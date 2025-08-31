/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_transition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:48:32 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 16:04:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Fallback position setter for invalid inputs.
 *
 * Sets the output position to the grid coordinates with z=0.
 *
 * @param fdf Pointer to the main application structure (unused).
 * @param p Pointer to the input point coordinates.
 * @param o Pointer to the output 3D point.
 */
static void	pos_fallback(t_app *fdf, t_point2 *p, t_fpoint3 *o)
{
	(void)fdf;
	if (!p || !o)
		return ;
	o->x = (float)p->x;
	o->y = (float)p->y;
	o->z = 0.0f;
}

/**
 * @brief Retrieves the 3D position for a given shape and grid point.
 *
 * Validates inputs and uses a function table to compute the position
 * for the specified shape. Falls back to default if invalid.
 *
 * @param shape The shape type to compute position for.
 * @param fdf Pointer to the main application structure.
 * @param p Pointer to the input grid point.
 * @param out Pointer to the output 3D position.
 */
void	get_shape_position(t_shape_type shape, t_app *fdf, t_point2 *p,
	t_fpoint3 *out)
{
	t_shape_pos_fn	*tbl;
	int				idx;
	int				index;

	if (!fdf || !p || !out || fdf->width <= 1 || fdf->height <= 1)
		return (pos_fallback(fdf, p, out));
	index = p->y * fdf->width + p->x;
	if (index < 0 || index >= fdf->width * fdf->height)
		return (pos_fallback(fdf, p, out));
	tbl = shape_pos_tbl();
	if (!tbl)
		return (pos_fallback(fdf, p, out));
	idx = (int)shape;
	if (idx < 0 || idx >= (int)SHAPE_COUNT || tbl[idx] == NULL)
		return (pos_fallback(fdf, p, out));
	tbl[idx](fdf, p, out);
}

/**
 * @brief Overloaded version of get_shape_position with coordinate struct.
 *
 * Calls get_shape_position with the provided coordinates.
 *
 * @param shape The shape type to compute position for.
 * @param fdf Pointer to the main application structure.
 * @param coord The input grid coordinates.
 * @param out Pointer to the output 3D position.
 */
void	get_shape_position_coords(t_shape_type shape, t_app *fdf,
			t_point2 coord, t_fpoint3 *out)
{
	if (!fdf || !out)
		return ;
	get_shape_position(shape, fdf, &coord, out);
}
