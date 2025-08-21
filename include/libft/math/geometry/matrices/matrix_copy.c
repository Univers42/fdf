/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:38:02 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 02:10:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"

/*
** Copies the contents of a 4x4 matrix from src to dst.
** Usage: matrix_copy(&dst, &src);
** Expects: Both pointers are valid and non-NULL.
*/

void	matrix_copy(t_mat4 *dst, const t_mat4 *src)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			dst->m[i][j] = src->m[i][j];
			j++;
		}
		i++;
	}
}
