/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:27:28 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 17:16:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include "fdf.h"
#include "libft/libft.h"

#define INPUT_BUF_SIZE 4096

static inline bool	find_chunk_end(
	t_parser *p,
	char *buf,
	size_t leftover,
	size_t *chunk_end
) {
	bool	delim_found;
	size_t	end;

	if (p->bytes_read == 0)
		end = leftover;
	else
	{
		end = leftover + p->bytes_read;
		delim_found = false;
		while (end-- > 0)
		{
			if (is_delim(buf[end]))
			{
				delim_found = true;
				break ;
			}
		}
		if (!delim_found)
		{
			ft_fprintf(STDERR_FILENO, "Error: file input value too long");
			return (false);
		}
	}
	*chunk_end = end;
	return (true);
}

/**
 * Chunks represent the parseable end of the buffer. Whatever is after chunk end
 * is copied to the front of the buffer.
 */
static inline bool	parse_buffered(t_parser *p, t_app *fdf, int fd)
{
	size_t			leftover;
	size_t			chunk_end;

	leftover = 0;
	while (true)
	{
		p->bytes_read = read(fd, p->buf + leftover, INPUT_BUF_SIZE - leftover);
		if (p->bytes_read < 0)
			return (perror("read: "), false);
		if (p->bytes_read == 0 && leftover == 0)
			break ;
		if (!find_chunk_end(p, p->buf, leftover, &chunk_end))
			return (false);
		if (!parse_chunk(p, fdf, chunk_end))
			return (false);
		if (p->bytes_read == 0)
			break ;
		ft_memmove(p->buf, &p->buf[chunk_end + 1],
			leftover + p->bytes_read - chunk_end - 1);
		leftover = leftover + p->bytes_read - chunk_end - 1;
	}
	fdf->min_z = p->min_z;
	fdf->max_z = p->max_z;
	return (true);
}

static inline uint32_t	blend_rgb(uint32_t a, uint32_t b, float t)
{
	uint8_t	ar = (a >> 16) & 0xFF, ag = (a >> 8) & 0xFF, ab = a & 0xFF;
	uint8_t	br = (b >> 16) & 0xFF, bg = (b >> 8) & 0xFF, bb = b & 0xFF;
	uint8_t	r = ar + (uint8_t)((br - ar) * t);
	uint8_t	g = ag + (uint8_t)((bg - ag) * t);
	uint8_t	bc = ab + (uint8_t)((bb - ab) * t);
	return (r << 16) | (g << 8) | bc;
}

static void	apply_default_height_palette(t_app *fdf)
{
	int			total;
	int			i;
	float		range;
	uint32_t	c_low, c_mid, c_high;

	if (fdf->color == NULL || fdf->points == NULL)
		return ;
	/* Heuristic: if at least one non-white color exists, skip auto palette */
	total = fdf->width * fdf->height;
	i = 0;
	while (i < total)
	{
		if (fdf->color[i] != 0xFFFFFF)
			return ;
		++i;
	}
	range = (float)(fdf->max_z - fdf->min_z);
	if (range == 0)
		range = 1.0f;
	c_low = 0x0000FF;
	c_mid = 0x00FF00;
	c_high = 0xFF0000;
	i = 0;
	while (i < total)
	{
		float z = fdf->points[i];
		float t = (z - fdf->min_z) / range;
		uint32_t c;
		if (t < 0.5f)
			c = blend_rgb(c_low, c_mid, t / 0.5f);
		else
			c = blend_rgb(c_mid, c_high, (t - 0.5f) / 0.5f);
		fdf->color[i] = c;
		++i;
	}
}

bool	parse_file(t_app *fdf, char *filename)
{
	bool		ok;
	t_parser	parser;
	int			fd;

	ok = false;
	parser = (t_parser){0};
	parser.buf = malloc(INPUT_BUF_SIZE);
	fd = open(filename, O_RDONLY);
	if (fd >= 0)
	{
		if (parser.buf != NULL)
			ok = parse_buffered(&parser, fdf, fd);
		close(fd);
	}
	else
		perror("open: ");
	free(parser.buf);
	if (ok)
		apply_default_height_palette(fdf);
	return (ok);
}
