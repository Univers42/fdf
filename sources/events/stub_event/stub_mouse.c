/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:29:14 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 23:34:47 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>
#include <stdio.h>
#include "mlx.h"

void	mouse_right(t_app *fdf, int keycode, void *data)
{
	(void)fdf;
	(void)keycode;
	(void)data;
	printf("Right mouse button event\n");
}

void	mouse_left(t_app *fdf, int keycode, void *data)
{
	(void)fdf;
	(void)keycode;
	(void)data;
	printf("Left mouse button event\n");
}

void	scroll_mouse(t_app *fdf, int keycode, void *data)
{
	(void)fdf;
	(void)keycode;
	(void)data;
	printf("Mouse scroll event\n");
}
