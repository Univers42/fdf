/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_mult.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:02:24 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/04 14:44:04 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "algebra.h"
#include "../stdio/ft_stdio.h"

int	ft_tab_mult(int x)
{
	int	i;

	i = 0;
	while (++i < 10)
		ft_printf("%d x %d = %d\n", x, i, ft_multiply(x, i));
	return (0);
}

//int main(int argc, char **argv)
//{
//    if (argc != 2)
//        return 1;
//    int x = atoi(argv[1]);
//    ft_tab_mult(x);
//    return 0;
//}