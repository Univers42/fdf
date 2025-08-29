/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trackball_apply.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 00:56:54 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/29 18:55:51 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	apply_trackball_to_transform_stack(t_app *fdf)
{
	t_trackball_state	*trackball;
	float				rotation_matrix[16];
	float				temp_matrix[16];
	int					i;

	trackball = gtrack();
	if (!trackball->initialized || !transition_is_active())
		return ;
	quaternion_to_matrix4(trackball->current_quat, rotation_matrix);
	matrix4_multiply(fdf->trans_stack.combined, rotation_matrix, temp_matrix);
	i = 0;
	while (i < 16)
	{
		fdf->trans_stack.combined[i] = temp_matrix[i];
		i++;
	}
}

static void	calculate_centroid(t_app *fdf, float *cx, float *cy, float *cz)
{
	int	i;
	int	total_points;

	*cx = 0.0f;
	*cy = 0.0f;
	*cz = 0.0f;
	total_points = fdf->width * fdf->height;
	i = 0;
	while (i < total_points)
	{
		*cx += fdf->transformed_points[i].x;
		*cy += fdf->transformed_points[i].y;
		*cz += fdf->transformed_points[i].z;
		i++;
	}
	*cx /= total_points;
	*cy /= total_points;
	*cz /= total_points;
}

static void	matrix4_apply_to_point(const float *m, float *x, float *y, float *z)
{
	float	v[4];
	float	out[4];
	int		i;
	int		j;

	v[0] = *x;
	v[1] = *y;
	v[2] = *z;
	v[3] = 1.0f;
	i = -1;
	while (++i < 4)
	{
		out[i] = 0;
		j = -1;
		while (++j < 4)
			out[i] += m[i * 4 + j] * v[j];
	}
	*x = out[0];
	*y = out[1];
	*z = out[2];
}

static void	apply_trackball_to_shape_points_inner(
	t_app *fdf, float *centroid, t_trackball_shape_state *shape_state
)
{
	t_fpoint2	p;
	int			idx;
	float		s[3];

	p.y = -1;
	while (++p.y < fdf->height)
	{
		p.x = -1;
		while (++p.x < fdf->width)
		{
			idx = p.y * fdf->width + p.x;
			s[0] = fdf->transformed_points[idx].x - centroid[0];
			s[1] = fdf->transformed_points[idx].y - centroid[1];
			s[2] = fdf->transformed_points[idx].z - centroid[2];
			matrix4_apply_to_point(shape_state->rotation_matrix,
				&s[0], &s[1], &s[2]);
			fdf->transformed_points[idx].x = s[0] + centroid[0];
			fdf->transformed_points[idx].y = s[1] + centroid[1];
			fdf->transformed_points[idx].z = s[2] + centroid[2];
		}
	}
}

void	apply_trackball_to_shape_points(t_app *fdf)
{
	t_trackball_shape_state	*shape_state;
	float					c[3];

	shape_state = gstate_tball();
	if (!shape_state->is_active || !transition_is_active())
		return ;
	calculate_centroid(fdf, &c[0], &c[1], &c[2]);
	apply_trackball_to_shape_points_inner(fdf, c, shape_state);
	shape_state->is_active = false;
}
