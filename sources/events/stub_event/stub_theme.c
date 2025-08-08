/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub_theme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:30:06 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 23:53:58 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>
#include <stdio.h>
#include "mlx.h"
#include "theme.h"

void	palette_1_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	set_palette_index(0, fdf);
	ft_printf("Color Palette 1: Planet/Ocean theme\n");
}

void	palette_2_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	set_palette_index(1, fdf);
	ft_printf("Color Palette 2: Default theme\n");
}

void	palette_3_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	set_palette_index(2, fdf);
	ft_printf("Color Palette 3: Gamma Random V2\n");
}

void	palette_4_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	set_palette_index(3, fdf);
	ft_printf("Color Palette 4: Vibrant/Rainbow\n");
}

void	palette_5_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	set_palette_index(4, fdf);
	ft_printf("Color Palette 5: Grayscale\n");
}
