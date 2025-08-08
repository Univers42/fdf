/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>            // added for realloc
#include <stdint.h>            // uint32_t

bool	realloc_all(t_parser *p, t_app *fdf)
{
	size_t	new_cap;
	float		*new_points;
	uint32_t	*new_colors;

	if (p->values_read < p->arr_capacity)
		return (true);
	new_cap = (p->arr_capacity == 0) ? 4096 : p->arr_capacity * 2;
	new_points = (float *)realloc(fdf->points, new_cap * sizeof(float));
	if (!new_points)
		return (false);
	new_colors = (uint32_t *)realloc(fdf->color, new_cap * sizeof(uint32_t));
	if (!new_colors)
		return (false);
	fdf->points = new_points;
	fdf->color = new_colors;
	p->arr_capacity = new_cap;
	return (true);
}

bool	parse_color(t_parser *p, size_t chunk_size, size_t *i)
{
	int	hex_len;

	if (*i < chunk_size && p->buf[*i] == ',')
	{
		++*i;
		hex_len = strntohex(&p->color, &p->buf[*i], p->buf + chunk_size);
		if (hex_len <= 0)
			return (false);
		*i += hex_len;
	}
	else
		p->color = 0xffffff;
	return (true);
}

bool	is_delim(char c)
{
	return (c == ' ' || c == '\n');
}

int	skip_delim(char *buf, int end, int i)
{
	while (i < end && is_delim(buf[i]))
		++i;
	return (i);
}
