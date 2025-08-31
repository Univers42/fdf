/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_destroy_display.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 18:56:35 by mg                #+#    #+#             */
/*   Updated: 2025/08/31 14:31:09 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

/**
 * @brief Destroys the MiniLibX display and releases associated resources.
 *
 * This function closes the X11 display connection used by MiniLibX,
 * freeing all resources allocated for the display context.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @return Always returns 0.
 */
int	mlx_destroy_display(t_xvar *xvar)
{
	XCloseDisplay(xvar->display);
}
