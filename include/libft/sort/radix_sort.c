/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:58:04 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

int	get_max_bits(int max_num)
{
	int	bits;

	bits = 0;
	while (max_num > 0)
	{
		bits++;
		max_num >>= 1;
	}
	return (bits);
}

static void	collect_zeros(int *arr, int *output, int size, int bit)
{
	int	i;
	int	idx;

	i = 0;
	idx = 0;
	while (i < size)
	{
		if (((arr[i] >> bit) & 1) == 0)
			output[idx++] = arr[i];
		i++;
	}
}

static void	collect_ones(int *arr, int *output, int size, int bit)
{
	int	i;
	int	idx;

	i = 0;
	idx = 0;
	while (i < size)
	{
		if (((arr[i] >> bit) & 1) == 0)
			idx++;
		i++;
	}
	i = 0;
	while (i < size)
	{
		if (((arr[i] >> bit) & 1) == 1)
			output[idx++] = arr[i];
		i++;
	}
}

static void	copy_back(int *arr, int *output, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		arr[i] = output[i];
		i++;
	}
}

void	radix_sort(int *arr, int size, int max_bits)
{
	int	*output;
	int	bit;

	output = malloc(size * sizeof(int));
	if (!output)
		return ;
	bit = 0;
	while (bit < max_bits)
	{
		collect_zeros(arr, output, size, bit);
		collect_ones(arr, output, size, bit);
		copy_back(arr, output, size);
		bit++;
	}
	free(output);
}

//void	print_array(int *arr, int size)
//{
//	int	i;
//
//	i = -1;
//	while (++i < size)
//		ft_printf("[%d] ==> %d\n", i, arr[i]);
//}
//int	main(void)
//{
//	int	arr[7];
//	int	size;
//	int	max_value;
//	int	max_bits;
//
//	arr[0] = 3;
//	arr[1] = 1;
//	arr[2] = 4;
//	arr[3] = 15500;
//	arr[4] = 5;
//	arr[5] = 9;
//	arr[6] = 2;
//	size = sizeof(arr) / sizeof(int);
//	print_array(arr, size);
//	max_value = max(arr, size);
//	max_bits = get_max_bits(max_value);
//	radix_sort(arr, size, max_bits);
//	print_array(arr, size);
//	ft_printf("Max value: %d\n", max_value);
//	ft_printf("Maximum of bits: %d\n", max_bits);
//	return (0);
//}
