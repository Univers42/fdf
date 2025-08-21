/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:20:10 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/07/29 17:14:06 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stddef.h"
#include <stdlib.h>
/**
 * Counts the number of digits in an unsigned integer
 */
static int	ft_count_udigits(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

/**
 * Converts an unsigned integer to a string
 */
char	*ft_utoa(unsigned int n)
{
	char	*str;
	int		digits;
	int		i;

	digits = ft_count_udigits(n);
	str = (char *)malloc(sizeof(char) * (digits + 1));
	if (!str)
		return (NULL);
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	i = digits - 1;
	str[digits] = '\0';
	while (n)
	{
		str[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	return (str);
}
