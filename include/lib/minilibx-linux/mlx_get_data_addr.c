/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_get_data_addr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:35:37 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 14:35:45 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

/**
 * @brief Retrieves the address and metadata of the image pixel data.
 *
 * This function returns a pointer to the raw pixel data of the given image,
 * and fills out the bits per pixel, line size, and endian information.
 *
 * @param img Pointer to the MiniLibX image structure.
 * @param bits_per_pixel Pointer to store the number of bits per pixel.
 * @param size_line Pointer to store the number of bytes in a row of the image.
 * @param endian Pointer to store the endianess of the image data.
 * @return Pointer to the image pixel data.
 */
char	*mlx_get_data_addr(t_img *img,int *bits_per_pixel,
			   int *size_line,int *endian)
{
  *bits_per_pixel = img->bpp;
  *size_line = img->size_line;
  *endian = img->image->byte_order;
  return (img->data);
}
