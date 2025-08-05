/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_projection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:03 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:26:04 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <math.h>

#include "fdf.h"
#define ISOMETRIC_ANGLE 0.6155f

void	transformation_stack_isometric(t_transformation_stack *t)
{
	t->px = 0;
	t->px2 = 0;
	t->pz = 0;
	t->rx = 0;
	t->ry = 0;
	t->rz = 0;
	transformation_stack_rview_z(t, M_PI_4);
	transformation_stack_rview_x(t, M_PI_2);
	transformation_stack_rview_x2(t, -ISOMETRIC_ANGLE);
	transformation_stack_rotate_x(t, 0);
	transformation_stack_rotate_y(t, 0);
	transformation_stack_rotate_z(t, 0);
}

void	transformation_stack_parallel(t_transformation_stack *t)
{
	t->px = 0;
	t->px2 = 0;
	t->pz = 0;
	t->rx = 0;
	t->ry = 0;
	t->rz = 0;
	transformation_stack_rview_z(t, 0);
	transformation_stack_rview_x(t, 0);
	transformation_stack_rview_x2(t, 0);
	transformation_stack_rotate_x(t, 0);
	transformation_stack_rotate_y(t, 0);
	transformation_stack_rotate_z(t, 0);
}
