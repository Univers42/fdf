/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 02:50:58 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 03:02:41 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	hex_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

/* Return number of consumed characters; updates *acc and *digits */
int	accumulate_hex(uint32_t *acc, char *cur, char *end, int *digits)
{
	int	val;
	int	len;

	len = 0;
	*digits = 0;
	while (cur < end)
	{
		val = hex_digit(*cur);
		if (val < 0 || *digits == 8)
			break ;
		*acc = (*acc << 4) | (uint32_t)val;
		++(*digits);
		++cur;
		++len;
	}
	return (len);
}

int	strntohex(uint32_t *n, char *str, char *end)
{
	uint32_t	acc;
	int			digits;
	char		*cur;

	cur = str;
	if (cur >= end)
		return (0);
	(void)skip_prefix(&cur, end);
	acc = 0;
	digits = 0;
	cur += accumulate_hex(&acc, cur, end, &digits);
	if (digits == 0)
		return (0);
	*n = acc;
	return ((int)(cur - str));
}
