/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_get_color_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:34:54 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 14:35:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

/**
 * @brief Converts a given color value to the appropriate pixel value for the display.
 *
 * This function adapts the input color to the display's color depth and format.
 * For displays with 24 bits or more, it returns the color unchanged.
 * For lower depths, it maps the color to the closest available pixel value using XColor.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param color The color value to convert.
 * @return The pixel value suitable for the display.
 */
int             mlx_get_color_value(t_xvar *xvar,int color)
{
  return(mlx_int_get_good_color(xvar,color));
}

/**
 * @brief Converts a color value to the closest pixel value for the display.
 *
 * This function adapts the input color to the display's color depth and format.
 * For displays with 24 bits or more, it returns the color unchanged.
 * For lower depths, it maps the color to the closest available pixel value using XColor
 * and the display's RGB decomposition.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @param color The color value to convert.
 * @return The pixel value suitable for the display.
 */
int		mlx_int_get_good_color(t_xvar *xvar,int color)
{
  XColor	xc;

  if (xvar->depth>=24)
    return (color);
  xc.red = (color>>8)&0xFF00;
  xc.green = color&0xFF00;
  xc.blue = (color<<8)&0xFF00;
  xc.pixel = ((xc.red>>(16-xvar->decrgb[1]))<<xvar->decrgb[0])+
    ((xc.green>>(16-xvar->decrgb[3]))<<xvar->decrgb[2])+
    ((xc.blue>>(16-xvar->decrgb[5]))<<xvar->decrgb[4]);
  return (xc.pixel);
}
