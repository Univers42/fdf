/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modulo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:02:16 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algebra.h"

int	ft_modulo(int a, int b)
{
	int				sign;
	unsigned int	ua;
	unsigned int	ub;
	int				i;

	if (b == 0)
		return (0);
	sign = 1;
	if (a < 0)
		sign = -1;
	ua = a;
	if (a < 0)
		ua = -a;
	ub = b;
	if (b < 0)
		ub = -b;
	i = 31;
	while (i >= 0)
	{
		if ((ua >> i) >= ub)
			ua = ft_subtract(ua, (ub << i));
		i--;
	}
	return (sign * ua);
}

//int main(int argc, char **argv)
//{
//    if (argc != 3)
//        return 1;
//    int a = atoi(argv[1]);
//    int b = atoi(argv[2]);
//   	ft_printf("%d %% %d = %d\n", a, b, ft_modulo(a, b));
//    return 0;
//}