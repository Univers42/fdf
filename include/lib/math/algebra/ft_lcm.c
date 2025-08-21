/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lcm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:02:12 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algebra.h"

int	ft_lcm(int x, int y)
{
	int	hcf;

	hcf = ft_hcf(x, y);
	if (hcf == 0)
		return (0);
	return ((x / hcf) * y);
}

//int main(int argc, char **argv)
//{
//    if (argc != 3)
//        return 1;
//    int a = atoi(argv[1]);
//    int b = atoi(argv[2]);
//   	ft_printf("LCM of %d and %d is %d\n", a, b, ft_lcm(a, b));
//    return 0;
//}
