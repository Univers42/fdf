/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:21:32 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/07/29 17:13:46 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stddef.h"
#include <stdlib.h>
#include "ft_stdlib.h"
/**
 * Calculates the number of digits in a hexadecimal number
 */
static size_t	ft_xtoa_len(unsigned long num)
{
	size_t	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num >= 1)
	{
		len++;
		num /= 16;
	}
	return (len);
}

/**
 * Converts a number to hexadecimal string representation
 */
static char	*ft_hex_to_str(unsigned long int num, char *str, size_t len)
{
	int		mod;

	str = ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	len--;
	while (len != (size_t)-1)
	{
		mod = num % 16;
		if (mod < 10)
			str[len] = mod + '0';
		else if (mod >= 10)
			str[len] = (mod - 10) + 'a';
		num = num / 16;
		len--;
	}
	return (str);
}

/**
 * Converts an unsigned long int to a hexadecimal string
 * If is_upper is 1, uppercase letters are used for A-F
 */
char	*ft_xtoa(unsigned long int num, int is_upper)
{
	size_t	len;
	char	*str;
	int		i;

	len = ft_xtoa_len(num);
	str = 0;
	str = ft_hex_to_str(num, str, len);
	if (!str)
		return (NULL);
	if (is_upper == 1)
	{
		i = 0;
		while (str[i])
		{
			if (str[i] >= 'a' && str[i] <= 'f')
				str[i] -= 32;
			i++;
		}
	}
	return (str);
}
