/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_set_win_event_mask.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:25:58 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 15:26:07 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

/**
 * @brief Sets the event mask for all MiniLibX windows.
 *
 * This function iterates through the window list and updates the X11 event mask
 * for each window based on the registered hooks. It combines all event masks
 * and applies them using XChangeWindowAttributes.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @return Always returns 0.
 */
int	mlx_int_set_win_event_mask(t_xvar *xvar)
{
  t_win_list	*win;
  int		mask;
  int		i;
  XSetWindowAttributes	xwa;

  win = xvar->win_list;
  while (win)
    {
      xwa.event_mask = 0;
      i = MLX_MAX_EVENT;
      while (i--)
	xwa.event_mask |= win->hooks[i].mask;
      XChangeWindowAttributes(xvar->display, win->window, CWEventMask, &xwa);
      win = win->next;
    }
}
