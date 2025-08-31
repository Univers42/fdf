/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_anti_resize_win.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:22:05 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 15:22:06 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

/**
 * @brief Prevents a MiniLibX window from being resized.
 *
 * This function sets the window manager hints to fix the window size,
 * so the user cannot resize the window. It sets the minimum and maximum
 * width and height to the specified values.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param win The X11 window to restrict resizing.
 * @param w Desired window width.
 * @param h Desired window height.
 * @return Always returns 0.
 */
int	mlx_int_anti_resize_win(t_xvar *xvar,Window win,int w,int h)
{
  XSizeHints    hints;
  long          toto;

  memset(&hints, 0, sizeof(XSizeHints));
  toto = 0;
  XGetWMNormalHints(xvar->display,win,&hints,&toto);
  hints.width = w;
  hints.height = h;
  hints.min_width = w;
  hints.min_height = h;
  hints.max_width = w;
  hints.max_height = h;
  hints.flags = PPosition | PSize | PMinSize | PMaxSize;
  XSetWMNormalHints(xvar->display,win,&hints);
}
