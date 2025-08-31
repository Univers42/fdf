/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_destroy_window.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:32:25 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 14:32:26 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

/**
 * @brief Destroys a MiniLibX window and frees associated resources.
 *
 * This function removes the specified window from the internal window list,
 * destroys the X11 window and graphics context, frees memory, and flushes
 * the display if required.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param win Pointer to the window to be destroyed.
 * @return Always returns 0.
 */
int	mlx_destroy_window(t_xvar *xvar,t_win_list *win)
{
  t_win_list	*w;
  t_win_list	*prev;
  t_win_list	first;

  first.next = xvar->win_list;
  prev = &first;
  w = prev->next;
  while (w)
    {
      if (w==win)
	prev->next = w->next;
      else
	prev = w;
      w = w->next;
    }
  xvar->win_list = first.next;
  XDestroyWindow(xvar->display,win->window);
  XFreeGC(xvar->display,win->gc);
  free(win);
  if (xvar->do_flush)
    XFlush(xvar->display);
}
