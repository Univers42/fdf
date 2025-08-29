/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 02:33:35 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/29 13:55:50 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <stdint.h>

bool	ft_realloc_shrink_to(void **ptr, size_t elem_size,
			size_t *cap, size_t new_cap);

/**
 *	my header exposes ft_realloc_shrink_to(ptr_pp, elem_size, cap_p, new_cap)
 *  built on ft_realloc()
 * @note
 * Track old capacity before growing
 * Grow points first; on failure, return false.
 * Try tog grow colors, if this fails, rollback to old capacity, then
 * return false.
 * Commit p->arr_capacity only after both succeed.
 * 	
 *	If growing points then colors and colors fails,
 *	call ft_realloc_shrink_to
 *	on points back to the old capacity before returning false.
 *	
 */
bool	realloc_all(t_parser *p, t_app *fdf)
{
	size_t		old_cap;
	size_t		new_cap;
	size_t		points_cap;
	size_t		colors_cap;

	if (p->values_read < p->arr_capacity)
		return (true);
	old_cap = p->arr_capacity;
	if (old_cap == 0)
		new_cap = 4096;
	else
		new_cap = old_cap * 2;
	points_cap = old_cap;
	if (!ft_realloc_shrink_to((void **)&fdf->points, sizeof(float),
			&points_cap, new_cap))
		return (false);
	colors_cap = old_cap;
	if (!ft_realloc_shrink_to((void **)&fdf->color, sizeof(uint32_t),
			&colors_cap, new_cap))
		return ((void)ft_realloc_shrink_to((void **)&fdf->points, sizeof(float),
				&points_cap, old_cap), false);
	p->arr_capacity = new_cap;
	return (true);
}

/**
 * parse_color
 * @brief
 * boundary protaction and verify delimiter ','
 * then convert the str to hex bease on size of chunk
 * parse color set the p->color to the current color
 * if encountered. Otherwise will set to the default color which
 * is 0xffffff
 * @param p pointer to parser structure 
 * @param chunk_size self explanatory
 * @param i the pointer of index
 * @return bool
 */
bool	parse_color(t_parser *p, size_t chunk_size, size_t *i)
{
	int	hex_len;

	if (*i < chunk_size && p->buf[*i] == ATT_DELIMITER)
	{
		++*i;
		hex_len = strntohex(&p->color, &p->buf[*i], p->buf + chunk_size);
		if (hex_len <= 0)
			return (false);
		*i += hex_len;
	}
	else
		p->color = COLOR_DEFAULT;
	return (true);
}

/**
 * @param c
 * @return true or false
 * helper to skip delimitation when recognized.
 */
bool	is_delim(char c)
{
	return (c == ' ' || c == '\n');
}

/**
 * @brief it it teh current helper function 
 * that skip efficiently in-place the limitation
 * @param bufcd
 * @param end
 * @param i
 * @return the next indices 
 */
int	skip_delim(char *buf, int end, int i)
{
	while (i < end && is_delim(buf[i]))
		++i;
	return (i);
}
