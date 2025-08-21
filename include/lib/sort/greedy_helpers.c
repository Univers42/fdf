/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 18:14:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

void	initialize_stacks(t_stck *a, t_stck *b, int *arr, int size)
{
	int	i;

	a->data = malloc(size * sizeof(int));
	a->size = size;
	b->data = malloc(size * sizeof(int));
	b->size = 0;
	i = 0;
	while (i < size)
	{
		a->data[i] = arr[i];
		i++;
	}
}

void	copy_result_back(int *arr, t_stck *a, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		arr[i] = a->data[i];
		i++;
	}
}
