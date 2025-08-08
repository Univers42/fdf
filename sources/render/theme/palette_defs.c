/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette_defs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 00:05:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 23:59:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "theme.h"

static t_theme_palette	*get_palette_singleton(void)
{
	static t_theme_palette	palettes[9];
	static bool				initialized = false;

	if (!initialized)
	{
		// Planet/Ocean
		palettes[0] = (t_theme_palette){"Planet/Ocean", 
			{create_color(10,25,68), create_color(18,87,122), create_color(32,155,164), create_color(180,220,230)}, 
			4, create_color(0,8,20)};
		
		// Default
		palettes[1] = (t_theme_palette){"Default", 
			{create_color(30,30,30), create_color(80,80,80), create_color(160,160,160), create_color(220,220,220)}, 
			4, create_color(0,0,0)};
		
		// Gamma Random V2
		palettes[2] = (t_theme_palette){"Gamma Random V2", 
			{create_color(5,5,20), create_color(90,15,120), create_color(200,40,40), create_color(250,200,60)}, 
			4, create_color(5,5,16)};
		
		// Vibrant/Rainbow
		palettes[3] = (t_theme_palette){"Vibrant/Rainbow", 
			{create_color(255,0,64), create_color(255,128,0), create_color(64,255,0), create_color(0,200,255), create_color(160,0,255)}, 
			5, create_color(0,0,0)};
		
		// Grayscale
		palettes[4] = (t_theme_palette){"Grayscale", 
			{create_color(0,0,0), create_color(64,64,64), create_color(128,128,128), create_color(192,192,192), create_color(255,255,255)}, 
			5, create_color(0,0,0)};
		
		// Sunset
		palettes[5] = (t_theme_palette){"Sunset", 
			{create_color(20,10,40), create_color(120,30,90), create_color(220,80,40), create_color(255,180,60)}, 
			4, create_color(20,10,40)};
		
		// Matrix/Neon Green
		palettes[6] = (t_theme_palette){"Matrix/Neon Green", 
			{create_color(0,8,0), create_color(0,40,0), create_color(0,120,0), create_color(40,255,90)}, 
			4, create_color(0,6,0)};
		
		// Fire/Lava
		palettes[7] = (t_theme_palette){"Fire/Lava", 
			{create_color(20,0,0), create_color(120,10,0), create_color(200,40,0), create_color(255,160,0), create_color(255,240,180)}, 
			5, create_color(18,0,0)};
		
		// Ice/Arctic
		palettes[8] = (t_theme_palette){"Ice/Arctic", 
			{create_color(0,10,30), create_color(0,60,120), create_color(40,140,200), create_color(160,220,255)}, 
			4, create_color(0,16,32)};
		
		initialized = true;
	}
	return palettes;
}

const t_theme_palette *get_theme_palette(int idx)
{
	t_theme_palette	*palettes;

	palettes = get_palette_singleton();
	if (idx < 0 || idx >= 9)
		return &palettes[0];
	return &palettes[idx];
}

int	get_theme_palette_count(void)
{
	return 9;
}