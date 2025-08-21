/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_prime_sum.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:02:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algebra.h"

int	ft_add_prime_sum(int x)
{
	int	sum;
	int	i;

	i = 1;
	if (x < 2)
		return (0);
	while (++i <= x)
	{
		if (ft_is_prime(i))
			sum = ft_add(sum, i);
	}
	return (sum);
}

//int main(int argc, char **argv)
//{
//    if (argc != 2)
//    {
//        write(1, "\n", 1);
//        return (1);
//    }
//    int x = ft_atoi(argv[1]);
//   	ft_printf("The sum of prime numbers ""
//up to %d is: %d\n", x, ft_add_prime_sum(x));
//    return (0);
//}