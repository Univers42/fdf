/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_transition2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:36:02 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 16:14:39 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Applies a shape transformation to the entire grid.
 *
 * Computes the 3D positions for each grid point based on the specified shape
 * and applies the transformation matrix to update the transformed points.
 *
 * @param fdf Pointer to the main application structure.
 * @param shape The shape type to apply.
 */
void	apply_shape_grid(t_app *fdf, t_shape_type shape)
{
	t_meta_shape	s;
	t_point2		pt;
	t_fpoint3		out;

	s.s_coord.y = -1;
	while (++s.s_coord.y < fdf->height)
	{
		s.s_coord.x = -1;
		while (++s.s_coord.x < fdf->width)
		{
			s.index = s.s_coord.y * fdf->width + s.s_coord.x;
			pt.x = s.s_coord.x;
			pt.y = s.s_coord.y;
			get_shape_position_coords(shape, fdf, pt, &out);
			s.sp[0] = out.x;
			s.sp[1] = out.y;
			s.sp[2] = out.z;
			s.sp[3] = 1.0f;
			s.dp = (float *)&fdf->transformed_points[s.index];
			matrix4_dot_product(fdf->trans_stack.combined, s.sp, s.dp);
		}
	}
}

/**
 * @brief Returns the singleton function-pointer table for shape applicators.
 *
 * Provides a static table of functions to apply each shape transformation.
 *
 * @return Pointer to the array of shape apply functions.
 */
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

/**
 * @brief Applies the transformation for a specific shape
 * using the function table.
 *
 * Validates the shape index and calls the corresponding apply function.
 *
 * @param fdf Pointer to the main application structure.
 * @param shape The shape type to apply.
 */
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

/**
 * @brief Updates the transition state and applies transformations.
 *
 * Handles the transition logic, including interpolation
 * during active transitions
 * and applying the current shape when not transitioning.
 *
 * @param fdf Pointer to the main application structure.
 */
void	transition_update(t_app *fdf)
{
	t_transition_state	*st;
	float				progress;
	float				smooth_t;

	st = gtransition(NULL);
	if (!st->active && st->current_shape == SHAPE_ORIGINAL)
		return ;
	store_original_positions(fdf);
	if (!st->original_positions)
		return ;
	if (st->active)
	{
		progress = (float)st->frame / (float)st->max_frames;
		smooth_t = ease_in_out(progress);
		apply_interpolated_frame(fdf, st, smooth_t);
		st->frame++;
		if (st->frame >= st->max_frames)
		{
			st->active = false;
			st->frame = 0;
			st->current_shape = st->target_shape;
		}
	}
	else if (st->current_shape != SHAPE_ORIGINAL)
		apply_shape_with_transform(fdf, st->current_shape);
}

/**
 * @brief Starts a transition to the next shape.
 *
 * Sets the transition state to active and prepares for
 * transitioning to the next shape.
 *
 * @param to_torus Unused parameter (legacy).
 */
void	transition_start_torus(bool to_torus)
{
	t_transition_state	*st;
	t_shape_type		next;

	(void)to_torus;
	st = gtransition(NULL);
	next = (st->current_shape + 1) % SHAPE_COUNT;
	st->active = true;
	st->frame = 0;
	st->target_shape = next;
}
