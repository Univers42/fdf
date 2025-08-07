/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_rview.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:11 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:26:12 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

void	transformation_stack_rview_x(t_transformation_stack *t, float dx)
{
	t->dirty[M_VIEW_ROTATE_X] = true;
	t->px += dx;
}

void	transformation_stack_rview_x2(t_transformation_stack *t, float dx)
{
	t->dirty[M_VIEW_ROTATE_X2] = true;
	t->px2 += dx;
}

void	transformation_stack_rview_z(t_transformation_stack *t, float dz)
{
	t->dirty[M_VIEW_ROTATE_Z] = true;
	t->pz += dz;
}
