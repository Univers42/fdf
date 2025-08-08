/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 00:28:06 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 00:16:26 by dlesieur         ###   ########.fr       */
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
	ft_printf("DEBUG: init_palette_system called\n");
	if (!fdf)
	{
		ft_printf("DEBUG: fdf is NULL in init_palette_system\n");
		return ;
	}
	ft_printf("DEBUG: Setting g_palette_app\n");
	g_palette_app = fdf;
	ft_printf("DEBUG: Getting theme palette count\n");
	fdf->palette_state.count = get_theme_palette_count();
	ft_printf("DEBUG: Palette count: %d\n", fdf->palette_state.count);
	fdf->palette_state.current = 0;
	fdf->palette_state.funcs = NULL;
	ft_printf("DEBUG: init_palette_system completed\n");
}

void	set_palette_index(int idx, t_app *fdf)
{
	ft_printf("DEBUG: set_palette_index called with idx=%d\n", idx);
	if (!fdf)
	{
		ft_printf("DEBUG: fdf is NULL in set_palette_index\n");
		return ;
	}
	if (fdf->palette_state.count == 0)
	{
		ft_printf("DEBUG: Palette count is 0, initializing\n");
		init_palette_system(fdf);
	}
	if (idx < 0)
		idx = 0;
	if (idx >= fdf->palette_state.count)
		idx = fdf->palette_state.count - 1;
	ft_printf("DEBUG: Setting current palette to %d\n", idx);
	fdf->palette_state.current = idx;
	
	// Apply palette immediately when it changes
	ft_printf("DEBUG: Applying palette immediately\n");
	apply_current_palette(fdf);
	ft_printf("DEBUG: Palette %d applied successfully\n", idx);
}

bool	palette_needs_update(t_app *fdf)
{
	(void)fdf;
	return false;  // Never needs update in render loop
}

void	update_palette_if_needed(t_app *fdf)
{
	(void)fdf;
	// No-op - palette updates happen immediately when palette changes
}

uint32_t	get_background_color(void)
{
	const t_theme_palette *p;

	if (!g_palette_app)
		return pack_rgba(0,0,0,255);
	if (g_palette_app->palette_state.count == 0)
		return pack_rgba(0,0,0,255);  // Don't initialize here to prevent recursion
	p = get_theme_palette(g_palette_app->palette_state.current);
	if (!p)
		return pack_rgba(0,0,0,255);
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
	
	// Just return a default color if system not initialized
	if (!fdf || fdf->palette_state.count == 0)
		return pack_rgba(128, 128, 128, 255); // default gray
	
	// Additional safety check for current index
	if (fdf->palette_state.current < 0 || fdf->palette_state.current >= fdf->palette_state.count)
	{
		ft_printf("DEBUG: Invalid palette index %d, using 0\n", fdf->palette_state.current);
		fdf->palette_state.current = 0;
	}
		
	p = get_theme_palette(fdf->palette_state.current);
	if (!p)
	{
		ft_printf("DEBUG: get_theme_palette returned NULL\n");
		return pack_rgba(128, 128, 128, 255);
	}
	
	// Validate color_count before accessing colors array
	if (p->color_count <= 0 || p->color_count > 8)
	{
		ft_printf("DEBUG: Invalid color_count: %d\n", p->color_count);
		return pack_rgba(128, 128, 128, 255);
	}
	
	if (p->color_count == 1)
		return p->colors[0];
		
	seg = (int)(norm * (p->color_count - 1));
	if (seg >= p->color_count - 1)
		seg = p->color_count - 2;
	if (seg < 0)
		seg = 0;
		
	local_t = (norm * (p->color_count - 1)) - seg;
	
	// Validate array access bounds
	if (seg >= p->color_count || (seg + 1) >= p->color_count)
	{
		ft_printf("DEBUG: Array bounds error: seg=%d, color_count=%d\n", seg, p->color_count);
		return p->colors[0];
	}
	
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

void	apply_current_palette(t_app *fdf)
{
	int		i;
	int		total_points;
	float	z_norm;
	float	z_value;

	ft_printf("DEBUG: apply_current_palette called - updating %d points\n", fdf->width * fdf->height);
	if (!fdf || !fdf->points || !fdf->color)
		return ;
	
	total_points = fdf->width * fdf->height;
	if (total_points <= 0)
		return ;
		
	i = -1;
	while (++i < total_points)
	{
		// fdf->points is a 1D array of Z values, not 3D coordinates
		z_value = fdf->points[i];
		if (fdf->max_z != fdf->min_z)
			z_norm = (z_value - (float)fdf->min_z) / (float)(fdf->max_z - fdf->min_z);
		else
			z_norm = 0.5f;
		
		fdf->color[i] = get_color_for_height(fdf, z_norm);
	}
	ft_printf("DEBUG: apply_current_palette completed\n");
}