/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer_write_format.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:48:48 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 01:53:19 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "writer.h"
#include "ft_ctype.h"

bool	writer_write_str(t_writer *w, const char *str)
{
	while (*str != '\0' && writer_putchar(w, *str))
		++str;
	return (w->error >= 0);
}

bool	writer_pad_with(t_writer *w, char c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (!writer_putchar(w, c))
			return (false);
		++i;
	}
	return (true);
}

void	writer_write_hex(t_writer *w, size_t n, size_t len, bool upper)
{
	static char	hex_map[] = {"0123456789abcdef"};
	char		c;

	while (len--)
	{
		c = hex_map[(n >> (4 * len)) & 0xf];
		if (upper)
			c = ft_toupper(c);
		writer_putchar(w, c);
	}
}

void	writer_write_uint(t_writer *w, unsigned int n, size_t len)
{
	char	c;
	int		magnitude;

	if (len == 0)
		return ;
	magnitude = 1;
	while (--len)
		magnitude *= 10;
	while (magnitude != 0)
	{
		c = (n / magnitude) + '0';
		writer_putchar(w, c);
		n %= magnitude;
		magnitude /= 10;
	}
}
