/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub_theme2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:30:53 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 23:53:59 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>
#include <stdio.h>
#include "mlx.h"
#include "theme.h"

void	palette_6_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	set_palette_index(5, fdf);
	ft_printf("Color Palette 6: Sunset\n");
}

void	palette_7_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	set_palette_index(6, fdf);
	ft_printf("Color Palette 7: Matrix/Neon Green\n");
}

void	palette_8_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	set_palette_index(7, fdf);
	ft_printf("Color Palette 8: Fire/Lava\n");
}

void	palette_9_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	set_palette_index(8, fdf);
	ft_printf("Color Palette 9: Ice/Arctic\n");
}
