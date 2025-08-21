/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_vec_multiply.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:38:31 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/03 15:55:49 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"

/*
** Multiplies a 4x4 matrix by a 4D vector: out = mat * vec.
** Usage: matrix_vec_multiply(&out, &mat, &vec);
** Expects: All pointers are valid and non-NULL.
*/

void	matrix_vec_multiply(t_vec4 *out, const t_mat4 *mat, const t_vec4 *vec)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		out->v[i] = 0.0f;
		j = 0;
		while (j < 4)
		{
			out->v[i] += mat->m[i][j] * vec->v[j];
			j++;
		}
		i++;
	}
}
