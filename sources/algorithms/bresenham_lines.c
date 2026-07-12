/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline uint32_t	cfx_pack(const int32_t c[3])
{
	return (((uint32_t)(c[0] >> 20) << 16)
		| ((uint32_t)(c[1] >> 20) << 8)
		| (uint32_t)(c[2] >> 20));
}

/*
 * Solid-color variant: both endpoints share one color (no gradient),
 * so the loop is a bare pointer-stepping Bresenham.
 */
void	line_fast_solid(t_bresenham_ctx *ctx)
{
	t_bresenham_state	*b;
	unsigned int		*p;
	long				adv[2];
	int					step;

	b = ctx->bresenham;
	p = ctx->screen + (long)ctx->coord[1] * WIN_WIDTH + ctx->coord[0];
	adv[0] = b->step[0];
	adv[1] = (long)b->step[1] * WIN_WIDTH;
	step = -1;
	while (++step <= ctx->limit)
	{
		*p = b->color1;
		p += adv[ctx->major_axis];
		b->error_count += 2 * b->delta[1 - ctx->major_axis];
		if (b->error_count > 0)
		{
			p += adv[1 - ctx->major_axis];
			b->error_count -= 2 * b->delta[ctx->major_axis];
		}
	}
}

/*
 * Fast path: both endpoints inside the viewport, so every pixel of the
 * line is too (Bresenham never leaves the endpoints' bounding box).
 * Pure pointer stepping, no bounds test, no multiply per pixel.
 */
void	line_fast(t_bresenham_ctx *ctx)
{
	t_bresenham_state	*b;
	unsigned int		*p;
	long				adv[2];
	int					step;

	b = ctx->bresenham;
	p = ctx->screen + (long)ctx->coord[1] * WIN_WIDTH + ctx->coord[0];
	adv[0] = b->step[0];
	adv[1] = (long)b->step[1] * WIN_WIDTH;
	step = -1;
	while (++step <= ctx->limit)
	{
		*p = cfx_pack(b->cfx);
		p += adv[ctx->major_axis];
		b->error_count += 2 * b->delta[1 - ctx->major_axis];
		if (b->error_count > 0)
		{
			p += adv[1 - ctx->major_axis];
			b->error_count -= 2 * b->delta[ctx->major_axis];
		}
		b->cfx[0] += b->cfx_d[0];
		b->cfx[1] += b->cfx_d[1];
		b->cfx[2] += b->cfx_d[2];
	}
}

void	line_guarded(t_bresenham_ctx *ctx)
{
	t_bresenham_state	*b;
	int					step;

	b = ctx->bresenham;
	step = -1;
	while (++step <= ctx->limit)
	{
		if ((unsigned int)ctx->coord[0] < WIN_WIDTH
			&& (unsigned int)ctx->coord[1] < WIN_HEIGHT)
			ctx->screen[(long)ctx->coord[1] * WIN_WIDTH
				+ ctx->coord[0]] = cfx_pack(b->cfx);
		ctx->coord[ctx->major_axis] += b->step[ctx->major_axis];
		b->error_count += 2 * b->delta[1 - ctx->major_axis];
		if (b->error_count > 0)
		{
			ctx->coord[1 - ctx->major_axis] += b->step[1 - ctx->major_axis];
			b->error_count -= 2 * b->delta[ctx->major_axis];
		}
		b->cfx[0] += b->cfx_d[0];
		b->cfx[1] += b->cfx_d[1];
		b->cfx[2] += b->cfx_d[2];
	}
}
