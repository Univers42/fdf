/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:27:28 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/29 18:53:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include "fdf.h"
#include "libft.h"

void	color_snapshot_restore(t_app *fdf);
void	color_snapshot_capture(t_app *fdf);

/**
 * @brief Finds the end fo teh parseable chunk in the buffer by locating a
 * delimiter.
 * 
 * This function determines the end of the current parseable chunk in th
 * buffer. If it's the first read.
 * (bytes_read == 0), it sets the ened to the leftover size. Otherwise it
 * starts
 * from the total buffer size.
 * (leftover + bytes_read) and searches backwards for a delimiter character.
 * if no delimiter is found,
 * it reports an error for overly long input values and return false. The found
 * end index is stored in *chunk_end.
 * @param p Pointer to the parser structure containing read state
 * @param buf The buffer array being parsed
 * @param leftover the number of leftover bytes from previous reads
 * @param chunk_end Pointer to a size_t where the chunk end index will be
 * stored
 * @return true if a valid chunk end is found; false if no delimiter is
 * found (error case)
 */
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
 * @brief parses the file contents i buffered chunks, handling
 * partial read and leftovers.
 * 
 * This function reads the file in chunks into a buffer, ensuring
 * that parsing occurs only on complete
 * parseable segments (up to a delimiter). it manages leftover data
 * from previous reads by prepending it
 * to new reads. for each chunk, it fins a safe aend point, parses
 * the chunk, and moves any remaining.
 * Data to the front of the buffer for the next iteration. Upon
 * completion, it transfers min/max z values
 * to the app structure and captures a color snapshot. The loop
 * continues until the file is fully read.
 * 
 * @param p Pointer to the parser structure containing buffer and
 * state.
 * @param fdf Pointer to the application structure where parsed data
 * is stored
 * @param fd the file descriptor of the open file being parsed
 * @return true if the buffered parsing completes successfully;
 * false if an error occurs (e.g., read failure, parsing error)
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
	color_snapshot_capture(fdf);
	return (true);
}

/**
 * @brief blends two RGB colors using linear interpolation
 * 
 * This function performs linear interpolation between two 32-bit
 * RGB colors, delegating the actual computation to the lerp_color
 * function. The interpolation factor t ranges from 0.0
 * (fully color a) to 1.0 (fully color b).
 * @param a The first RGB color as 32-bit unsigned integer
 * @param b The second RGB color as 32-bit unsigned integer
 * @param t The interpolation factor, typically between 0.0 and 1.0
 * @return the blended RGB color as 32-bit unsigned integer
 */
static inline uint32_t	blend_rgb(uint32_t a, uint32_t b, float t)
{
	return (lerp_color(a, b, t));
}

/**
 * @brief initializes the pivot colors for the height-based
 * palette
 * 
 * This function sets the low, mid, and high pivot colors to
 * predefined RGB values:
 * low (blue:0x0000ff)
 * high (red:0xff0000)
 * mid (green:0x00ff00)
 * These pivots are used in color interpolationo for height
 * based coloring for the map
 * @param color Pointer to the t_pivot structure where the
 * colors will be stored
 */
void	init_pivot_colors(t_pivot *color)
{
	color->low = (void *)(uintptr_t)0x0000FF;
	color->mid = (void *)(uintptr_t)0x00FF00;
	color->high = (void *)(uintptr_t)0xFF0000;
}

/**
 * @brief retrieves a color from the height based paletter using
 * pivot colors.
 * 
 * This function  interpolates the pivot colors (low, mig, high)
 * based on the normalized height factor t (ranging from 0.0 to
 * 1.0). If it is less than 0.5, it blends between low and mid
 * colors: otherwise, it blends between mid, and high colors.
 * The blending is performed using linear interpolation
 * via teh blend rgb function
 * 
 * @param color Pointer to the t_pivot structure containing
 * the low, mid, and high pivot colors.
 * @param t the normalized height factor, tipically between 0.0
 * (low) and 1.0 (high)
 * @return The interpolated RGB color as a 32-bit unsigned integer
 * @note see the obsidian section type of variables for details on
 * color representation
 */
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
