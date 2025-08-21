/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:36:07 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

int	get_left_child(int parent_index)
{
	return (parent_index * 2 + 1);
}

int	get_right_child(int parent_index)
{
	return (parent_index * 2 + 2);
}

int	is_valid_index(int index, int size)
{
	if (index >= 0 && index < size)
		return (1);
	return (0);
}

int	get_tree_height(int size)
{
	int	height;
	int	nodes_count;

	height = 0;
	nodes_count = 1;
	while (nodes_count <= size)
	{
		height++;
		nodes_count *= 2;
	}
	return (height);
}

void	print_spaces(int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		ft_printf(" ");
		i++;
	}
}
