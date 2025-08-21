/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slab_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:40:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 01:41:27 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slab_internal.h"
#include <stdlib.h>
#include <stdbool.h>

void	*slab_alloc(t_slab_allocator *slab, size_t size)
{
	t_slab_cache	*cache;
	t_slab_chunk	*chunk;
	t_slab_block	*block;

	if (slab == NULL)
		return (NULL);
	cache = find_best_cache(slab, size);
	if (cache == NULL)
		return (malloc(size));
	chunk = cache->chunks;
	while (chunk != NULL && chunk->free_list == NULL)
		chunk = chunk->next;
	if (chunk == NULL)
	{
		chunk = create_slab_chunk(cache);
		if (chunk == NULL)
			return (NULL);
		cache->chunks = chunk;
	}
	block = chunk->free_list;
	chunk->free_list = block->next;
	block->is_free = false;
	chunk->used_blocks += 1;
	cache->total_allocated += 1;
	return (block->data);
}
