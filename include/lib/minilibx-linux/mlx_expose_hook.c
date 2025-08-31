/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_expose_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:32:52 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 14:33:03 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

/**
 * @brief Sets the expose event hook for a MiniLibX window.
 *
 * This function registers a callback to be called when the window receives
 * an expose event (such as being uncovered or redrawn). The callback function
 * and its parameter are stored in the window's hook structure.
 *
 * @param win Pointer to the MiniLibX window structure.
 * @param funct Function pointer to the expose event handler.
 * @param param Pointer to user data to be passed to the handler.
 * @return Always returns 0.
 */
int		mlx_expose_hook(t_win_list *win,int (*funct)(),void *param)
{
  win->hooks[Expose].hook = funct;
  win->hooks[Expose].param = param;
  win->hooks[Expose].mask = ExposureMask;
}
