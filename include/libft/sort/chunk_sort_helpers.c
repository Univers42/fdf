/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 18:27:22 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

void	distribute_elements(int *normalized_arr, int size, int **chunks,
	int *chunk_counts)
{
	int	i;
	int	j;
	int	chunk_size;
	int	num_chunks;

	num_chunks = 10;
	chunk_size = 100 / num_chunks + 1;
	i = 0;
	while (i < size)
	{
		j = normalized_arr[i] / chunk_size;
		if (j >= num_chunks)
			j = num_chunks - 1;
		chunks[j][chunk_counts[j]++] = normalized_arr[i];
		i++;
	}
}

void	sort_and_merge_chunks(int *normalized_arr, int **chunks,
	int *chunk_counts, int num_chunks)
{
	int	i;
	int	k;
	int	output_idx;

	output_idx = 0;
	i = 0;
	while (i < num_chunks)
	{
		if (chunk_counts[i] > 1)
			qsort(chunks[i], chunk_counts[i], sizeof(int), cmp_int);
		k = 0;
		while (k < chunk_counts[i])
		{
			normalized_arr[output_idx++] = chunks[i][k];
			k++;
		}
		free(chunks[i]);
		i++;
	}
}

void	cleanup_chunks(int **chunks, int *chunk_counts, int num_chunks)
{
	int	i;

	i = 0;
	while (i < num_chunks)
	{
		free(chunks[i]);
		i++;
	}
	free(chunks);
	free(chunk_counts);
}

void	choose_chunk_size_and_process(int *normalized_arr, int size)
{
	if (size <= 10)
		process_chunks(normalized_arr, size, 2);
	else if (size <= 50)
		process_chunks(normalized_arr, size, 5);
	else
		process_chunks(normalized_arr, size, 10);
}
