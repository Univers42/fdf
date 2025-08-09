/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:27:28 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 03:02:29 by dlesieur         ###   ########.fr       */
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
bool	parse_buffered(t_parser *p, t_app *fdf, int fd)
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
	return (lerp_color(a, b, t));
}

void	init_pivot_colors(t_pivot *color)
{
	color->low = (void *)(uintptr_t)0x0000FF;
	color->mid = (void *)(uintptr_t)0x00FF00;
	color->high = (void *)(uintptr_t)0xFF0000;
}

uint32_t	get_palette_color(t_pivot *color, float t)
{
	if (t < 0.5f)
		return (blend_rgb(
				(uint32_t)(uintptr_t)color->low,
			(uint32_t)(uintptr_t)color->mid,
			t / 0.5f
		));
	else
		return (blend_rgb(
				(uint32_t)(uintptr_t)color->mid,
			(uint32_t)(uintptr_t)color->high,
			(t - 0.5f) / 0.5f
		));
}
