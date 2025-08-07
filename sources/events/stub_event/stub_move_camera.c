/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub_move_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:23:44 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 23:37:32 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>
#include <stdio.h>
#include "mlx.h"

void	move_forward(t_app *fdf, float amount)
{
	trans_stack_translate(&fdf->trans_stack, 0, -amount, 0);
	fdf->trans_stack.dirty[M_TB] = true;
}

void	move_backward(t_app *fdf, float amount)
{
	trans_stack_translate(&fdf->trans_stack, 0, amount, 0);
	fdf->trans_stack.dirty[M_TB] = true;
}

void	move_left_internal(t_app *fdf, float amount)
{
	trans_stack_translate(&fdf->trans_stack, -amount, 0, 0);
	fdf->trans_stack.dirty[M_TB] = true;
}

void	move_right_internal(t_app *fdf, float amount)
{
	trans_stack_translate(&fdf->trans_stack, amount, 0, 0);
	fdf->trans_stack.dirty[M_TB] = true;
}
