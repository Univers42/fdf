/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:08:16 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 02:05:56 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pixel.h"

/*
*	Acording the z value of the point and de max and min values of the map
*	this function set the color needed of the point received.
*	All the colors are defined in pixel.h of course in a future a callback
*   function will be integrated to change those values and override the colors
*   As the user would wish
*/
void	load_color(int max, int min, t_point *point, t_colors colors)
{
	point->paint = 1;
	point->color.hex_color = DEFAULT_COLOR;
	if (point->axis[Z] == max)
		point->color.hex_color = colors.topcolor;
	else if (point->axis[Z] == 0)
		point->color.hex_color = colors.groundcolor;
	else if (point->axis[Z] == min && min != 0)
		point->color.hex_color = colors.bottomcolor;
	else if (point->axis[Z] > 0)
		point->color.hex_color = gradient(colors.groundcolor, colors.topcolor,
				max, point->axis[Z]);
	else
		point->color.hex_color = gradient(colors.bottomcolor,
				colors.groundcolor,
				-min, - (min - point->axis[Z]));
}
