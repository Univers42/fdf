/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:02:06 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algebra.h"
#include "ft_stdlib.h"
#include "ft_stdio.h"
#include <stdio.h>

void	init_op_map(char *op_idx_map)
{
	int	i;

	i = 0;
	while (i < 128)
	{
		op_idx_map[i] = -1;
		i++;
	}
	op_idx_map['+'] = 0;
	op_idx_map['-'] = 1;
	op_idx_map['*'] = 2;
	op_idx_map['/'] = 3;
	op_idx_map['%'] = 4;
}

int	get_op_index(char sign)
{
	static char	op_idx_map[128];
	static int	initialized;

	if (!initialized)
	{
		init_op_map(op_idx_map);
		initialized = 1;
	}
	if ((unsigned char)sign >= 128)
		return (-1);
	return (op_idx_map[(unsigned char)sign]);
}

void	setup_operations(t_ops *op_funcs)
{
	op_funcs[0] = ft_add;
	op_funcs[1] = ft_subtract;
	op_funcs[2] = ft_multiply;
	op_funcs[3] = ft_divide;
	op_funcs[4] = ft_modulo;
}

void	do_op(int n1, char sign, int n2)
{
	int				res;
	unsigned int	op_map;
	t_ops			op_funcs[5];
	int				op_idx;

	op_map = 31;
	setup_operations(op_funcs);
	op_idx = get_op_index(sign);
	if (op_idx < 0 || !(op_map & (1u << op_idx)))
		return ;
	res = op_funcs[op_idx](n1, n2);
	ft_printf("%d %c %d = %d\n", n1, sign, n2, res);
}

//int	main(int argc, char **argv)
//{
//	char	sign;
//	int		x;
//	int		y;
//
//	if (argc != 4)
//		return (ft_putchar_fd('\n', 1), 1);
//	x = ft_atoi(argv[1]);
//	sign = argv[2][0];
//	y = ft_atoi(argv[3]);
//	do_op(x, sign, y);
//	return (0);
//}
