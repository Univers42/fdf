/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coktail_shaker_sort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:15:27 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/11 10:46:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"
/**
 * bi directional bubble sort
 * it is a variation of bubble sort that's easier to understand and implement
 * 
 */

static void	forward_pass(int *arr, int start, int *end, int *swapped)
{
	int	i;

	*swapped = 0;
	i = start;
	while (i < *end)
	{
		if (arr[i] > arr[i + 1])
		{
			ft_swap(&arr[i], &arr[i + 1], sizeof(int));
			*swapped = 1;
		}
		i++;
	}
	if (!*swapped)
		return ;
	(*end)--;
}

static void	backward_pass(int *arr, int *start, int end, int *swapped)
{
	int	i;

	i = end;
	while (i > *start)
	{
		if (arr[i] < arr[i - 1])
		{
			ft_swap(&arr[i], &arr[i - 1], sizeof(int));
			*swapped = 1;
		}
		i--;
	}
	(*start)++;
}

void	cocktail_shaker_sort(int *arr, int size)
{
	int	start;
	int	swapped;
	int	end;

	if (!arr || size <= 1)
		return ;
	start = 0;
	end = size - 1;
	swapped = 1;
	while (swapped)
	{
		forward_pass(arr, start, &end, &swapped);
		if (!swapped)
			break ;
		backward_pass(arr, &start, end, &swapped);
	}
}

//int main(void)
//{
//    int arr[] = {32, 1, 12, 53, 41};
//    int size = sizeof(arr) / sizeof(arr[0]);
//    print_array(arr, size);
//    cocktail_shaker_sort(arr, size);
//    print_array(arr, size);
//}