/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_screen_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:47:08 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 15:47:09 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

/**
 * @brief Gets the screen size of the root window.
 *
 * Retrieves the width and height of the screen associated with the MiniLibX display context.
 *
 * @param mlx_ptr Pointer to the MiniLibX display context (t_xvar).
 * @param sizex Pointer to store the screen width.
 * @param sizey Pointer to store the screen height.
 * @return Always returns 0.
 */
int		mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey)
{
	XWindowAttributes	xwAttr;
	Status				ret;
	t_xvar				*xvar;
	
	xvar = mlx_ptr;
	ret = XGetWindowAttributes(xvar->display, xvar->root, &xwAttr);
	(*sizex) = xwAttr.width;
	(*sizey) = xwAttr.height;
}
