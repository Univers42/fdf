/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:41:08 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/21 15:42:02 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	color_interp_t(const t_bresenham_state *bs, int step)
{
	float	den;
	float	t;

	if (!bs)
		return (0.0f);
	den = (float)bs->delta[0];
	if ((float)bs->delta[1] > den)
		den = (float)bs->delta[1];
	if (den <= 0.0f)
		t = 0.0f;
	else
		t = (float)step / den;
	if (t < 0.0f)
		t = 0.0f;
	if (t > 1.0f)
		t = 1.0f;
	return (t);
}
