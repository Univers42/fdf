/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 21:10:24 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 21:10:25 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <time.h>

#define STAR_COUNT 200

static int	g_current_bg_theme = 0;
static int	g_stars_enabled = 1;

static uint32_t	star_color_for_theme(int theme, int i)
{
	uint32_t	c;

	c = 0xFFFFFF;
	if (theme == 1)
		c = 0x00FFFF;
	else if (theme == 2)
		c = 0xFFFF00;
	else if (theme == 3)
		c = 0xFFFFFF;
	else if (theme == 4)
		c = 0xCCCCCC;
	else if (theme == 5)
		c = 0xFF0080 + (uint32_t)((i * 31) % 0x7F7F7F);
	else if (theme == 6)
		c = 0x808080 + (uint32_t)((i * 17) % 0x7F7F7F);
	else if (theme == 7)
		c = 0xFFB300 + (uint32_t)((i * 23) % 0x004C00);
	else if (theme == 8)
		c = 0xCC99FF;
	return (c);
}

void	generate_background(t_app *fdf, int theme_index)
{
	static const uint32_t	bg[9] = {
		0x00000000, 0x00001A1A, 0x001A0000,
		0x00001A00, 0x00000033, 0x00331100,
		0x00003333, 0x00330033, 0x00222222
	};
	uint32_t				*buf;
	uint32_t				color;
	int						i;
	int						total;

	g_current_bg_theme = theme_index % 9;
	color = bg[g_current_bg_theme];
	buf = (uint32_t *)fdf->renderer.data;
	total = WIN_WIDTH * WIN_HEIGHT;
	i = 0;
	while (i < total)
	{
		buf[i] = color;
		++i;
	}
}

void	generate_stars(t_app *fdf)
{
	uint32_t	*buf;
	int			i;
	int			sx;
	int			sy;
	uint32_t	c;
	static int	seeded = 0;

	if (!g_stars_enabled)
		return ;
	if (!seeded)
	{
		srand((unsigned int)time(NULL));
		seeded = 1;
	}
	buf = (uint32_t *)fdf->renderer.data;
	i = 0;
	while (i < STAR_COUNT)
	{
		sx = (i * 73 + 17) % WIN_WIDTH;
		sy = (i * 137 + 23) % WIN_HEIGHT;
		c = star_color_for_theme(g_current_bg_theme, i);
		if (sx + 1 < WIN_WIDTH && sy + 1 < WIN_HEIGHT)
		{
			buf[sy * WIN_WIDTH + sx] = c;
			buf[sy * WIN_WIDTH + sx + 1] = c;
			buf[(sy + 1) * WIN_WIDTH + sx] = c;
			buf[(sy + 1) * WIN_WIDTH + sx + 1] = c;
		}
		++i;
	}
}

void toggle_stars(void)
{
	g_stars_enabled = !g_stars_enabled;
	ft_printf("Stars %s\n", g_stars_enabled ? "enabled" : "disabled");
}

bool are_stars_enabled(void)
{
	return (g_stars_enabled);
}

int get_current_background_theme(void)
{
	return (g_current_bg_theme);
}
