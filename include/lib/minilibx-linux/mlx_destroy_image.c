/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_destroy_image.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:31:36 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 14:31:44 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

/**
 * @brief Destroys a MiniLibX image and frees associated resources.
 *
 * This function releases all memory and resources allocated for the given image,
 * including shared memory, X11 image structures, pixmaps, and graphics contexts.
 * If the display requires flushing, it calls XFlush to update the display.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param img Pointer to the image to be destroyed.
 * @return Always returns 0.
 */
int	mlx_destroy_image(t_xvar *xvar, t_img *img)
{
  if (img->type == MLX_TYPE_SHM_PIXMAP ||
      img->type == MLX_TYPE_SHM)
    {
      XShmDetach(xvar->display, &(img->shm));
      shmdt(img->shm.shmaddr);
      /* shmctl IPC_RMID already done */
    }
  XDestroyImage(img->image);  /* For image & shm-image. Also free img->data */
  XFreePixmap(xvar->display, img->pix);
  if (img->gc)
    XFreeGC(xvar->display, img->gc);
  free(img);
  if (xvar->do_flush)
    XFlush(xvar->display);
}
