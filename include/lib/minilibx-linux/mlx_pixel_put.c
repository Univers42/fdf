/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:45:38 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 15:46:01 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

/**
 * @brief Draws a pixel at the specified coordinates in a MiniLibX window.
 *
 * Sets the foreground color of the graphics context, draws the point, and flushes
 * the display if required.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param win Pointer to the MiniLibX window structure.
 * @param x X coordinate of the pixel.
 * @param y Y coordinate of the pixel.
 * @param color Color value of the pixel.
 * @return Always returns 0.
 */
int		mlx_pixel_put(t_xvar *xvar,t_win_list *win,
			      int x,int y,int color)
{
   XGCValues	xgcv;
   
   xgcv.foreground = mlx_int_get_good_color(xvar,color);
   XChangeGC(xvar->display,win->gc,GCForeground,&xgcv);
   XDrawPoint(xvar->display,win->window,win->gc,x,y);
   if (xvar->do_flush)
     XFlush(xvar->display);
}
