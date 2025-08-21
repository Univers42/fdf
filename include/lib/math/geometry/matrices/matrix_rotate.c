/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:38:16 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 14:16:01 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"
#include "pixel.h"
#include <math.h>

/* Normalize axis into v[0..2]; return 0 if zero vector */
static int	normalize_axis(t_fpoint3 axis, float v[7])
{
	float	mag;

	v[0] = axis.x;
	v[1] = axis.y;
	v[2] = axis.z;
	mag = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (mag == 0.0f)
		return (0);
	v[0] /= mag;
	v[1] /= mag;
	v[2] /= mag;
	return (1);
}

void	matrix_rotate(t_mat4 *out, float angle_rad, t_fpoint3 axis)
{
	float	v[7];

	if (!normalize_axis(axis, v))
	{
		matrix_identity(out);
		return ;
	}
	v[4] = sinf(angle_rad);
	v[5] = cosf(angle_rad);
	v[6] = 1.0f - v[5];
	matrix_identity(out);
	out->m[0][0] = v[5] + v[0] * v[0] * v[6];
	out->m[0][1] = v[0] * v[1] * v[6] - v[2] * v[4];
	out->m[0][2] = v[0] * v[2] * v[6] + v[1] * v[4];
	out->m[1][0] = v[1] * v[0] * v[6] + v[2] * v[4];
	out->m[1][1] = v[5] + v[1] * v[1] * v[6];
	out->m[1][2] = v[1] * v[2] * v[6] - v[0] * v[4];
	out->m[2][0] = v[2] * v[0] * v[6] - v[1] * v[4];
	out->m[2][1] = v[2] * v[1] * v[6] + v[0] * v[4];
	out->m[2][2] = v[5] + v[2] * v[2] * v[6];
}
