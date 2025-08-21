/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:31:46 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algebra.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

//int main(int argc, char **argv)
//{
//	if (argc != 2)
//		return 1;
//	int x = atoi(argv[1]);
//	ft_printf("abs(%d) = %d\n", x, ft_abs(x));
//	return 0;
//}