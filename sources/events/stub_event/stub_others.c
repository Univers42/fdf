/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub_others.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 02:19:25 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>
#include <stdio.h>
#include "mlx.h"

void	exit_prog(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	ft_printf("Goodbye!\n");
	mlx_loop_end(fdf->mlx);
}

void	auto_rotate(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	fdf->auto_rotate = !fdf->auto_rotate;
	if (fdf->auto_rotate)
		ft_printf("Auto-rotation ON\n");
	else
		ft_printf("Auto-rotation OFF\n");
}

void	dance_toggle_handler(t_app *fdf, int keycode, void *data)
{
	(void)fdf;
	(void)keycode;
	(void)data;
	dance_system_toggle();
}

void	dynamic_background_toggle_handler(t_app *fdf, int keycode, void *data)
{
	(void)fdf;
	(void)keycode;
	(void)data;
	dynamic_background_toggle();
}

void	texture_toggle_handler(t_app *fdf, int keycode, void *data)
{
	(void)fdf;
	(void)keycode;
	(void)data;
	texture_system_toggle();
}
