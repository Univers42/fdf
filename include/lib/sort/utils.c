/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/01/15 10:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

int	get_min(int *arr, int size)
{
	int	min_val;
	int	i;

	if (!arr || size <= 0)
		return (0);
	min_val = arr[0];
	i = 1;
	while (i < size)
	{
		if (arr[i] < min_val)
			min_val = arr[i];
		i++;
	}
	return (min_val);
}

int	get_max(int *arr, int size)
{
	int	max_val;
	int	i;

	if (!arr || size <= 0)
		return (0);
	max_val = arr[0];
	i = 1;
	while (i < size)
	{
		if (arr[i] > max_val)
			max_val = arr[i];
		i++;
	}
	return (max_val);
}

void	handle_duplicates(int *arr, int *pos, int item)
{
	if (!arr || !pos)
		return ;
	while (*pos < 10000 && item == arr[*pos])
		(*pos)++;
}
