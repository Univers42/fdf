/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:27:18 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:27:19 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"
#include <stdint.h>
#include <stddef.h>
#include <ctype.h>

uint32_t	pack_color(t_bresenham_state *b, int step)
{
	return ((((int)(step * b->color_r_delta)
			+ (b->color1 >> 16 & 0xff)) << 16)
	| (((int)(step * b->color_g_delta)
				+ ((b->color1 >> 8 & 0xff))) << 8)
	| ((int)(step * b->color_b_delta)
				+ (b->color1 & 0xff)));
}

void	palette_gamma(int *arr, int pos, int z_value)
{
	if (z_value >= 720)
		arr[pos] = hex_to_color("ac7456");
	if (z_value < 720 && z_value >= 400)
		arr[pos] = hex_to_color("bfabcc");
	if (z_value < 400 && z_value >= 200)
		arr[pos] = hex_to_color("ddab41");
	if (z_value < 200 && z_value >= 90)
		arr[pos] = hex_to_color("decd51");
	if (z_value < 90 && z_value >= 0)
		arr[pos] = hex_to_color("aced99");
	if (z_value == 0)
		arr[pos] = hex_to_color("ac74f9");
	if (z_value < 0 && z_value >= -80)
		arr[pos] = hex_to_color("40cdbf");
	if (z_value < -80 && z_value >= -170)
		arr[pos] = hex_to_color("189995");
	if (z_value < -170 && z_value >= -250)
		arr[pos] = hex_to_color("555999");
	if (z_value < -250 && z_value >= -320)
		arr[pos] = hex_to_color("60699b");
	if (z_value < -320 && z_value >= -400)
		arr[pos] = hex_to_color("8879be");
	palette_gamma_2(arr, pos, z_value);
}


void	palette_test(int *arr, int pos, int z_value)
{
	if (z_value >= 0)
		arr[pos] = hex_to_color("d773ca");
	else
		arr[pos] = hex_to_color("b8ac94");
}

void	palette_gamma_red(int *arr, int pos, int z_value)
{
	if (z_value > 13)
		arr[pos] = hex_to_color("aca951");
	if (z_value <= 13 && z_value >= 10)
		arr[pos] = hex_to_color("ab7153");
	if (z_value < 10 && z_value >= 7)
		arr[pos] = hex_to_color("aa6543");
	if (z_value < 7 && z_value >= 4)
		arr[pos] = hex_to_color("825536");
	if (z_value < 4 && z_value >= -5)
		arr[pos] = hex_to_color("965035");
	if (z_value < -5)
		arr[pos] = hex_to_color("853535");
}

void	palette_gamma_random(int *arr, int pos, int z_value)
{
	if (z_value > 100)
		arr[pos] = hex_to_color("7799a7");
	if (z_value <= 100 && z_value >= 50)
		arr[pos] = hex_to_color("b8ba99");
	if (z_value < 50 && z_value >= 15)
		arr[pos] = hex_to_color("b8ba5a");
	if (z_value < 15 && z_value >= 0)
		arr[pos] = hex_to_color("b8ab94");
	if (z_value < -15 && z_value >= -60)
		arr[pos] = hex_to_color("b8ac94");
	if (z_value < -60 && z_value >= -90)
		arr[pos] = hex_to_color("b5ab90");
	if (z_value < -90 && z_value >= -140)
		arr[pos] = hex_to_color("b3aa86");
	if (z_value < -140 && z_value >= -170)
		arr[pos] = hex_to_color("a09783");
	if (z_value < -170 && z_value >= -210)
		arr[pos] = hex_to_color("959282");
	if (z_value < -210 && z_value >= -240)
		arr[pos] = hex_to_color("918381");
	if (z_value < -240 && z_value >= -280)
		arr[pos] = hex_to_color("897882");
	pallete_gamma_random_2(arr, pos, z_value);
}

void	palette_gamma_2(int *arr, int pos, int z_value)
{
	if (z_value < -400 && z_value >= -460)
		arr[pos] = hex_to_color("ac74f9");
	if (z_value < -460)
		arr[pos] = hex_to_color("997498");
}

void	pallete_gamma_random_2(int *arr, int pos, int z_value)
{
	if (z_value < -280 && z_value >= -310)
		arr[pos] = hex_to_color("887780");
	if (z_value < -310 && z_value >= -460)
		arr[pos] = hex_to_color("877678");
	if (z_value < -460 && z_value >= -510)
		arr[pos] = hex_to_color("857576");
	if (z_value < -510 && z_value >= -560)
		arr[pos] = hex_to_color("847474");
	if (z_value < -560 && z_value >= -610)
		arr[pos] = hex_to_color("837272");
	if (z_value < -610)
		arr[pos] = hex_to_color("827070");
}

// Converts a hex string (e.g., "ff00ff") to a 24-bit RGB integer (0xRRGGBB)
int hex_to_color(char *color)
{
	uint32_t result = 0;
	int i = 0;
	char c;

	// Skip "0x" or "0X" prefix if present
	if (color[0] == '0' && (color[1] == 'x' || color[1] == 'X'))
		color += 2;

	while (i < 6 && (c = color[i]))
	{
		result <<= 4;
		if (c >= '0' && c <= '9')
			result |= (c - '0');
		else if (c >= 'a' && c <= 'f')
			result |= (c - 'a' + 10);
		else if (c >= 'A' && c <= 'F')
			result |= (c - 'A' + 10);
		else
			break;
		i++;
	}
	return (int)result;
}
