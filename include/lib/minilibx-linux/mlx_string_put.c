/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_string_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:47:39 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 15:48:16 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

/**
 * @brief Draws a string at the specified coordinates in a MiniLibX window.
 *
 * Sets the foreground color of the graphics context, draws the string, and flushes
 * the display if required.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param win Pointer to the MiniLibX window structure.
 * @param x X coordinate of the string.
 * @param y Y coordinate of the string.
 * @param color Color value of the string.
 * @param string The string to draw.
 * @return Always returns 0.
 */
int		mlx_string_put(t_xvar *xvar,t_win_list *win,
			       int x,int y,int color,char *string)
{
   XGCValues	xgcv;
   
   xgcv.foreground = mlx_int_get_good_color(xvar,color);
   XChangeGC(xvar->display,win->gc,GCForeground,&xgcv);
   XDrawString(xvar->display,win->window,win->gc,x,y,string,strlen(string));
   if (xvar->do_flush)
     XFlush(xvar->display);
}
