/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:19:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algebra.h"

int	ft_power(int base, int exp)
{
	unsigned int	uexp;
	int				result;
	int				zero;

	result = 1;
	uexp = (unsigned int)exp;
	zero = (exp >> 31) & 1;
	while (uexp)
	{
		result *= ((base & -(uexp & 1)) | (1 & ~(-(uexp & 1))));
		base *= base;
		uexp >>= 1;
	}
	return (result & ~(-zero));
}

//int main(int argc, char **argv)
//{
//	if (argc != 3)
//		return 1;
//	int base = atoi(argv[1]);
//	int exp = atoi(argv[2]);
//	ft_printf("%d^%d = %d\n", base, exp, ft_power(base, exp));
//	return 0;
//}
//