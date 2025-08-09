/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 21:10:24 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 05:09:22 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <time.h>

//static int	fdf->current_bg_theme = 0;
//static int	fdf->stars_enabled = 1;

uint32_t	star_color_for_theme(int theme, int i)
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

static uint32_t	get_bg_color_for_theme(int theme_index)
{
	static const uint32_t	bg[9] = {
		0x00000000, 0x00001A1A, 0x001A0000,
		0x00001A00, 0x00000033, 0x00331100,
		0x00003333, 0x00330033, 0x00222222
	};

	return (bg[theme_index % 9]);
}

static void	fill_background_buffer(uint32_t *buf, uint32_t color, int total)
{
	int	i;

	i = 0;
	while (i < total)
	{
		buf[i] = color;
		++i;
	}
}

void	generate_background(t_app *fdf, int theme_index)
{
	uint32_t	*buf;
	int			total;

	fdf->current_bg_theme = theme_index % 9;
	buf = (uint32_t *)fdf->renderer.data;
	total = WIN_WIDTH * WIN_HEIGHT;
	fill_background_buffer(buf,
		get_bg_color_for_theme(fdf->current_bg_theme), total);
}

int	get_current_background_theme(t_app *fdf)
{
	return (fdf->current_bg_theme);
}
