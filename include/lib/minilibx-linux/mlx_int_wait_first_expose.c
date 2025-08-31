/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_wait_first_expose.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:27:34 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 15:28:08 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"


/**
 * @brief Waits for the first expose event on a MiniLibX window.
 *
 * This function blocks until the specified window receives an expose event,
 * then puts the event back into the event queue for normal processing.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param win The X11 window to wait for an expose event.
 * @return Always returns 0.
 */
int	mlx_int_wait_first_expose(t_xvar *xvar,Window win)
{
  XEvent	ev;

  XWindowEvent(xvar->display,win,ExposureMask,&ev);
  XPutBackEvent(xvar->display,&ev);
}
