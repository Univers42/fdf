/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition_system.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:28:19 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 16:03:24 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include "ft_math.h"

/* helpers to keep functions short and declarations at top */

/**
 * @brief Ensures the original positions buffer is allocated
 *
 * Allocates memory for storign the original grid position of not already
 * done. Frees any existing buffer fefore allocating a new one
 *
 * @param fdf Pointer to the main application structure
 * @param st Pointer to the transition state structure
 * @return 1 on success, 0 on failure (memory allocation error)
 *
 */
static int	ensure_original_buffer(t_app *fdf, t_transition_state *st)
{
	size_t	total;

	total = (size_t)fdf->width * (size_t)fdf->height * 3u;
	if (st->original_positions)
		free(st->original_positions);
	st->original_positions = (float *)malloc(sizeof(float) * total);
	if (!st->original_positions)
		return (0);
	return (1);
}

/**
 * @brief Fills the original positions buffer with grid data.
 *
 * Populates the original_positions array with x, y coordinates and z values
 * from the initial grid points.
 *
 * @param fdf Pointer to the main application structure.
 * @param st Pointer to the transition state structure.
 */
static void	fill_original_positions(t_app *fdf, t_transition_state *st)
{
	int	y;
	int	x;
	int	index;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			index = y * fdf->width + x;
			st->original_positions[index * 3 + 0] = (float)x;
			st->original_positions[index * 3 + 1] = (float)y;
			st->original_positions[index * 3 + 2] = fdf->points[index];
			++x;
		}
		++y;
	}
}

/**
 * @brief Stores the original grid positions once.
 *
 * Initializes the original positions buffer if not already done.
 * This is called once to capture the initial state of the grid.
 *
 * @param fdf Pointer to the main application structure.
 */
void	store_original_positions(t_app *fdf)
{
	t_transition_state	*st;

	st = gtransition(NULL);
	if (st->initialized)
		return ;
	if (!ensure_original_buffer(fdf, st))
		return ;
	fill_original_positions(fdf, st);
	st->initialized = true;
}

/**
 * @brief Applies interpolation for a single row during transition.
 *
 * For each point in the row, computes the interpolated position between
 * the current and target shapes using the progress factor t, then applies
 * the transformation matrix.
 *
 * @param fdf Pointer to the main application structure.
 * @param st Pointer to the transition state structure.
 * @param t Interpolation progress factor (0.0 to 1.0).
 * @param y The row index to process.
 */
static void	apply_row(t_app *fdf, t_transition_state *st, float t, int y)
{
	t_row_apply	v;
	t_point2	p;

	v.x = 0;
	while (v.x < fdf->width)
	{
		v.index = y * fdf->width + v.x;
		p.x = v.x;
		p.y = y;
		get_shape_position(st->current_shape, fdf, &p, &v.c);
		get_shape_position(st->target_shape, fdf, &p, &v.d);
		v.o.x = v.c.x + (v.d.x - v.c.x) * t;
		v.o.y = v.c.y + (v.d.y - v.c.y) * t;
		v.o.z = v.c.z + (v.d.z - v.c.z) * t;
		v.sp[0] = v.o.x;
		v.sp[1] = v.o.y;
		v.sp[2] = v.o.z;
		v.sp[3] = 1.0f;
		v.dp = (float *)&fdf->transformed_points[v.index];
		matrix4_dot_product(fdf->trans_stack.combined, v.sp, v.dp);
		++v.x;
	}
}

/**
 * @brief Applies the interpolated frame for the entire grid.
 *
 * Processes each row of the grid, applying the interpolation between
 * current and target shapes based on the progress factor t.
 *
 * @param fdf Pointer to the main application structure.
 * @param st Pointer to the transition state structure.
 * @param t Interpolation progress factor (0.0 to 1.0).
 */
void	apply_interpolated_frame(t_app *fdf, t_transition_state *st, float t)
{
	int	y;

	y = 0;
	while (y < fdf->height)
	{
		apply_row(fdf, st, t, y);
		++y;
	}
}
