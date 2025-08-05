/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_rotation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:07 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:26:08 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

void	transformation_stack_rotate_x(t_transformation_stack *t, float dx)
{
	t->dirty[M_ROTATION_X] = true;
	t->rx += dx;
}

void	transformation_stack_rotate_y(t_transformation_stack *t, float dy)
{
	t->dirty[M_ROTATION_Y] = true;
	t->ry += dy;
}

void	transformation_stack_rotate_z(t_transformation_stack *t, float dz)
{
	t->dirty[M_ROTATION_Z] = true;
	t->rz += dz;
}
