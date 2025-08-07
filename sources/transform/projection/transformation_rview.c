/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_rview.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:11 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 23:03:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	trans_stack_rview_x(t_trans_stack *t, float dx)
{
	t->dirty[M_VIEW_ROTATE_X] = true;
	t->px += dx;
}

void	trans_stack_rview_x2(t_trans_stack *t, float dx)
{
	t->dirty[M_VIEW_ROTATE_X2] = true;
	t->px2 += dx;
}

void	trans_stack_rview_z(t_trans_stack *t, float dz)
{
	t->dirty[M_VIEW_ROTATE_Z] = true;
	t->pz += dz;
}
