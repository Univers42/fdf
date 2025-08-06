/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:27:24 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/06 04:36:31 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define STAR_COUNT 200
#define WHITE 0xFFFFFF

static bool g_stars_enabled = true; // Enable stars by default
static int g_current_bg_theme = 0;

// Theme-based background colors (matching your palette themes)
const uint32_t g_background_themes[9] = {
	0x000000, // Theme 0: Pure black (planet theme)
	0x00001a1a, // Theme 1: Dark blue
	0x001a0000, // Theme 2: Dark red  
	0x00001a00, // Theme 3: Dark green
	0x00000033, // Theme 4: Dark blue
	0x00331100, // Theme 5: Dark yellow
	0x00003333, // Theme 6: Dark cyan
	0x00330033, // Theme 7: Dark magenta
	0x00222222  // Theme 8: Dark gray
};

void generate_background(t_app *fdf, int theme_index)
{
	uint32_t *buffer = (uint32_t *)fdf->renderer.data;
	uint32_t bg_color = 0x00000000; // Default black
	
	g_current_bg_theme = theme_index;
	
	// Simple solid color backgrounds for different themes
	switch (theme_index % 9)
	{
		case 0: bg_color = 0x00000000; break; // Black
		case 1: bg_color = 0x00001a1a; break; // Dark blue
		case 2: bg_color = 0x001a0000; break; // Dark red
		case 3: bg_color = 0x00001a00; break; // Dark green
		case 4: bg_color = 0x00000033; break; // Dark blue
		case 5: bg_color = 0x00331100; break; // Dark yellow
		case 6: bg_color = 0x00003333; break; // Dark cyan
		case 7: bg_color = 0x00330033; break; // Dark magenta
		case 8: bg_color = 0x00222222; break; // Dark gray
	}
	
	// Fill background
	for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; i++)
		buffer[i] = bg_color;
}

void generate_stars(t_app *fdf)
{
	uint32_t *buffer;
	int star_x, star_y;
	uint32_t star_color;
	static bool seeded = false;
	
	if (!g_stars_enabled)
		return;
	
	// Seed random once
	if (!seeded)
	{
		srand((unsigned int)time(NULL) + 12345); // Different seed than particles
		seeded = true;
	}
	
	buffer = (uint32_t *)fdf->renderer.data;
	
	// Generate stars with theme-appropriate colors
	for (int i = 0; i < STAR_COUNT; i++)
	{
		// Create more stable star positions
		star_x = (i * 73 + 17) % WIN_WIDTH;
		star_y = (i * 137 + 23) % WIN_HEIGHT;
		
		// Different star colors based on theme
		switch (g_current_bg_theme)
		{
			case 0: // Planet theme - white stars
				star_color = WHITE;
				break;
			case 1: // Blue theme - cyan stars
				star_color = 0x00FFFF;
				break;
			case 2: // Red theme - yellow stars
				star_color = 0xFFFF00;
				break;
			case 3: // Green theme - white stars
				star_color = WHITE;
				break;
			case 4: // Gamma random - light gray stars
				star_color = 0xCCCCCC;
				break;
			case 5: // Vibrant - rainbow effect
				star_color = 0xFF0080 + ((i * 31) % 0x7F7F7F);
				break;
			case 6: // Grayscale - various gray stars
				star_color = 0x808080 + ((i * 17) % 0x7F7F7F);
				break;
			case 7: // Sunset - warm colored stars
				star_color = 0xFFB300 + ((i * 23) % 0x004C00);
				break;
			case 8: // Purple theme - light purple stars
				star_color = 0xCC99FF;
				break;
			default:
				star_color = WHITE;
		}
		
		// Draw star (larger for visibility)
		for (int sy = 0; sy < 2; sy++)
		{
			for (int sx = 0; sx < 2; sx++)
			{
				int x = star_x + sx;
				int y = star_y + sy;
				
				if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
				{
					buffer[y * WIN_WIDTH + x] = star_color;
				}
			}
		}
	}
}

void toggle_stars(void)
{
	g_stars_enabled = !g_stars_enabled;
	printf("Stars %s\n", g_stars_enabled ? "enabled" : "disabled");
}

bool are_stars_enabled(void)
{
	return g_stars_enabled;
}

int get_current_background_theme(void)
{
	return g_current_bg_theme;
}
