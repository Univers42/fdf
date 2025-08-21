/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slab.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:40:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 02:19:29 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slab.h"
#include <string.h>

void	slab_init(t_slab_allocator *slab)
{
	if (slab == NULL)
		return ;
	slab->cache_count = 0;
	memset(slab->caches, 0, sizeof(slab->caches));
}

void	slab_add_cache(t_slab_allocator *slab,
				size_t block_size, size_t blocks_per_chunk)
{
	t_slab_cache	*cache;

	if (slab == NULL)
		return ;
	if (slab->cache_count >= MAX_SLAB_SIZES)
		return ;
	cache = &slab->caches[slab->cache_count];
	cache->block_size = block_size;
	cache->blocks_per_chunk = blocks_per_chunk;
	cache->total_allocated = 0;
	cache->total_freed = 0;
	cache->chunks = NULL;
	slab->cache_count += 1;
}

t_slab_cache	*find_best_cache(t_slab_allocator *slab, size_t size)
{
	size_t			i;
	t_slab_cache	*best;

	best = NULL;
	i = -1;
	while (++i < slab->cache_count)
	{
		if (slab->caches[i].block_size >= size)
			if (!best || slab->caches[i].block_size < best->block_size)
				best = &slab->caches[i];
	}
	return (best);
}
