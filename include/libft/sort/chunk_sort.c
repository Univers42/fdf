/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:18:46 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

int	normalized_value(int val, int min, int max, char *stat)
{
	if (strcmp(stat, "denormalize") == 0)
		return (val * (max - min) / 100 + min);
	else if (strcmp(stat, "normalize") == 0)
		return ((val - min) * 100 / (max - min));
	return (val);
}

static void	normalize_array(int *arr, int *normalized_arr, int size,
				t_norm_params *params)
{
	int	i;

	i = 0;
	while (i < size)
	{
		normalized_arr[i] = normalized_value(arr[i], params->min,
				params->max, "normalize");
		i++;
	}
}

static void	denormalize_array(int *arr, int *normalized_arr, int size,
	t_norm_params *params)
{
	int	i;

	i = 0;
	while (i < size)
	{
		arr[i] = normalized_value(normalized_arr[i], params->min,
				params->max, "denormalize");
		i++;
	}
}

void	ft_chunk_sort(int *arr, int size)
{
	int				*normalized_arr;
	t_norm_params	params;

	if (!arr || size <= 1)
		return ;
	normalized_arr = malloc(size * sizeof(int));
	if (!normalized_arr)
		return ;
	params.min = get_min(arr, size);
	params.max = get_max(arr, size);
	normalize_array(arr, normalized_arr, size, &params);
	choose_chunk_size_and_process(normalized_arr, size);
	denormalize_array(arr, normalized_arr, size, &params);
	free(normalized_arr);
}

// int main(void)
// {
//     int arr[] = {2, 802, 24, 45, 66, 170, 75, 90};
//     int size = 8;
//
//    	ft_printf("Original array: ");
//     print_array(arr, size);
//
//     ft_chunk_sort(arr, size);
//
//    	ft_printf("Sorted array: ");
//     print_array(arr, size);
//
//     return (0);
// }