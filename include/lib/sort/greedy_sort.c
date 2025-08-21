/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:26:11 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

static void	greedy_sort_algorithm(t_stck *a, t_stck *b);

void	greed_sort(int *arr, int size)
{
	t_stck	a;
	t_stck	b;

	if (size <= 1)
		return ;
	initialize_stacks(&a, &b, arr, size);
	greedy_sort_algorithm(&a, &b);
	copy_result_back(arr, &a, size);
	free(a.data);
	free(b.data);
}

static void	greedy_sort_algorithm(t_stck *a, t_stck *b)
{
	(void)a;
	(void)b;
}

// Test
//int main(void) {
//    int arr[] = {5, 2, 4, 3, 1};
//    int size = sizeof(arr) / sizeof(arr[0]);
//    greedy_sort(arr, size);
//    for (int i = 0; i < size; i++)
//       	ft_printf("%d ", arr[i]);
//   	ft_printf("\n");
//    return 0;
//}