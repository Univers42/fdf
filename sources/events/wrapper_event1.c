/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_event1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 01:08:56 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/06 01:08:58 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Move the model forward (along Y axis)
void	move_forward(t_app *fdf, float amount)
{
	transformation_stack_translate(&fdf->transformation_stack, 0, -amount, 0);
}

// Move the model backward (along Y axis)
void	move_backward(t_app *fdf, float amount)
{
	transformation_stack_translate(&fdf->transformation_stack, 0, amount, 0);
}

// Move the model left (along X axis)
void	move_left(t_app *fdf, float amount)
{
	transformation_stack_translate(&fdf->transformation_stack, -amount, 0, 0);
}

// Move the model right (along X axis)
void	move_right(t_app *fdf, float amount)
{
	transformation_stack_translate(&fdf->transformation_stack, amount, 0, 0);
}

// Rotate the model up (around X axis)
void	rotate_up(t_app *fdf, float angle)
{
	transformation_stack_rotate_x(&fdf->transformation_stack, -angle);
}
