/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:02:18 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algebra.h"

int	ft_multiply(int x, int y)
{
	int	res;
	int	negative;
	int	ax;
	int	ay;

	res = 0;
	negative = (ft_is_negative(x) ^ ft_is_negative(y));
	ax = ft_abs(x);
	ay = ft_abs(y);
	while (ay > 0)
	{
		res += ft_add(0, ax) * (ay & 1);
		ax <<= 1;
		ay >>= 1;
	}
	res = (res ^ -negative) + negative;
	return (res);
}
//
//#include <stdio.h>
//#include <stdlib.h>
//
//int main(int argc, char *argv[])
//{
//    if (argc != 3)
//        return 1;
//    int x = atoi(argv[1]);
//    int y = atoi(argv[2]);
//   	ft_printf("%d * %d = %d\n", x, y, ft_multiply(x, y));
//    return 0;
//}
