/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub_rotate_internal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:26:28 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 23:35:09 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>
#include <stdio.h>
#include "mlx.h"

void	rotate_up_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	printf("ROTATE: Before rx=%.4f\n", fdf->trans_stack.rx);
	rotate_up(fdf, 0.1f);
	trans_stack_update(&fdf->trans_stack);
	printf("ROTATE: After rx=%.4f\n", fdf->trans_stack.rx);
}

void	rotate_down_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	rotate_down(fdf, 0.1f);
	trans_stack_update(&fdf->trans_stack);
}

void	rotate_left_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	rotate_left(fdf, 0.1f);
	trans_stack_update(&fdf->trans_stack);
}

void	rotate_right_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	rotate_right(fdf, 0.1f);
	trans_stack_update(&fdf->trans_stack);
}
