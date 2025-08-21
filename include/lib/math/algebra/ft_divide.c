/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_divide.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:02:04 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/04 14:40:48 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algebra.h"

static void	ft_divide_loop(unsigned int *a,
							unsigned int b,
							unsigned int *result)
{
	int	i;

	i = 31;
	while (i >= 0)
	{
		if ((*a >> i) >= b)
		{
			*a -= (b << i);
			*result |= (1U << i);
		}
		i--;
	}
}

int	ft_divide(int dividend, int divisor)
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	result;
	int				sign;

	if (divisor == 0)
		return (0);
	sign = 1;
	if ((dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0))
		sign = -1;
	if (dividend < 0)
		a = -dividend;
	else
		a = dividend;
	if (divisor < 0)
		b = -divisor;
	else
		b = divisor;
	result = 0;
	ft_divide_loop(&a, b, &result);
	return (sign * (int)result);
}
