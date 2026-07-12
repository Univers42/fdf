/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
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
 * Showcase sky: zenith-to-horizon gradient, warm haze below the
 * horizon line, and an emissive sun disc with a soft glow. Baked once
 * into a full-res buffer; per frame it is a single memcpy.
 * ponytail: screen-fixed sky; regenerate per yaw/pitch if a moving sky
 * is ever wanted.
 */

static uint32_t	sky_pixel(int x, int y)
{
	float		t;
	float		d;
	uint32_t	c;

	t = (float)y / gviewport()->h;
	if (t > 1.0f)
		t = 1.0f;
	if (t < 0.62f)
		c = lerp_color(0x1B2C55, SKY_HORIZON & 0xFFFFFF, t / 0.62f);
	else
		c = lerp_color(SKY_HORIZON & 0xFFFFFF, 0x66748C,
				(t - 0.62f) / 0.38f);
	d = sqrtf((x - gviewport()->w * 0.70f) * (x - gviewport()->w * 0.70f)
			+ (y - gviewport()->h * 0.22f) * (y - gviewport()->h * 0.22f));
	if (d < gviewport()->h * 0.045f)
		return (0xFFF6DE);
	if (d < gviewport()->h * 0.30f)
	{
		t = 1.0f - (d / (gviewport()->h * 0.30f));
		c = lerp_color(c, 0xFFE9B8, t * t);
	}
	return (c);
}

static uint32_t	**gsky_slot(void)
{
	static uint32_t	*sky;

	return (&sky);
}

static uint32_t	*gsky(void)
{
	uint32_t	*sky;
	int			x;
	int			y;

	sky = *gsky_slot();
	if (sky)
		return (sky);
	sky = (uint32_t *)malloc(sizeof(uint32_t) * WIN_WIDTH * WIN_HEIGHT);
	*gsky_slot() = sky;
	if (!sky)
		return (NULL);
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			sky[y * WIN_WIDTH + x] = sky_pixel(x, y);
	}
	return (sky);
}

void	sky_render(t_app *f)
{
	uint32_t	*sky;

	sky = gsky();
	if (!sky)
		return ((void)generate_background(f, 0));
	ft_memcpy(f->renderer.data, sky,
		sizeof(uint32_t) * WIN_WIDTH * WIN_HEIGHT);
}

void	sky_free(void)
{
	free(*gsky_slot());
	*gsky_slot() = NULL;
}
