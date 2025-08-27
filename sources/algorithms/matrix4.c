/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:54:47 by dmontesd          #+#    #+#             */
/*   Updated: 2025/08/26 17:21:11 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
 
/**
 * @brief Create a 4x4 identity matrix (row-major).
 * @param[out] out Pointer to at least 16 floats (destination 4x4 matrix).
 * @return void
 * @note The function zeroes all 16 elements then sets the diagonal entries
 *       out[0], out[5], out[10], out[15] to 1.0f. Use this before applying
 *       partial setters like matrix4_rotate_* that only modify a subset of
 *       elements.
 */
void	identity_matrix4(float *out)
{
	ft_memset(out, 0, sizeof(float[16]));
	out[0] = 1.0f;
	out[5] = 1.0f;
	out[10] = 1.0f;
	out[15] = 1.0f;
}

/**
 * @brief Multiply two 4x4 matrices (row-major): out = a * b.
 * @param[in] a Pointer to the first 4x4 matrix (16 floats, row-major).
 * @param[in] b Pointer to the second 4x4 matrix (16 floats, row-major).
 * @param[out] out Pointer to the destination 4x4 matrix (16 floats, row-major).
 * @return void
 */
void	matrix4_multiply(const float *a, const float *b, float *out)
{
	int	i;
	int	j;
	int	k;

	ft_memset(out, 0, sizeof(float [16]));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4)
			{
				out[i * 4 + j] += a[i * 4 + k] * b[k * 4 + j];
				++k;
			}
			++j;
		}
		++i;
	}
}

/**
 * @brief Write the X-axis rotation submatrix into the provided 4x4 matrix.
 * @param[in,out] m Pointer to a 4x4 matrix (row-major). Only the rotation
 *                  entries related to X-axis rotation are overwritten.
 * @param[in] rads Rotation angle in radians.
 * @return void
 * @note This function sets:
 *       m[5]  =  cos(rads)
 *       m[6]  = -sin(rads)
 *       m[9]  =  sin(rads)
 *       m[10] =  cos(rads)
 *       Call identity_matrix4(m) first if you need a pure X-rotation matrix.
 * @example
 * float m[16];
 * identity_matrix4(m);
 * matrix4_rotate_x_abs(m, M_PI / 2);
 */
void	matrix4_rotate_x_abs(float *m, float rads)
{
	m[5] = cosf(rads);
	m[6] = -sinf(rads);
	m[9] = sinf(rads);
	m[10] = cosf(rads);
}

/**
 * @brief Write the Y-axis rotation submatrix into the provided 4x4 matrix.
 * @param[in,out] m Pointer to a 4x4 matrix (row-major). Only the rotation
 *                  entries related to Y-axis rotation are overwritten.
 * @param[in] rads Rotation angle in radians.
 * @return void
 * @note This function sets:
 *       m[0]  =  cos(rads)
 *       m[2]  =  sin(rads)
 *       m[8]  = -sin(rads)
 *       m[10] =  cos(rads)
 *       Call identity_matrix4(m) first if you need a pure Y-rotation matrix.
 * @example
 * float m[16];
 * identity_matrix4(m);
 * matrix4_rotate_y_abs(m, M_PI / 4);
 */
void	matrix4_rotate_y_abs(float *m, float rads)
{
	m[0] = cosf(rads);
	m[2] = sinf(rads);
	m[8] = -sinf(rads);
	m[10] = cosf(rads);
}

/**
 * @brief Write the Z-axis rotation submatrix into the provided 4x4 matrix.
 * @param[in,out] m Pointer to a 4x4 matrix (row-major). Only the rotation
 *                  entries related to Z-axis rotation are overwritten.
 * @param[in] rads Rotation angle in radians.
 * @return void
 * @note This function sets:
 *       m[0] =  cos(rads)
 *       m[1] = -sin(rads)
 *       m[4] =  sin(rads)
 *       m[5] =  cos(rads)
 *       Call identity_matrix4(m) first if you need a pure Z-rotation matrix.
 * @example
 * float m[16];
 * identity_matrix4(m);
 * matrix4_rotate_z_abs(m, M_PI);
 */
void	matrix4_rotate_z_abs(float *m, float rads)
{
	m[0] = cosf(rads);
	m[1] = -sinf(rads);
	m[4] = sinf(rads);
	m[5] = cosf(rads);
}
