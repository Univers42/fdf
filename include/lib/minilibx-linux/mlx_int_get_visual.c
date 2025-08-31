/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_get_visual.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:22:39 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 15:22:49 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"


/*
** We need a private colormap for non-default Visual.
*/

/**
 * @brief Selects a TrueColor visual for the MiniLibX display context.
 *
 * This function checks if the default visual is TrueColor. If not, it searches
 * for a TrueColor visual with the current depth and sets it in the display context.
 * If a non-default visual is used, it marks the need for a private colormap.
 *
 * @param xvar Pointer to the MiniLibX display context.
 * @return 0 on success, -1 if no TrueColor visual is found.
 */
int		mlx_int_get_visual(t_xvar *xvar)
{
  XVisualInfo	*vi;
  XVisualInfo	template;
  int		nb_item;

  xvar->private_cmap = 0;
  xvar->visual = DefaultVisual(xvar->display,xvar->screen);
  if (xvar->visual->class == TrueColor)
    return (0);
  template.class = TrueColor;
  template.depth = xvar->depth;
  if (!(vi = XGetVisualInfo(xvar->display,VisualDepthMask|VisualClassMask,
			    &template,&nb_item)) )
    return (-1);
  xvar->visual = vi->visual;
  xvar->private_cmap = 1;
  return (0);
}
