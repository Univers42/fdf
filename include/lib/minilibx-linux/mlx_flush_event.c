/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_flush_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:34:22 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 14:34:37 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

/**
 * @brief Flushes all pending X11 events from the MiniLibX display queue.
 *
 * This function removes and discards all pending events from the X11 event queue
 * for the given display context, ensuring that no events remain to be processed.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @return Always returns 0.
 */
int	mlx_flush_event(t_xvar *xvar)
{
  XEvent	ev;

  while (XPending(xvar->display))
  {
     XNextEvent(xvar->display,&ev);
  }
}
