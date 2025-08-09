/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub_theme2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:59:29 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 16:59:46 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	palette_5_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	set_idx(fdf, 4);
}

void	palette_6_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	set_idx(fdf, 5);
}

void	palette_7_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	set_idx(fdf, 6);
}

void	palette_8_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	set_idx(fdf, 7);
}

void	palette_9_handler(t_app *fdf, int keycode, void *data)
{
	(void)keycode;
	(void)data;
	set_idx(fdf, 8);
}
