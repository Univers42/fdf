/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_param_event.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:23:49 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 15:25:20 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

int	mlx_int_param_undef()
{
}

/**
 * @brief Handles KeyPress events for MiniLibX windows.
 *
 * Calls the registered KeyPress hook with the keysym and user parameter.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param ev Pointer to the XEvent structure.
 * @param win Pointer to the window structure.
 * @return Always returns 0.
 */
int	mlx_int_param_KeyPress(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
  win->hooks[KeyPress].hook(XkbKeycodeToKeysym(xvar->display,
					       ev->xkey.keycode, 0, 0),
			    win->hooks[KeyPress].param);
}

/**
 * @brief Handles KeyRelease events for MiniLibX windows.
 *
 * Calls the registered KeyRelease hook with the keysym and user parameter.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param ev Pointer to the XEvent structure.
 * @param win Pointer to the window structure.
 * @return Always returns 0.
 */
int	mlx_int_param_KeyRelease(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
  win->hooks[KeyRelease].hook(XkbKeycodeToKeysym(xvar->display,
						 ev->xkey.keycode, 0, 0),
			      win->hooks[KeyRelease].param);
}

/**
 * @brief Handles ButtonPress events for MiniLibX windows.
 *
 * Calls the registered ButtonPress hook with button, x, y, and user parameter.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param ev Pointer to the XEvent structure.
 * @param win Pointer to the window structure.
 * @return Always returns 0.
 */
int	mlx_int_param_ButtonPress(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
  win->hooks[ButtonPress].hook(ev->xbutton.button,ev->xbutton.x,ev->xbutton.y,
			       win->hooks[ButtonPress].param);
}

/**
 * @brief Handles ButtonRelease events for MiniLibX windows.
 *
 * Calls the registered ButtonRelease hook with button, x, y, and user parameter.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param ev Pointer to the XEvent structure.
 * @param win Pointer to the window structure.
 * @return Always returns 0.
 */
int	mlx_int_param_ButtonRelease(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
  win->hooks[ButtonRelease].hook(ev->xbutton.button,
				 ev->xbutton.x, ev->xbutton.y,
				 win->hooks[ButtonRelease].param);
}

/**
 * @brief Handles MotionNotify events for MiniLibX windows.
 *
 * Calls the registered MotionNotify hook with x, y, and user parameter.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param ev Pointer to the XEvent structure.
 * @param win Pointer to the window structure.
 * @return Always returns 0.
 */
int	mlx_int_param_MotionNotify(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
  win->hooks[MotionNotify].hook(ev->xbutton.x,ev->xbutton.y,
				win->hooks[MotionNotify].param);
}

/**
 * @brief Handles Expose events for MiniLibX windows.
 *
 * Calls the registered Expose hook if this is the last expose event.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param ev Pointer to the XEvent structure.
 * @param win Pointer to the window structure.
 * @return Always returns 0.
 */
int	mlx_int_param_Expose(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
  if (!ev->xexpose.count)
    win->hooks[Expose].hook(win->hooks[Expose].param);
}

/**
 * @brief Handles generic X11 events for MiniLibX windows.
 *
 * This function calls the registered hook for the event type, passing the user parameter.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param ev Pointer to the XEvent structure.
 * @param win Pointer to the window structure.
 * @return Always returns 0.
 */
int	mlx_int_param_generic(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
  win->hooks[ev->type].hook(win->hooks[ev->type].param);
}

/**
 * @brief Array of event handler functions for MiniLibX.
 *
 * This array maps X11 event types to their corresponding handler functions.
 * It is used to dispatch events to the correct handler based on event type.
 */
int	(*(mlx_int_param_event[]))() =
{
  mlx_int_param_undef,   /* 0 */
  mlx_int_param_undef,
  mlx_int_param_KeyPress,
  mlx_int_param_KeyRelease,  /* 3 */
  mlx_int_param_ButtonPress,
  mlx_int_param_ButtonRelease,
  mlx_int_param_MotionNotify,  /* 6 */
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_Expose,   /* 12 */
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic,
  mlx_int_param_generic
};
