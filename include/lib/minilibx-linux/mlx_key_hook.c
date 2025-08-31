/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:39:17 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 15:39:35 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

/**
 * @brief Sets the key release event hook for a MiniLibX window.
 *
 * This function registers a callback to be called when the window receives
 * a key release event. The callback function and its parameter are stored
 * in the window's hook structure.
 *
 * @param win Pointer to the MiniLibX window structure.
 * @param funct Function pointer to the key release event handler.
 * @param param Pointer to user data to be passed to the handler.
 * @return Always returns 0.
 */
int		mlx_key_hook(t_win_list *win,int (*funct)(),void *param)
{
  win->hooks[KeyRelease].hook = funct;
  win->hooks[KeyRelease].param = param;
  win->hooks[KeyRelease].mask = KeyReleaseMask;
}
