/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_super_trim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 22:38:41 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 01:15:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_stddef.h"
#include "ft_ctype.h"

static int	should_skip(char c, int flags)
{
	if ((flags & TRIM_SPACES)
		&& (c == ' ' || c == '\t' || c == '\n' || c == '\r'))
		return (1);
	if ((flags & TRIM_NUMS) && (c >= '0' && c <= '9'))
		return (1);
	if ((flags & TRIM_RADIX)
		&& ((c >= '0' && c <= '9')
			|| (c >= 'a' && c <= 'f')
			|| (c >= 'A' && c <= 'F')))
		return (1);
	return (0);
}

void	ft_super_trim(t_addr *ptr, int flags)
{
	while (*(char *)*ptr && should_skip(*(char *)*ptr, flags))
		*ptr = (char *)*ptr + 1;
}

int	parse_sign(t_addr *ptr)
{
	int	sign;

	sign = 1;
	if (*(char *)*ptr == '-')
	{
		sign = -1;
		*ptr = (char *)*ptr + 1;
	}
	else if (*(char *)*ptr == '+')
		*ptr = (char *)*ptr + 1;
	return (sign);
}

int	parse_int(t_addr *ptr)
{
	int	val;

	val = 0;
	while (*(char *)*ptr >= '0' && *(char *)*ptr <= '9')
	{
		val = val * 10 + (*(char *)*ptr - '0');
		*ptr = (char *)*ptr + 1;
	}
	return (val);
}
