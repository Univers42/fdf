/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log10.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:32:14 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algebra.h"

int	ft_log10(int n)
{
	int	log;

	log = 0;
	while (n >= 10)
	{
		n /= 10;
		log++;
	}
	return (log);
}

//int main(int argc, char **argv)
//{
//    if (argc != 2)
//        return (1);
//    int n = atoi(argv[1]);
//    if (n < 0)
//        return (2);
//   	ft_printf("Log10 of %d is %d\n", n, ft_log10(n));
//    return (0);    
//}