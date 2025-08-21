/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log10.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:41:10 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/07/29 17:14:42 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Calculate the base-10 logarithm of a number (number of digits - 1)
 * 
 * @param n The number to calculate log10 of
 * @return The base-10 logarithm of n, or -1 for n=0
 */
int	ft_log10(int n)
{
	int	count;

	if (n == 0)
		return (-1);
	if (n < 0)
		n = -n;
	count = 0;
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}
