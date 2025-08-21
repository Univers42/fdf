/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:02:14 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algebra.h"

int	ft_max(int a, int b)
{
	int	diff;
	int	mask;

	diff = ft_subtract(a, b);
	mask = diff >> (sizeof(int) * 8 - 1);
	return ((a & ~mask) | (b & mask));
}
//
//int main(int argc, char **argv)
//{
//    if (argc != 3)
//        return 1;
//    int a = atoi(argv[1]);
//    int b = atoi(argv[2]);
//   	ft_printf("max(%d, %d) = %d\n", a, b, ft_max(a, b));
//    return 0;
//}