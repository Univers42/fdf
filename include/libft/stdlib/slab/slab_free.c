/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slab_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:40:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 01:45:02 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slab.h"
#include <stdlib.h>
#include <stdbool.h>

static t_slab_block	*slab_get_block_at_ptr(t_slab_chunk *chunk,
						t_slab_cache *cache, void *ptr)
{
	char			*start;
	size_t			bsz;
	size_t			offset;
	t_slab_block	*blk;

	start = chunk->memory;
	bsz = sizeof(t_slab_block) + cache->block_size;
	if ((char *)ptr < start
		|| (char *)ptr >= start + chunk->total_blocks * bsz)
		return (NULL);
	offset = (size_t)((char *)ptr - start) / bsz;
	blk = (t_slab_block *)(start + offset * bsz);
	if (blk->data != ptr)
		return (NULL);
	return (blk);
}

static int	slab_free_in_cache(t_slab_cache *cache, void *ptr)
{
	t_slab_chunk	*chunk;
	t_slab_block	*blk;

	chunk = cache->chunks;
	while (chunk != NULL)
	{
		blk = slab_get_block_at_ptr(chunk, cache, ptr);
		if (blk != NULL && blk->is_free == false)
		{
			blk->is_free = true;
			blk->next = chunk->free_list;
			chunk->free_list = blk;
			chunk->used_blocks -= 1;
			cache->total_freed += 1;
			return (1);
		}
		if (blk != NULL)
			return (0);
		chunk = chunk->next;
	}
	return (0);
}

void	slab_free(t_slab_allocator *slab, void *ptr)
{
	size_t	i;

	if (slab == NULL || ptr == NULL)
		return ;
	i = 0;
	while (i < slab->cache_count)
	{
		if (slab_free_in_cache(&slab->caches[i], ptr))
			return ;
		i += 1;
	}
	if (ptr > (void *)0x1000)
		free(ptr);
}
