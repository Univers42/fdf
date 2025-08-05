/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_event2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 01:09:09 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/06 01:09:16 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Rotate the model down (around X axis)
void	rotate_down(t_app *fdf, float angle)
{
	transformation_stack_rotate_x(&fdf->transformation_stack, angle);
}

// Rotate the model left (around Y axis)
void	rotate_left(t_app *fdf, float angle)
{
	transformation_stack_rotate_y(&fdf->transformation_stack, -angle);
}

// Rotate the model right (around Y axis)
void	rotate_right(t_app *fdf, float angle)
{
	transformation_stack_rotate_y(&fdf->transformation_stack, angle);
}
