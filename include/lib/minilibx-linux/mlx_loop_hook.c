/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:40:48 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 15:41:01 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

/**
 * @brief Sets the main loop hook for the MiniLibX display context.
 *
 * This function registers a callback to be called on each iteration of the main event loop.
 * The callback function and its parameter are stored in the display context.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param funct Function pointer to the loop handler.
 * @param param Pointer to user data to be passed to the handler.
 * @return Always returns 0.
 */
int	mlx_loop_hook(t_xvar *xvar,int (*funct)(),void *param)
{
  xvar->loop_hook = funct;
  xvar->loop_param = param;
}
