/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   black_hole_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>

/*
 * Ring palette: one dark-red -> orange -> white-hot gradient, 1..255.
 * The LUT picks the index from ring shape x relativistic beaming, so
 * brightness varies smoothly around the ring at zero runtime cost.
 * Index 0 stays pure black (inside the photon sphere).
 */
static void	bh_palette(t_black_hole *bh)
{
	int		i;
	float	t;

	bh->palette[0] = 0x000000;
	i = 0;
	while (++i < 256)
	{
		t = (float)i / 255.0f;
		if (t < 0.55f)
			bh->palette[i] = lerp_color(0x120300, 0xC24E10, t / 0.55f);
		else
			bh->palette[i] = lerp_color(0xC24E10, 0xFFF3D6,
					(t - 0.55f) / 0.45f);
	}
}

/* Bright stars get a 2x2 splat so they survive the lens warp visually. */
static void	bh_put_star(t_black_hole *bh, int p, uint32_t c)
{
	bh->stars[p] = c;
	if (p % WIN_WIDTH < WIN_WIDTH - 1 && p < WIN_WIDTH * (WIN_HEIGHT - 1))
	{
		bh->stars[p + 1] = c;
		bh->stars[p + WIN_WIDTH] = c;
		bh->stars[p + WIN_WIDTH + 1] = c;
	}
}

/*
 * Star texture: black space, dim dust, then stars with varied brightness
 * and color temperature. Uses the libft xorshift RNG (deterministic look
 * per seed is fine here).
 */
static void	bh_stars(t_black_hole *bh)
{
	int	i;
	int	p;
	int	b;

	ft_memset(bh->stars, 0, sizeof(uint32_t) * WIN_WIDTH * WIN_HEIGHT);
	i = -1;
	while (++i < BH_DUST_COUNT)
	{
		p = ft_rand() % (WIN_WIDTH * WIN_HEIGHT);
		b = 24 + ft_rand() % 40;
		bh->stars[p] = create_color(b, b, b + 8);
	}
	i = -1;
	while (++i < BH_STAR_COUNT)
	{
		p = ft_rand() % (WIN_WIDTH * WIN_HEIGHT);
		b = 120 + ft_rand() % 136;
		if (ft_rand() % 3 == 0)
			bh->stars[p] = create_color(b - 30, b - 10, b);
		else if (b > 200)
			bh_put_star(bh, p, create_color(b, b - 15, b - 40));
		else
			bh->stars[p] = create_color(b, b - (ft_rand() % 25), b - 40);
	}
}

/*
 * Point-lens equation in screen space: a ray hitting the screen at
 * radius b from the hole apparently comes from radius b - Re^2 / b
 * (negative inside the Einstein radius: the inverted secondary image).
 * Inside the photon sphere nothing escapes -> palette black; a thin
 * annulus above it is the glowing photon ring.
 */
static uint32_t	bh_lut_pixel(t_black_hole *bh, int x, int y)
{
	float	d[2];
	float	b;
	float	src;
	int		s[2];

	d[0] = (float)x - gviewport()->w / 2.0f;
	d[1] = (float)y - gviewport()->h / 2.0f;
	b = sqrtf(d[0] * d[0] + d[1] * d[1]);
	if (b < bh->photon_r)
		return (0xFFFF0000u);
	if (b < bh->photon_r * BH_RING_MULT)
	{
		src = (b - bh->photon_r) / (bh->photon_r * (BH_RING_MULT - 1.0f));
		src = 1.0f - fabsf(src * 2.0f - 1.0f);
		src *= 0.30f + 0.70f * (0.5f + 0.5f * (d[0] / b));
		return (0xFFFF0000u | (1 + (uint32_t)(src * 254.0f)));
	}
	src = (b - bh->einstein_r * bh->einstein_r / b) / b;
	s[0] = (int)(gviewport()->w / 2.0f + d[0] * src) % WIN_WIDTH;
	s[1] = (int)(gviewport()->h / 2.0f + d[1] * src) % WIN_HEIGHT;
	s[0] += WIN_WIDTH * (s[0] < 0);
	s[1] += WIN_HEIGHT * (s[1] < 0);
	return ((uint32_t)s[0] | ((uint32_t)s[1] << 16));
}

/* One-shot build: ~50ms once, then every frame is a plain LUT walk. */
void	black_hole_build(t_black_hole *bh)
{
	int	x;
	int	y;

	bh->lut = malloc(sizeof(uint32_t) * WIN_WIDTH * WIN_HEIGHT);
	bh->stars = malloc(sizeof(uint32_t) * WIN_WIDTH * WIN_HEIGHT);
	if (!bh->lut || !bh->stars)
	{
		return ((void)(bh->failed = true), black_hole_free());
	}
	bh->photon_r = BH_PHOTON_R * gviewport()->h;
	bh->einstein_r = BH_EINSTEIN_MULT * bh->photon_r;
	bh_palette(bh);
	bh_stars(bh);
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			bh->lut[y * WIN_WIDTH + x] = bh_lut_pixel(bh, x, y);
	}
	bh->init = true;
}
