/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_chunk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:54:34 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/29 22:54:36 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "fdf.h"
#include "libft.h"

/**
 * @brief Advances the parser to the next lnine, updating coordinates and
 * handling map consistency.
 * 
 * This function  increments the y-coordinate and the map height, resets the
 * x-coordinate to 0,and ensures the map's witdth is consistent across lines
 * if teh width has not been set yet, it sets it based on the numbers of values
 * read in the current line. It checks for errors if too many values are read
 * and fills missing vlaues with defaults if too few are read,
 * potentially reallocating memory as needed.
 * @param p Pointer to the parser structure parsing state
 * @param fdf pointer to the application structure containing map data
 * @return true if the line advancement is successful; false if an 
 * error occurs (e.g., bad map or reallocation failure.)
 */
static bool	advance_line(t_parser *p, t_app *fdf)
{
	p->x = 0;
	++p->y;
	++fdf->height;
	if (!p->width_set)
	{
		p->width_set = true;
		fdf->width = (int)p->values_read;
	}
	else if (p->values_read > (size_t)p->y * fdf->width)
	{
		ft_fprintf(STDERR_FILENO, "Error: Bad map\n");
		return (false);
	}
	else if (p->values_read < (size_t)p->y * fdf->width)
	{
		if (!realloc_all(p, fdf))
			return (false);
		while (p->values_read < (size_t)p->y * fdf->width)
		{
			fdf->points[p->values_read] = 0;
			fdf->color[p->values_read] = 0xffffff;
			++p->values_read;
		}
	}
	return (true);
}

/**
 * @brief Stores the parsed z-value and color into the map arrays
 * and updates min/max z bounds.
 * 
 * PURPOSE: this function assigns the current color 
 * and z-value (cast to float) to the respective arrays
 * int the application structure at the index of values_read. It
 * updates the minimum and maximum z-values if this is the first value
 * or if the current z exceeds the current bounds. it then
 * sets the z_set flag to true, increments the values_read counter, 
 * and increments the x-coordinate
 * 
 * @param p Pointer to the parsre containing the current z-value, color
 * and parsing state
 * @param fdf Pointer to the application structure containing the points
 * and color arrays.
 */
static inline void	push_value(t_parser *p, t_app *fdf)
{
	fdf->color[p->values_read] = p->color;
	fdf->points[p->values_read] = (float)p->z;
	if (!p->z_set || p->z < p->min_z)
		p->min_z = p->z;
	if (!p->z_set || p->z > p->max_z)
		p->max_z = p->z;
	p->z_set = true;
	++p->values_read;
	++p->x;
}

/**
 * @brief Parses a single value (z-coordinate and opt color)
 * from the buffer
 * 
 * PURPOSE: This function attempts to parse an integer z-value
 * from the buffer starting at index *i using ft_strntoi.
 * it advances the index by the length of the parsed number.
 * then it calls parse_color to handle any optional color
 * information. Finally it checks if the next character
 * (if not at the end of the chunk) is a delimiter to
 * ensure proper parsing boundaries
 * 
 * @param p Pointer to the parser structure containing the buffer
 * and parsing state
 * @param chunk_size the size of the buffer chunk being parsed
 * @param i Pointer to the current index in the buffer; updateed
 * upon succesful parsing
 * @return true if the value is parsed succesfully;false if parsing
 * fails (e.g., invalid number, color, or delimiter)
 */
static inline bool	parse_value(
	t_parser *p,
	size_t chunk_size,
	size_t *i
) {
	int		number_len;

	number_len = ft_strntoi(&p->z, &p->buf[*i], chunk_size - *i);
	if (number_len == 0)
		return (false);
	*i += number_len;
	if (!parse_color(p, chunk_size, i))
		return (false);
	if (*i + number_len < chunk_size && !is_delim(p->buf[*i]))
		return (false);
	return (true);
}

/**
 * @brief Parses a chunk of the input buffer, extracting z-values
 * and colors, and handling line advancements.
 * 
 * This function iterates through the buffer chunk, skipping delimiters
 * parsing individual values (z-coordinates and optional colors),
 * reallocating memory as needed, storing the parsed data, and 
 * advancing to the next line when encountering newlines or the end
 * of the chunk. It ensures proper handling of spaces and delimiters
 * to maintain parsing integrity
 * 
 * @param p pointer to the parser structure containing the buffer
 * and parsing state
 * @param fdf Pointer to the application structure containing the
 * map data arrays
 * @param chunk_size The size of the buffer chunk being parsed
 * @return true if the chunk is parsed successfully; false if an error
 * occurs during parsing, reallocation, or line advancement
 */
bool	parse_chunk(t_parser *p, t_app *fdf, size_t chunk_size)
{
	size_t	i;

	i = 0;
	while (true)
	{
		i = skip_delim(p->buf, chunk_size, i);
		if (i == chunk_size)
			break ;
		if (!parse_value(p, chunk_size, &i))
			return (false);
		if (!realloc_all(p, fdf))
			return (false);
		push_value(p, fdf);
		while (i < chunk_size && p->buf[i] == ' ')
			++i;
		if (((i == chunk_size && p->bytes_read == 0) || p->buf[i] == '\n')
			&& !advance_line(p, fdf))
			return (false);
	}
	return (true);
}

/**
 * @brief Applies a default height-based color palette to the map if
 * no explicit colors are set
 * 
 * This functin check if the colors and points arrays are valid. 
 * it scans all points to determine if any explicit colors
 * (non default white, 0xFFFFFF) are present. if explicit color exist,
 * it returns without changes.Otherwise, it calculates teh range of z-values,
 * initializes a default color pivot structure, and applies a height-base
 * palette to the points using the range.
 * 
 * @param fdf Pointer to the application structure containing the map
 * data, colors, and z-values.
 */
void	apply_default_height_palette(t_app *fdf)
{
	int		total;
	int		i;
	float	range;
	t_pivot	color;
	bool	has_explicit_color;

	if (fdf->color == NULL || fdf->points == NULL)
		return ;
	total = fdf->width * fdf->height;
	i = -1;
	has_explicit_color = false;
	while (++i < total)
	{
		if (fdf->color[i] != 0xFFFFFF)
		{
			has_explicit_color = true;
			break ;
		}
	}
	if (has_explicit_color)
		return ;
	range = (float)(fdf->max_z - fdf->min_z);
	if (range == 0)
		range = 1.0f;
	(init_pivot_colors(&color), apply_palette_to_points(fdf, &color, range));
}
