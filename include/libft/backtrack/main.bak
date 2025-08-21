/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:57:27 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/29 18:05:50 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backtrack.h"

void	print_array(int **arr, int size, int returnSize)
{
	int	**row;
	int	*elem;
	int	*end_elem;
	int	**end_row;

	row = arr;
	end_row = arr + size;
	while (row < end_row)
	{
		elem = *row;
		end_elem = elem + returnSize;
		printf("[");
		while (elem < end_elem)
		{
			printf("%d", *elem);
			if (elem + 1 < end_elem)
				printf(", ");
			elem++;
		}
		printf("]");
		row++;
	}
}

static int	p(int n, int r)
{
	int	result;
	int	*pn;
	int	i;

	result = 1;
	pn = &n;
	i = -1;
	while (++i < r)
	{
		result *= *pn;
		(*pn)--;
	}
	return (result);
}

static int	**all_perm(int **arr, int size, int *returnSize)
{
	int	**perm_arr;
	int	size;

	perm_arr = (malloc(sizeof(int *) * p(size, size)));
	if (!perm_arr)
		return (NULL);
	return (arr);
}

int	main(int argc, char **argv)
{
	int	*arr;
	int	*ptr;
	int	*end;
	int	size;
	int *returnSize;

	if (argc == 1)
		return (1);
	size = argc - 1;
	arr = calloc(size, sizeof(char));
	if (!arr)
		return (NULL);
	ptr = arr;
	end = ptr + size - 1;
	++argv;
	while (ptr < end)
		*ptr++ = atoi(*argv++);
	all_perm(arr, size, returnSize);
	print_array(arr, size, returnSize);
	free(ptr);
	return (0);
}