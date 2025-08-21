/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pigeonhole_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/11 10:42:12 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

static void	initialize_holes(int *holes, int range)
{
	int	i;

	i = 0;
	while (i < range)
	{
		holes[i] = 0;
		i++;
	}
}

static void	count_elements(int *arr, int *holes, int size, int min)
{
	int	i;

	i = 0;
	while (i < size)
	{
		holes[arr[i] - min]++;
		i++;
	}
}

static void	place_elements(int *arr, int *holes, int range, int min)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < range)
	{
		while (holes[i]-- > 0)
		{
			arr[j++] = i + min;
		}
		i++;
	}
}

void	pigeonhole_sort(int *arr, int size)
{
	int	min;
	int	max;
	int	range;
	int	*holes;

	if (!arr || size <= 1)
		return ;
	min = get_min(arr, size);
	max = get_max(arr, size);
	range = max - min + 1;
	holes = malloc(range * sizeof(int));
	if (!holes)
		return ;
	initialize_holes(holes, range);
	count_elements(arr, holes, size, min);
	place_elements(arr, holes, range, min);
	free(holes);
}
