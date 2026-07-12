/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_upscale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * Procedural backgrounds are computed at quarter resolution (16x fewer
 * sinf calls) and expanded here: each low-res row is widened once into
 * the frame, then the widened row is memcpy'd to the remaining
 * BG_SCALE-1 rows of the block. Total cost ~= one framebuffer write.
 */
static void	expand_row(const uint32_t *lo, uint32_t *hi)
{
	int			x;
	int			r;
	uint32_t	c;

	x = -1;
	while (++x < BG_W)
	{
		c = lo[x];
		r = -1;
		while (++r < BG_SCALE)
			hi[x * BG_SCALE + r] = c;
	}
}

void	bg_upscale(const uint32_t *lo, uint32_t *hi)
{
	int	y;
	int	r;

	y = -1;
	while (++y < BG_H)
	{
		expand_row(lo + y * BG_W, hi + (long)y * BG_SCALE * WIN_WIDTH);
		r = 0;
		while (++r < BG_SCALE)
			ft_memcpy(hi + ((long)y * BG_SCALE + r) * WIN_WIDTH,
				hi + (long)y * BG_SCALE * WIN_WIDTH,
				sizeof(uint32_t) * WIN_WIDTH);
	}
}
