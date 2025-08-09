/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_cube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:11:52 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 18:40:07 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_cube_face_0_1(t_meta_shape *s, t_app *fdf)
{
	if (s->s_face.face == 0)
	{
		s->s_shape.x = s->s_vec.u * s->max_radius;
		s->s_shape.y = s->s_vec.v * s->max_radius;
		s->s_shape.z = s->max_radius + fdf->points[s->index] * 0.05f;
	}
	else
	{
		s->s_shape.x = -s->s_vec.u * s->max_radius;
		s->s_shape.y = s->s_vec.v * s->max_radius;
		s->s_shape.z = -s->max_radius + fdf->points[s->index] * 0.05f;
	}
}

void	apply_cube_face_2_3(t_meta_shape *s, t_app *fdf)
{
	if (s->s_face.face == 2)
	{
		s->s_shape.x = s->max_radius + fdf->points[s->index] * 0.05f;
		s->s_shape.y = s->s_vec.v * s->max_radius;
		s->s_shape.z = -s->s_vec.u * s->max_radius;
	}
	else
	{
		s->s_shape.x = -s->max_radius + fdf->points[s->index] * 0.05f;
		s->s_shape.y = s->s_vec.v * s->max_radius;
		s->s_shape.z = s->s_vec.u * s->max_radius;
	}
}

void	apply_cube_face_4_5(t_meta_shape *s, t_app *fdf)
{
	if (s->s_face.face == 4)
	{
		s->s_shape.x = s->s_vec.u * s->max_radius;
		s->s_shape.y = s->max_radius + fdf->points[s->index] * 0.05f;
		s->s_shape.z = -s->s_vec.v * s->max_radius;
	}
	else
	{
		s->s_shape.x = s->s_vec.u * s->max_radius;
		s->s_shape.y = -s->max_radius + fdf->points[s->index] * 0.05f;
		s->s_shape.z = s->s_vec.v * s->max_radius;
	}
}
