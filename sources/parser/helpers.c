/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 02:47:42 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/21 15:02:36 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "libft.h"
#include "fdf.h"

#define CUTOFF 214748364
#define HEXTABLE "0123456789abcdef"

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
	return (ok);
}

static inline bool	negative(const char *str, size_t *i, size_t max)
{
	bool	is_negative;

	is_negative = false;
	if (*i <= max && (str[*i] == '+' || str[*i] == '-'))
	{
		is_negative = str[*i] == '-';
		++*i;
	}
	return (is_negative);
}

int	ft_strntoi(int *n, char *str, size_t max)
{
	size_t			i;
	bool			is_negative;
	unsigned int	nlim;
	unsigned int	accumulator;

	i = 0;
	is_negative = negative(str, &i, max);
	nlim = 7;
	if (is_negative)
		nlim = 8;
	if (!ft_isdigit(str[i]))
		return (0);
	accumulator = 0;
	while (i <= max && ft_isdigit(str[i]))
	{
		if (accumulator > CUTOFF || (accumulator == CUTOFF
				&& (unsigned int)(str[i] - '0') > nlim))
			break ;
		accumulator = accumulator * 10 + (str[i] - '0');
		++i;
	}
	*n = (int)accumulator;
	if (is_negative)
		*n = (int)-accumulator;
	return ((int)i);
}

bool	skip_prefix(char **str, char *end)
{
	if (*str + 1 < end && **str == '0' && ((*str)[1] == 'x'
		|| (*str)[1] == 'X'))
	{
		*str += 2;
		return (true);
	}
	return (false);
}
