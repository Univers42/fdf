/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 18:24:07 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

void	process_chunks(int *normalized_arr, int size, int num_chunks)
{
	int	**chunks;
	int	*chunk_counts;
	int	i;

	chunks = malloc(num_chunks * sizeof(int *));
	chunk_counts = calloc(num_chunks, sizeof(int));
	i = 0;
	while (i < num_chunks)
	{
		chunks[i] = malloc(size * sizeof(int));
		i++;
	}
	distribute_elements(normalized_arr, size, chunks, chunk_counts);
	sort_and_merge_chunks(normalized_arr, chunks, chunk_counts, num_chunks);
	cleanup_chunks(chunks, chunk_counts, num_chunks);
}
