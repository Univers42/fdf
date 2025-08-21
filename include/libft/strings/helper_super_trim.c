/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_super_trim.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:10:32 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 01:15:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_stddef.h"
#include "ft_ctype.h"

int	cumul_value(t_addr *ptr, t_addr target)
{
	int	*val;
	int	sign;

	val = (int *)target;
	sign = parse_sign(ptr);
	*val = parse_int(ptr) * sign;
	return (*val);
}

int	extract_hex(t_addr *ptr, t_addr result)
{
	int	*color;
	int	digit;

	color = (int *)result;
	*color = 0;
	if (*(char *)*ptr == '0'
		&& (*(char *)(*ptr + 1) == 'x' || *(char *)(*ptr + 1) == 'X'))
	{
		*ptr = (char *)*ptr + 2;
		while (*(char *)*ptr)
		{
			digit = hex_digit(*(char *)*ptr);
			if (digit == -1)
				break ;
			*color = *color * 16 + digit;
			*ptr = (char *)*ptr + 1;
		}
	}
	else
		*color = DEFAULT_WHITE;
	return (*color);
}

void	advance_ptr(t_addr *ptr, char delimiter)
{
	while (*(char *)*ptr && *(char *)*ptr != delimiter)
		*ptr = (char *)*ptr + 1;
	if (*(char *)*ptr == delimiter)
		*ptr = (char *)*ptr + 1;
}
