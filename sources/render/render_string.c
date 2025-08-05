/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:27:02 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:27:03 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

#define SCALE 3

static inline void	render_scaled_bit(t_draw_char_params *p, int row, int col)
{
	int	i;
	int	j;
	int	srow;
	int	scol;

	i = 0;
	while (i < SCALE)
	{
		j = 0;
		while (j < SCALE)
		{
			srow = row * SCALE + i + p->y;
			scol = col * SCALE + j + p->x;
			p->buf[srow * WINDOW_WIDTH + scol] = p->color;
			++j;
		}
		++i;
	}
}

static inline void	render_char(t_draw_char_params *p, char c)
{
	const uint8_t	*glyph;
	int				row;
	int				col;

	glyph = get_glyph(c);
	row = 0;
	while (row < 8)
	{
		col = 0;
		while (col < 8)
		{
			if (glyph[row] & (1 << col))
				render_scaled_bit(p, row, col);
			++col;
		}
		++row;
	}
}

void	render_string(char *str, uint32_t *buf, int x, int y)
{
	while (*str)
	{
		render_char(&(t_draw_char_params){
			.x = x, .y = y, .buf = buf, .color = 0x00ffffff
		}, *str);
		++str;
		x += 8 * SCALE;
	}
}
