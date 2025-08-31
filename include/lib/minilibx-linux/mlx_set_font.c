/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_set_font.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:47:25 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 15:47:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

/*
** Allows to specify the font that will be used by mlx_string_put.
**
** Note: only fixed-width bitmap fonts are supported by Xlib, refer to xfontsel
** utility to get valid font names for this function.
*/

/**
 * @brief Sets the font for text rendering in a MiniLibX window.
 *
 * Allows specifying the font to be used by mlx_string_put. Only fixed-width bitmap fonts
 * are supported by Xlib. Use the xfontsel utility to get valid font names.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param win Pointer to the MiniLibX window structure.
 * @param name Name of the font to load.
 */
void	mlx_set_font(t_xvar *xvar, t_win_list *win, char *name)
{
	static Font		font = 0;

	if (font)
		XUnloadFont(xvar->display, font);
	font = XLoadFont(xvar->display, name);
	XSetFont(xvar->display, win->gc, font);
}
