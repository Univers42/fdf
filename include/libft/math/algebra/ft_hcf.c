/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hcf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:02:20 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algebra.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_hcf(int x, int y)
{
	if (y == 0)
		return (x);
	return (ft_hcf(y, x % y));
}

//int main(int argc, char **argv)
//{
//    if (argc != 3)
//        return 1;
//    int x = atoi(argv[1]);
//    int y = atoi(argv[2]);
//   	ft_printf("HCF of %d and %d is %d\n", x, y, ft_hcf(x, y));
//    return 0;
//}