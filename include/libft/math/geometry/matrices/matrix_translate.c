/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_translate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:38:22 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 14:08:19 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"

/*
** Sets the matrix to a translation transformation by (tx, ty, tz).
** Usage: matrix_translate(&mat, tx, ty, tz);
** Expects: Pointer to a valid t_mat4.
*/

void	matrix_translate(t_mat4 *out, t_fpoint3 t)
{
	matrix_identity(out);
	out->m[0][3] = t.x;
	out->m[1][3] = t.y;
	out->m[2][3] = t.z;
}
