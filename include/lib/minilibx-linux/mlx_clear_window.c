/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_clear_window.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:30:34 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 14:30:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

/**
 * @brief Clears the contents of the specified window.
 *
 * This function erases all drawings in the given window, making it blank.
 * It uses the X11 XClearWindow function to clear the window's display area.
 * If the display requires flushing, it calls XFlush to update the window immediately.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param win Pointer to the window to be cleared.
 * @return Always returns 0.
 */
int		mlx_clear_window(t_xvar *xvar,t_win_list *win)
{
  XClearWindow(xvar->display,win->window);
  if (xvar->do_flush)
    XFlush(xvar->display);
}
