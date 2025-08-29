/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:02:02 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/28 21:14:22 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algebra.h"

int	ft_add(int x, int y)
{
	int	carry;

	while (y != 0)
	{
		carry = x & y;
		x ^= y;
		y = carry << 1;
	}
	return (x);
}

//int main(int argc, char **argv)
//{
//	if (argc != 3)
//		return 1;
//	int n1 = atoi(argv[1]);
//	int n2 = atoi(argv[2]);
//	ft_printf("%d + %d = %d\n", n1, n2, ft_add(n1, n2));
//	return 0;
//}
