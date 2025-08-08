/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub_move_orthodox.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:25:34 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>
#include <stdio.h>
#include "mlx.h"

void	move_up(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	ft_printf("BEFORE: tx=%.2f, ty=%.2f, tz=%.2f\n",
		fdf->trans_stack.tx, fdf->trans_stack.ty, fdf->trans_stack.tz);
	move_forward(fdf, 5.0f);
	trans_stack_update(&fdf->trans_stack);
	ft_printf("AFTER: tx=%.2f, ty=%.2f, tz=%.2f\n",
		fdf->trans_stack.tx, fdf->trans_stack.ty, fdf->trans_stack.tz);
	ft_printf("Matrix [3]=%.2f, [7]=%.2f, [11]=%.2f\n",
		fdf->trans_stack.matrices[M_TB][3],
		fdf->trans_stack.matrices[M_TB][7],
		fdf->trans_stack.matrices[M_TB][11]);
}

void	move_down(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	move_backward(fdf, 5.0f);
	trans_stack_update(&fdf->trans_stack);
}

void	move_left(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	move_left_internal(fdf, 5.0f);
	trans_stack_update(&fdf->trans_stack);
}

void	move_right(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	move_right_internal(fdf, 5.0f);
	trans_stack_update(&fdf->trans_stack);
}
