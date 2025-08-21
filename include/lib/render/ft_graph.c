/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:05:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/04 00:36:48 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"
#include "../stdio/ft_stdio.h"

static void	print_graph_row(int *values, int count, t_graph_params params)
{
	int	i;
	int	bar_height;

	i = 0;
	while (i < count)
	{
		bar_height = (values[i] * params.max_height) / params.max_val;
		if (bar_height >= params.row)
			ft_printf("%s█%s", GREEN_TERM, RESET_TERM);
		else
			ft_printf(" ");
		i++;
	}
	ft_printf("\n");
}

static int	find_max_value(int *values, int count)
{
	int	max_val;
	int	i;

	max_val = 0;
	i = 0;
	while (i < count)
	{
		if (values[i] > max_val)
			max_val = values[i];
		i++;
	}
	return (max_val);
}

void	ft_print_graph(int *values, int count, int max_height)
{
	t_graph_params	params;
	int				row;
	int				i;

	params.max_val = find_max_value(values, count);
	params.max_height = max_height;
	row = max_height;
	while (row > 0)
	{
		params.row = row;
		print_graph_row(values, count, params);
		row--;
	}
	i = 0;
	while (i < count)
	{
		ft_printf("%d", values[i] % 10);
		i++;
	}
	ft_printf("\n");
}
