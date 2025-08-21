/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:38:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 02:19:03 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Optimized gradient calculation using integer arithmetic.
** Split into helpers to satisfy norm (max 5 vars per function).
*/

static void	extract_rgb(int color, int dst[3])
{
	dst[0] = (color >> 16) & 0xFF;
	dst[1] = (color >> 8) & 0xFF;
	dst[2] = color & 0xFF;
}

static int	interp_channel(int s, int e, int pix, int len)
{
	return (s + ((e - s) * pix) / len);
}

static int	clamp_channel(int v)
{
	if (v < 0)
		return (0);
	if (v > 255)
		return (255);
	return (v);
}

int	gradient(int startcolor, int endcolor, int len, int pix)
{
	int	start_rgb[3];
	int	end_rgb[3];
	int	out_rgb[3];
	int	i;

	if (len <= 0 || pix < 0 || pix > len)
		return (startcolor);
	if (startcolor == endcolor)
		return (startcolor);
	extract_rgb(startcolor, start_rgb);
	extract_rgb(endcolor, end_rgb);
	i = 0;
	while (i < 3)
	{
		out_rgb[i] = interp_channel(start_rgb[i], end_rgb[i], pix, len);
		out_rgb[i] = clamp_channel(out_rgb[i]);
		i += 1;
	}
	return ((out_rgb[0] << 16) | (out_rgb[1] << 8) | out_rgb[2]);
}
