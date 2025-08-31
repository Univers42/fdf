/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:36:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 15:17:40 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

/**
 * @brief Registers an event hook for a MiniLibX window.
 *
 * This function sets a callback for a specific X11 event type on the given window.
 * The callback function, its parameter, and the event mask are stored in the window's hook structure.
 *
 * @param win Pointer to the MiniLibX window structure.
 * @param x_event The X11 event type to hook.
 * @param x_mask The event mask for the hook.
 * @param funct Function pointer to the event handler.
 * @param param Pointer to user data to be passed to the handler.
 * @return Always returns 0.
 */
int	mlx_hook(t_win_list *win, int x_event, int x_mask, 
		 int (*funct)(),void *param)
{
  win->hooks[x_event].hook = funct;
  win->hooks[x_event].param = param;
  win->hooks[x_event].mask = x_mask;
}

/**
 * @brief Disables keyboard auto-repeat for the display.
 *
 * This function turns off the auto-repeat feature for keyboard input on the given display context.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @return Always returns 0.
 */
int	mlx_do_key_autorepeatoff(t_xvar *xvar)
{
  XAutoRepeatOff(xvar->display);
}

/**
 * @brief Enables keyboard auto-repeat for the display.
 *
 * This function turns on the auto-repeat feature for keyboard input on the given display context.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @return Always returns 0.
 */
int	mlx_do_key_autorepeaton(t_xvar *xvar)
{
  XAutoRepeatOn(xvar->display);
}

/**
 * @brief Synchronizes the X11 display.
 *
 * This function flushes the X11 output buffer and waits until all requests have been processed.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @return Always returns 0.
 */
int	mlx_do_sync(t_xvar *xvar)
{
  XSync(xvar->display, False);
}
