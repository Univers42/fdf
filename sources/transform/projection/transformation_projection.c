/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_projection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:03 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 23:03:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "fdf.h"
#define ISOMETRIC_ANGLE 0.6155f

void	trans_stack_isometric(t_trans_stack *t)
{
	t->px = 0;
	t->px2 = 0;
	t->pz = 0;
	t->rx = 0;
	t->ry = 0;
	t->rz = 0;
	trans_stack_rview_z(t, M_PI_4);
	trans_stack_rview_x(t, M_PI_2);
	trans_stack_rview_x2(t, -ISOMETRIC_ANGLE);
	trans_stack_rotate_x(t, 0);
	trans_stack_rotate_y(t, 0);
	trans_stack_rotate_z(t, 0);
}

void	trans_stack_parallel(t_trans_stack *t)
{
	t->px = 0;
	t->px2 = 0;
	t->pz = 0;
	t->rx = 0;
	t->ry = 0;
	t->rz = 0;
	trans_stack_rview_z(t, 0);
	trans_stack_rview_x(t, 0);
	trans_stack_rview_x2(t, 0);
	trans_stack_rotate_x(t, 0);
	trans_stack_rotate_y(t, 0);
	trans_stack_rotate_z(t, 0);
}
