/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:42:58 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 15:43:26 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

/**
 * @brief Moves the mouse pointer to the specified coordinates in a MiniLibX window.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param win Pointer to the MiniLibX window structure.
 * @param x X coordinate to move the pointer to.
 * @param y Y coordinate to move the pointer to.
 * @return Always returns 0.
 */
int		mlx_mouse_move(t_xvar *xvar, t_win_list *win, int x, int y)
{
	XWarpPointer(xvar->display, None, win->window, 0, 0, 0, 0, x, y);
	return (0);
}

/**
 * @brief Hides the mouse pointer in a MiniLibX window.
 *
 * Creates a blank cursor and sets it for the specified window.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param win Pointer to the MiniLibX window structure.
 * @return Always returns 0.
 */
int		mlx_mouse_hide(t_xvar *xvar, t_win_list *win)
{
	static char data[1] = {0};
	Cursor cursor;
	Pixmap blank;
	XColor dummy;

	blank = XCreateBitmapFromData(xvar->display, win->window, data, 1, 1);
	cursor = XCreatePixmapCursor(xvar->display, blank, blank, &dummy, &dummy, 0, 0);
	XDefineCursor(xvar->display, win->window, cursor);
	XFreePixmap(xvar->display, blank);
	XFreeCursor(xvar->display, cursor);
}

/**
 * @brief Shows the mouse pointer in a MiniLibX window.
 *
 * Removes any custom cursor, restoring the default pointer.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param win Pointer to the MiniLibX window structure.
 * @return Always returns 0.
 */
int		mlx_mouse_show(t_xvar *xvar, t_win_list *win)
{
	XUndefineCursor(xvar->display, win->window);
}

/**
 * @brief Gets the mouse pointer position relative to a MiniLibX window.
 *
 * Queries the position of the mouse pointer relative to the origin of the
 * specified window and saves it to the provided location.
 * If the pointer is not on the same screen as the specified window, both
 * win_x_return and win_y_return are set to zero and the function returns 0.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param win Pointer to the MiniLibX window structure.
 * @param win_x_return Pointer to store the X coordinate.
 * @param win_y_return Pointer to store the Y coordinate.
 * @return Non-zero if pointer is on the same screen, 0 otherwise.
 */
int		mlx_mouse_get_pos(t_xvar *xvar, t_win_list *win, \
			int *win_x_return, int *win_y_return)
{
	Window		root_return;
	Window		child_return;
	int			root_x_return;
	int			root_y_return;
	unsigned	mask_return;

	return (XQueryPointer(xvar->display, win->window, \
		&root_return, &child_return, &root_x_return, &root_y_return, \
		win_x_return, win_y_return, &mask_return));
}
