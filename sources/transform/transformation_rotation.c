/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_rotation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:07 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/06 04:02:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"
#include <stdio.h>
void	transformation_stack_rotate_x(t_transformation_stack *t, float dx)
{
	t->dirty[M_ROTATION_X] = true;
	t->rx += dx;
	
	// Force immediate matrix update
	identity_matrix4(t->matrices[M_ROTATION_X]);
	matrix4_rotate_x_abs(t->matrices[M_ROTATION_X], t->rx);
}

void	transformation_stack_rotate_y(t_transformation_stack *t, float dy)
{
	t->dirty[M_ROTATION_Y] = true;
	t->ry += dy;
	
	// Force immediate matrix update
	identity_matrix4(t->matrices[M_ROTATION_Y]);
	matrix4_rotate_y_abs(t->matrices[M_ROTATION_Y], t->ry);
}

void	transformation_stack_rotate_z(t_transformation_stack *t, float dz)
{
	t->dirty[M_ROTATION_Z] = true;
	t->rz += dz;
	
	// Force immediate matrix update
	identity_matrix4(t->matrices[M_ROTATION_Z]);
	matrix4_rotate_z_abs(t->matrices[M_ROTATION_Z], t->rz);
}
