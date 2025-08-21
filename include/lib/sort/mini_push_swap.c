/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_push_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/11 10:58:40 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

static void	binary_search_tag(int *sorted, int *arr, int size, int i)
{
	int	left;
	int	right;
	int	mid;
	int	tag;

	left = 0;
	right = size - 1;
	tag = 0;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (sorted[mid] == arr[i])
		{
			tag = mid;
			break ;
		}
		else if (sorted[mid] < arr[i])
			left = mid + 1;
		else
			right = mid - 1;
	}
	arr[i] = tag;
}

static void	tag_array(int *arr, int size, int *tag_to_value)
{
	int	*sorted;
	int	i;

	sorted = malloc(size * sizeof(int));
	memcpy(sorted, arr, size * sizeof(int));
	qsort(sorted, size, sizeof(int), cmp_int);
	i = 0;
	while (i < size)
	{
		tag_to_value[i] = sorted[i];
		i++;
	}
	i = 0;
	while (i < size)
	{
		binary_search_tag(sorted, arr, size, i);
		i++;
	}
	free(sorted);
}

static void	push_elements(int *src, int *src_size, int *dest, int *dest_size)
{
	int	i;

	if (*src_size == 0)
		return ;
	i = *dest_size;
	while (i > 0)
	{
		dest[i] = dest[i - 1];
		i--;
	}
	dest[0] = src[0];
	(*dest_size)++;
	i = 0;
	while (i < *src_size - 1)
	{
		src[i] = src[i + 1];
		i++;
	}
	(*src_size)--;
}

void	mini_pushswap_hybrid(int *arr, int size, int *tag_to_value)
{
	int	*a;
	int	*b;
	int	a_size;
	int	b_size;
	int	i;

	tag_array(arr, size, tag_to_value);
	a = malloc(size * sizeof(int));
	b = malloc(size * sizeof(int));
	a_size = size;
	b_size = 0;
	memcpy(a, arr, size * sizeof(int));
	while (a_size > 0)
		push_elements(a, &a_size, b, &b_size);
	while (b_size > 0)
		push_elements(b, &b_size, a, &a_size);
	i = 0;
	while (i < size)
	{
		arr[i] = a[i];
		i++;
	}
	free(a);
	free(b);
}
