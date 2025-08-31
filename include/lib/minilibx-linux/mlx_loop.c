/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:41:14 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 15:41:49 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

extern int	(*(mlx_int_param_event[]))();

/**
 * @brief Returns the number of active MiniLibX windows.
 *
 * Iterates through the window list and counts the windows.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @return Number of windows.
 */
static int	win_count(t_xvar *xvar)
{
	int			i;
	t_win_list	*win;

	i = 0;
	win = xvar->win_list;
	while (win)
	{
		win = win->next;
		++i;
	}
	return (i);
}

/**
 * @brief Signals the main loop to end.
 *
 * Sets the end_loop flag in the display context.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @return Always returns 1.
 */
int			mlx_loop_end(t_xvar *xvar)
{
	xvar->end_loop = 1;
	return (1);
}

/**
 * @brief Runs the MiniLibX main event loop.
 *
 * Processes X11 events for all windows, dispatches event hooks, and calls the loop hook.
 * The loop continues until there are no windows or end_loop is set.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @return Always returns 0.
 */
int			mlx_loop(t_xvar *xvar)
{
	XEvent		ev;
	t_win_list	*win;

	mlx_int_set_win_event_mask(xvar);
	xvar->do_flush = 0;
	while (win_count(xvar) && !xvar->end_loop)
	{
		while (!xvar->end_loop && (!xvar->loop_hook || XPending(xvar->display)))
		{
			XNextEvent(xvar->display,&ev);
			win = xvar->win_list;
			while (win && (win->window!=ev.xany.window))
				win = win->next;

			if (win && ev.type == ClientMessage && ev.xclient.message_type == xvar->wm_protocols && ev.xclient.data.l[0] == xvar->wm_delete_window && win->hooks[DestroyNotify].hook)
				win->hooks[DestroyNotify].hook(win->hooks[DestroyNotify].param);
			if (win && ev.type < MLX_MAX_EVENT && win->hooks[ev.type].hook)
				mlx_int_param_event[ev.type](xvar, &ev, win);
		}
		XSync(xvar->display, False);
		if (xvar->loop_hook)
			xvar->loop_hook(xvar->loop_param);
	}
	return (0);
}
