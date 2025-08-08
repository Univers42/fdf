/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 00:28:06 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 00:01:50 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "theme.h"
#include <math.h>

extern const t_theme_palette *get_theme_palette(int idx);
extern int get_theme_palette_count(void);

static t_app *g_palette_app = NULL;

#define R_CH(c) ((uint8_t)((c)>>24))
#define G_CH(c) ((uint8_t)((c)>>16))
#define B_CH(c) ((uint8_t)((c)>>8))

static uint32_t lerp_chan(uint32_t a, uint32_t b, float t)
{
	return (uint32_t)(a + (b - a) * t);
}

uint32_t	pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ((uint32_t)r << 24) | ((uint32_t)g << 16)
		| ((uint32_t)b << 8) | (uint32_t)a;
}

void	init_palette_system(t_app *fdf)
{
	g_palette_app = fdf;
	fdf->palette_state.count = get_theme_palette_count();
	if (fdf->palette_state.current < 0
		|| fdf->palette_state.current >= fdf->palette_state.count)
		fdf->palette_state.current = 0;
}

void	set_palette_index(int idx, t_app *fdf)
{
	if (fdf->palette_state.count == 0)
		init_palette_system(fdf);
	if (idx < 0)
		idx = 0;
	if (idx >= fdf->palette_state.count)
		idx = fdf->palette_state.count - 1;
	fdf->palette_state.current = idx;
}

uint32_t	get_background_color(void)
{
	const t_theme_palette *p;

	if (!g_palette_app)
		return pack_rgba(0,0,0,255);
	if (g_palette_app->palette_state.count == 0)
		init_palette_system(g_palette_app);
	p = get_theme_palette(g_palette_app->palette_state.current);
	return p->background;
}

uint32_t	get_color_for_height(t_app *fdf, float norm)
{
	const t_theme_palette *p;
	int		seg;
	float	local_t;
	uint32_t c1;
	uint32_t c2;
	uint8_t r,g,b;

	if (norm < 0) norm = 0;
	if (norm > 1) norm = 1;
	if (fdf->palette_state.count == 0)
		init_palette_system(fdf);
	p = get_theme_palette(fdf->palette_state.current);
	if (p->color_count <= 1)
		return p->colors[0];
	seg = (int)(norm * (p->color_count - 1));
	if (seg >= p->color_count - 1)
		seg = p->color_count - 2;
	local_t = (norm * (p->color_count - 1)) - seg;
	c1 = p->colors[seg];
	c2 = p->colors[seg + 1];
	r = (uint8_t)lerp_chan(R_CH(c1), R_CH(c2), local_t);
	g = (uint8_t)lerp_chan(G_CH(c1), G_CH(c2), local_t);
	b = (uint8_t)lerp_chan(B_CH(c1), B_CH(c2), local_t);
	return pack_rgba(r,g,b,255);
}

uint32_t	create_color(uint8_t r, uint8_t g, uint8_t b)
{
	return pack_rgba(r, g, b, 255);
}

// Compatibility function for bresenham algorithm
uint32_t	pack_color(t_bresenham_state *bs, int step)
{
	uint8_t	r, g, b_val;
	float	t;

	if (!bs)
		return 0xFF000000; // default black
	
	// Calculate interpolation factor
	if (bs->error_count <= 0)
		t = 0.0f;
	else
		t = (float)step / (float)bs->error_count;
	
	// Linear interpolation between color1 and color2
	r = (uint8_t)((bs->color1 >> 24) + t * bs->color_r_delta);
	g = (uint8_t)(((bs->color1 >> 16) & 0xFF) + t * bs->color_g_delta);
	b_val = (uint8_t)(((bs->color1 >> 8) & 0xFF) + t * bs->color_b_delta);
	
	return pack_rgba(r, g, b_val, 255);
}