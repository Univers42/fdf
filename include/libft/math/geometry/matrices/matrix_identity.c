/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_identity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:38:07 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 14:17:54 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"

/*
** Sets the given 4x4 matrix to the identity matrix.
** Usage: matrix_identity(&mat);
** Expects: Pointer to a valid t_mat4.
*/

void	matrix_identity(t_mat4 *out)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (i == j)
				out->m[i][j] = 1.0f;
			else
				out->m[i][j] = 0.0f;
		}
	}
}
