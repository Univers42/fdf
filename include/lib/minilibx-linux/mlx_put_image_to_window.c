/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_image_to_window.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:46:13 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 15:46:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

/**
 * @brief Puts an image onto a MiniLibX window at the specified coordinates.
 *
 * Handles shared memory and standard XImage types, sets the graphics context,
 * and copies the image to the window. Flushes the display if required.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param win Pointer to the MiniLibX window structure.
 * @param img Pointer to the image structure.
 * @param x X coordinate in the window.
 * @param y Y coordinate in the window.
 * @return Always returns 0.
 */
int	mlx_put_image_to_window(t_xvar *xvar,t_win_list *win,t_img *img,
				int x,int y)
{
  GC	gc;

  gc = win->gc;
  if (img->gc)
    {
      gc = img->gc;
      XSetClipOrigin(xvar->display, gc, x, y);
    }
  if (img->type==MLX_TYPE_SHM)
    XShmPutImage(xvar->display,img->pix, win->gc, img->image,0,0,0,0,
		 img->width,img->height,False);
  if (img->type==MLX_TYPE_XIMAGE)
    XPutImage(xvar->display,img->pix, win->gc, img->image,0,0,0,0,
	      img->width,img->height);
  XCopyArea(xvar->display,img->pix,win->window, gc,
	    0,0,img->width,img->height,x,y);
  if (xvar->do_flush)
    XFlush(xvar->display);
}
