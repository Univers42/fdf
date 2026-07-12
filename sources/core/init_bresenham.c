/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bresenham.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 01:46:41 by dlesieur          #+#    #+#             */
/*   Updated: 2025/09/01 08:34:52 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/**
 * @brief Initializes the Bresenham state for line drawing between two
 * projected points (colors are set by the caller).
 *
 * The transformed points are in normalized device coordinates [-1,1],
 * mapped here to screen pixels. Depth (z) is not rasterized, so no
 * per-edge depth conversion is done.
 *
 * @param b Pointer to the Bresenham state structure to initialize.
 * @param fdf Pointer to the main application structure.
 * @param i0 Flat index of the first endpoint.
 * @param i1 Flat index of the second endpoint.
 */
void	bresenham_init(t_bresenham_state *b, t_fpoint4 *p1, t_fpoint4 *p2)
{
	b->p1[0] = ndc_to_screen_x(p1->x);
	b->p1[1] = ndc_to_screen_y(p1->y);
	b->p2[0] = ndc_to_screen_x(p2->x);
	b->p2[1] = ndc_to_screen_y(p2->y);
	init_deltas(b);
}

/**
 * @brief Initializes Bresenham deltas and color interpolation values.
 *
 * Computes the absolute deltas for each axis and sets up
 the step direction
 * and color channel differences for interpolation.
 *
 * @param b Pointer to the Bresenham state struct.
 */
void	init_deltas(t_bresenham_state *b)
{
	b->delta[0] = b->p2[0] - b->p1[0];
	b->delta[1] = b->p2[1] - b->p1[1];
	b->step[0] = 1;
	b->step[1] = 1;
	if (b->delta[0] < 0)
		b->step[0] = -1;
	if (b->delta[1] < 0)
		b->step[1] = -1;
	b->delta[0] = ft_abs(b->delta[0]);
	b->delta[1] = ft_abs(b->delta[1]);
}

#define RECIP_MAX 4096

/*
 * recip_q32[s] = 2^32 / s, so x / s == (x * recip_q32[s]) >> 32.
 * Kills the three integer divisions per line (~70 cycles each edge);
 * lines longer than RECIP_MAX steps fall back to real division.
 */
static const uint64_t	*recip_tbl(void)
{
	static uint64_t	tbl[RECIP_MAX + 1];
	int				i;

	if (tbl[1] == 0)
	{
		i = 0;
		while (++i <= RECIP_MAX)
			tbl[i] = (1ULL << 32) / (uint64_t)i;
	}
	return (tbl);
}

static int32_t	cfx_step(int32_t diff, int steps, const uint64_t *recip)
{
	if (steps <= RECIP_MAX)
		return ((int32_t)(((int64_t)(diff << 20) * (int64_t)recip[steps])
			>> 32));
	return ((diff << 20) / steps);
}

/**
 * @brief Prepares 12.20 fixed-point color accumulators and per-step
 * increments so the draw loop interpolates c1 -> c2 with integer adds
 * only (no per-pixel float math, no clamping needed: the accumulator
 * stays between the two endpoint channels by construction).
 *
 * @param b Pointer to the Bresenham state structure.
 */
void	init_color_delta(t_bresenham_state *b)
{
	const uint64_t	*recip;
	int				steps;

	recip = recip_tbl();
	steps = b->delta[1];
	if (b->delta[0] >= b->delta[1])
		steps = b->delta[0];
	if (steps == 0)
		steps = 1;
	b->cfx[0] = (int32_t)((b->color1 >> 16 & 0xFF) << 20);
	b->cfx[1] = (int32_t)((b->color1 >> 8 & 0xFF) << 20);
	b->cfx[2] = (int32_t)((b->color1 & 0xFF) << 20);
	b->cfx_d[0] = cfx_step((int32_t)(b->color2 >> 16 & 0xFF)
			- (int32_t)(b->color1 >> 16 & 0xFF), steps, recip);
	b->cfx_d[1] = cfx_step((int32_t)(b->color2 >> 8 & 0xFF)
			- (int32_t)(b->color1 >> 8 & 0xFF), steps, recip);
	b->cfx_d[2] = cfx_step((int32_t)(b->color2 & 0xFF)
			- (int32_t)(b->color1 & 0xFF), steps, recip);
}
