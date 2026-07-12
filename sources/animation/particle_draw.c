/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particle_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Classic alpha blend: dst + (src - dst) * a, per channel. */
static uint32_t	blend_px(uint32_t dst, uint32_t src, float a)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	r = (dst >> 16 & 0xFF) + (uint32_t)(a * ((float)(src >> 16 & 0xFF)
				- (float)(dst >> 16 & 0xFF)));
	g = (dst >> 8 & 0xFF) + (uint32_t)(a * ((float)(src >> 8 & 0xFF)
				- (float)(dst >> 8 & 0xFF)));
	b = (dst & 0xFF) + (uint32_t)(a * ((float)(src & 0xFF)
				- (float)(dst & 0xFF)));
	return ((r << 16) | (g << 8) | b);
}

/* Additive blend with saturation: light emitters (fire, sparks, stars). */
static uint32_t	add_px(uint32_t dst, uint32_t src, float a)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	r = (dst >> 16 & 0xFF) + (uint32_t)(a * (float)(src >> 16 & 0xFF));
	g = (dst >> 8 & 0xFF) + (uint32_t)(a * (float)(src >> 8 & 0xFF));
	b = (dst & 0xFF) + (uint32_t)(a * (float)(src & 0xFF));
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

/* Fire cools over its life: white-yellow core -> orange -> dark ember. */
uint32_t	fire_ramp(float t)
{
	if (t < 0.35f)
		return (lerp_color(0xFFF3B0, 0xFF9C30, t / 0.35f));
	return (lerp_color(0xFF9C30, 0x6B1A00, (t - 0.35f) / 0.65f));
}

/*
 * Soft round sprite: quadratic radial falloff, alpha or additive blend.
 * The falloff squared gives a gaussian-ish core with soft edges.
 */
void	draw_particle_soft(uint32_t *screen, struct s_pdraw *d)
{
	int		v[2];
	long	i;
	float	r2;
	float	a;

	v[1] = -d->size - 1;
	while (++v[1] <= d->size)
	{
		v[0] = -d->size - 1;
		while (++v[0] <= d->size)
		{
			r2 = (float)(v[0] * v[0] + v[1] * v[1])
				/ (float)(d->size * d->size + 1);
			if (r2 > 1.0f || (unsigned int)(d->px + v[0]) >= WIN_WIDTH
				|| (unsigned int)(d->py + v[1]) >= WIN_HEIGHT)
				continue ;
			a = d->alpha * (1.0f - r2) * (1.0f - r2);
			i = (long)(d->py + v[1]) * WIN_WIDTH + d->px + v[0];
			if (d->add)
				screen[i] = add_px(screen[i], d->color, a);
			else
				screen[i] = blend_px(screen[i], d->color, a);
		}
	}
}

/*
 * Velocity-aligned streak (motion blur) for rain: a fading trail of
 * blended pixels behind the drop's current position.
 */
void	draw_particle_streak(uint32_t *screen, struct s_pdraw *d,
			float vx, float vy)
{
	float	p[2];
	float	inv;
	int		i;
	long	idx;

	inv = 1.0f / sqrtf(vx * vx + vy * vy + 0.001f);
	p[0] = (float)d->px;
	p[1] = (float)d->py;
	i = -1;
	while (++i < 26)
	{
		if ((unsigned int)(int)p[0] < WIN_WIDTH - 1
			&& (unsigned int)(int)p[1] < WIN_HEIGHT)
		{
			idx = (long)p[1] * WIN_WIDTH + (long)p[0];
			screen[idx] = blend_px(screen[idx], d->color,
					d->alpha * (1.0f - (float)i / 26.0f));
			screen[idx + 1] = blend_px(screen[idx + 1], d->color,
					d->alpha * 0.5f * (1.0f - (float)i / 26.0f));
		}
		p[0] -= vx * inv;
		p[1] -= vy * inv;
	}
}
