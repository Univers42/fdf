/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matric_from_quaternon.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:37:44 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 14:05:51 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"
#include "pixel.h"

/*
** Convert quaternion (x,y,z,w) in t_fpoint4 to 3x3 rotation (rest identity).
*/
void	matrix_from_quaternion(t_mat4 *out, t_fpoint4 q)
{
	float	x;
	float	y;
	float	z;
	float	w;

	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
	matrix_identity(out);
	out->m[0][0] = 1.0f - 2.0f * (y * y + z * z);
	out->m[0][1] = 2.0f * (x * y - w * z);
	out->m[0][2] = 2.0f * (x * z + w * y);
	out->m[1][0] = 2.0f * (x * y + w * z);
	out->m[1][1] = 1.0f - 2.0f * (x * x + z * z);
	out->m[1][2] = 2.0f * (y * z - w * x);
	out->m[2][0] = 2.0f * (x * z - w * y);
	out->m[2][1] = 2.0f * (y * z + w * x);
	out->m[2][2] = 1.0f - 2.0f * (x * x + y * y);
}
