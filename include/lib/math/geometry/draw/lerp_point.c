/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:00:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 02:06:24 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pixel.h"
#include "algebra.h"

// Interpolate between two points
void	lerp_point(t_point *result, const t_point *a, const t_point *b, float t)
{
	result->axis[X] = lerp(a->axis[X], b->axis[X], t);
	result->axis[Y] = lerp(a->axis[Y], b->axis[Y], t);
	result->axis[Z] = lerp(a->axis[Z], b->axis[Z], t);
	result->color = a->color;
	result->color.hex_color = a->color.hex_color;
	result->paint = a->paint;
	result->polar[LAT] = lerp(a->polar[LAT], b->polar[LAT], t);
	result->polar[LONG] = lerp(a->polar[LONG], b->polar[LONG], t);
}
