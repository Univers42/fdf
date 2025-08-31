/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:42:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 15:42:26 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

/**
 * @brief Sets the mouse button press event hook for a MiniLibX window.
 *
 * This function registers a callback to be called when the window receives
 * a mouse button press event. The callback function and its parameter are stored
 * in the window's hook structure.
 *
 * @param win Pointer to the MiniLibX window structure.
 * @param funct Function pointer to the mouse button press event handler.
 * @param param Pointer to user data to be passed to the handler.
 * @return Always returns 0.
 */
int		mlx_mouse_hook(t_win_list *win,int (*funct)(),void *param)
{
  win->hooks[ButtonPress].hook = funct;
  win->hooks[ButtonPress].param = param;
  win->hooks[ButtonPress].mask = ButtonPressMask;
}
