/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:49 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 13:46:08 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "fdf.h"
#include "libft.h"

// --- Color interpolation helpers ---

typedef struct s_color_point {
	int z;
	uint32_t color;
} t_color_point;


// Find the color for a given z using control points
static uint32_t color_from_control_points(const t_color_point *points, int n, int z)
{
	if (z <= points[0].z)
		return points[0].color;
	for (int i = 1; i < n; ++i)
	{
		if (z <= points[i].z)
		{
			float t = (float)(z - points[i-1].z) / (points[i].z - points[i-1].z);
			return lerp_color(points[i-1].color, points[i].color, t);
		}
	}
	return points[n-1].color;
}

// --- Palette definitions ---

static const t_color_point planet_points[] = {
	{ -200, 0x2e0854 },
	{  -70, 0x6a0572 },
	{  -20, 0xab83a1 },
	{    0, 0xf5d0c5 },
	{   50, 0xf49d6e },
	{  100, 0xf47a60 },
	{  200, 0x303960 },
	{  400, 0x1b2845 },
	{  720, 0x0b132b }
};

// --- Add the gamma_random_v2 palette control points ---
static const t_color_point gamma_random_v2_points[] = {
	{  101, 0x7799a7 },
	{  100, 0xb8ba99 },
	{   50, 0xb8ba99 },
	{   49, 0xb8ba5a },
	{   15, 0xb8ba5a },
	{   14, 0xb8ab94 },
	{    0, 0xb8ab94 },
	{  -15, 0xb8ac94 },
	{  -60, 0xb5ab90 },
	{  -90, 0xb3aa86 },
	{ -140, 0xa09783 },
	{ -170, 0x959282 },
	{ -210, 0x918381 },
	{ -240, 0x897882 },
	{ -280, 0x897882 }
};

// Palette 5: terrain (classic)
// extern void palette_terrain(int *arr, int pos, int z_value);

// Palette 6: gamma (classic)
// extern void palette_gamma(int *arr, int pos, int z_value);

// Palette 7: vibrant (rainbow-like)
static const t_color_point vibrant_points[] = {
	{ -200, 0x9400D3 }, // Violet
	{ -150, 0x4B0082 }, // Indigo
	{ -100, 0x0000FF }, // Blue
	{  -50, 0x00FF00 }, // Green
	{    0, 0xFFFF00 }, // Yellow
	{   50, 0xFF7F00 }, // Orange
	{  100, 0xFF0000 }, // Red
	{  200, 0xFFFFFF }  // White
};

void palette_vibrant(int *arr, int pos, int z_value)
{
	arr[pos] = color_from_control_points(
		vibrant_points,
		sizeof(vibrant_points)/sizeof(*vibrant_points),
		z_value
	);
}

// Palette 8: grayscale
static const t_color_point grayscale_points[] = {
	{ -200, 0x000000 },
	{    0, 0x888888 },
	{  200, 0xFFFFFF }
};

void palette_grayscale(int *arr, int pos, int z_value)
{
	arr[pos] = color_from_control_points(
		grayscale_points,
		sizeof(grayscale_points)/sizeof(*grayscale_points),
		z_value
	);
}

// Palette 9: sunset
static const t_color_point sunset_points[] = {
	{ -200, 0x120078 },
	{ -100, 0x9D0191 },
	{    0, 0xFD3A69 },
	{  100, 0xFF6A00 },
	{  200, 0xFFB300 }
};

void palette_sunset(int *arr, int pos, int z_value)
{
	arr[pos] = color_from_control_points(
		sunset_points,
		sizeof(sunset_points)/sizeof(*sunset_points),
		z_value
	);
}

// Palette 7: Matrix/Neon Green theme
static const t_color_point matrix_points[] = {
	{ -200, 0x000000 }, // Black
	{ -100, 0x001100 }, // Dark green
	{    0, 0x00FF00 }, // Bright green
	{  100, 0x66FF66 }, // Light green
	{  200, 0xFFFFFF }  // White highlights
};

void palette_matrix(int *arr, int pos, int z_value)
{
	arr[pos] = color_from_control_points(
		matrix_points,
		sizeof(matrix_points)/sizeof(*matrix_points),
		z_value
	);
}

// Palette 8: Fire/Lava theme
static const t_color_point fire_points[] = {
	{ -200, 0x330000 }, // Dark red
	{ -100, 0x660000 }, // Deep red
	{    0, 0xFF0000 }, // Red
	{   50, 0xFF4400 }, // Red-orange
	{  100, 0xFF8800 }, // Orange
	{  150, 0xFFCC00 }, // Yellow-orange
	{  200, 0xFFFF00 }  // Yellow
};

void palette_fire(int *arr, int pos, int z_value)
{
	arr[pos] = color_from_control_points(
		fire_points,
		sizeof(fire_points)/sizeof(*fire_points),
		z_value
	);
}

// Palette 9: Ice/Arctic theme
static const t_color_point ice_points[] = {
	{ -200, 0x000033 }, // Dark blue
	{ -100, 0x003366 }, // Deep blue
	{    0, 0x0066CC }, // Blue
	{   50, 0x3399FF }, // Light blue
	{  100, 0x66CCFF }, // Cyan
	{  150, 0xCCFFFF }, // Light cyan
	{  200, 0xFFFFFF }  // White
};

void palette_ice(int *arr, int pos, int z_value)
{
	arr[pos] = color_from_control_points(
		ice_points,
		sizeof(ice_points)/sizeof(*ice_points),
		z_value
	);
}

// --- Palette functions for control points palettes ---

static void palette_planet(int *arr, int pos, int z_value)
{
	arr[pos] = color_from_control_points(
		planet_points,
		sizeof(planet_points)/sizeof(*planet_points),
		z_value
	);
}

static void palette_gamma_random_v2(int *arr, int pos, int z_value)
{
	arr[pos] = color_from_control_points(
		gamma_random_v2_points,
		sizeof(gamma_random_v2_points)/sizeof(*gamma_random_v2_points),
		z_value
	);
}

static void palette_default(int *arr, int pos, int z_value)
{
	arr[pos] = (uint32_t)z_value; // fallback: encode z as color
}


// --- Palette selection logic ---

typedef void (*palette_func_t)(int *, int, int);

static palette_func_t g_palettes[] = {
	palette_planet,             // 1 - Planet/Ocean theme
	palette_default,            // 2 - Default
	palette_gamma_random_v2,    // 3 - Gamma random V2
	palette_vibrant,            // 4 - Vibrant/Rainbow
	palette_grayscale,          // 5 - Grayscale
	palette_sunset,             // 6 - Sunset
	palette_matrix,             // 7 - Matrix/Neon Green
	palette_fire,               // 8 - Fire/Lava
	palette_ice                 // 9 - Ice/Arctic
};

static int g_palette_count = sizeof(g_palettes)/sizeof(*g_palettes);
static int g_current_palette = 0;

palette_func_t get_color_palette(int palette)
{
	if (palette >= 0 && palette < g_palette_count)
		return g_palettes[palette];
	return palette_default;
}

void set_color_palet(int *a, palette_func_t f, int p, int z_val)
{
	f(a, p, z_val);
}

// Call this to update all colors after palette switch
void set_color_array(t_app *fdf)
{
	int	i, j, val;
	palette_func_t palette = get_color_palette(g_current_palette);

	for (i = 0; i < fdf->height; i++)
	{
		for (j = 0; j < fdf->width; j++)
		{
			val = (int)fdf->points[i * fdf->width + j];
			set_color_palet((int *)fdf->color, palette, i * fdf->width + j, val);
		}
	}
}

// Called from handler when user presses 1-9
void set_palette_index(int idx, t_app *fdf)
{
	if (idx >= 0 && idx < g_palette_count)
	{
		g_current_palette = idx;
		set_color_array(fdf);
		
		// Update background theme to match palette
		generate_background(fdf, idx);
	}
}