/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slab_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:40:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 01:41:04 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slab_internal.h"
#include <stdlib.h>
#include <stdbool.h>

static void	slab_build_free_list(t_slab_chunk *chunk, t_slab_cache *cache)
{
	char			*ptr;
	size_t			i;
	t_slab_block	*block;

	ptr = chunk->memory;
	i = 0;
	while (i < cache->blocks_per_chunk)
	{
		block = (t_slab_block *)ptr;
		block->is_free = true;
		block->next = chunk->free_list;
		chunk->free_list = block;
		ptr += sizeof(t_slab_block) + cache->block_size;
		i += 1;
	}
}

t_slab_chunk	*create_slab_chunk(t_slab_cache *cache)
{
	size_t			chunk_size;
	size_t			mem_size;
	t_slab_chunk	*chunk;

	chunk_size = sizeof(t_slab_chunk);
	mem_size = cache->blocks_per_chunk;
	mem_size *= sizeof(t_slab_block) + cache->block_size;
	chunk = (t_slab_chunk *)malloc(chunk_size);
	if (chunk == NULL)
		return (NULL);
	chunk->memory = (char *)malloc(mem_size);
	if (chunk->memory == NULL)
	{
		free(chunk);
		return (NULL);
	}
	chunk->block_size = cache->block_size;
	chunk->used_blocks = 0;
	chunk->total_blocks = cache->blocks_per_chunk;
	chunk->free_list = NULL;
	chunk->next = cache->chunks;
	slab_build_free_list(chunk, cache);
	return (chunk);
}

t_slab_cache	*find_best_cache(t_slab_allocator *slab, size_t size)
{
	size_t			i;
	t_slab_cache	*best;

	best = NULL;
	i = 0;
	while (i < slab->cache_count)
	{
		if (slab->caches[i].block_size >= size)
		{
			if (best == NULL
				|| slab->caches[i].block_size < best->block_size)
				best = &slab->caches[i];
		}
		i += 1;
	}
	return (best);
}
