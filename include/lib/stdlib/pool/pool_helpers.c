/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:55:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 01:55:44 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pool_internal.h"
#include <stdlib.h>

static void	build_free_list(t_pool_chunk *chunk, t_pool *pool)
{
	char			*ptr;
	size_t			i;
	t_pool_block	*blk;

	ptr = chunk->memory;
	i = 0;
	while (i < pool->blocks_per_chunk)
	{
		blk = (t_pool_block *)ptr;
		blk->is_free = true;
		blk->next = chunk->free_list;
		chunk->free_list = blk;
		ptr += sizeof(t_pool_block) + pool->block_size;
		i += 1;
	}
}

t_pool_chunk	*create_chunk(t_pool *pool)
{
	size_t			mem_size;
	t_pool_chunk	*chunk;
	char			*ptr;
	size_t			i;

	mem_size = pool->blocks_per_chunk;
	mem_size *= sizeof(t_pool_block) + pool->block_size;
	chunk = (t_pool_chunk *)malloc(sizeof(t_pool_chunk));
	if (chunk == NULL)
		return (NULL);
	chunk->memory = (char *)malloc(mem_size);
	if (chunk->memory == NULL)
	{
		free(chunk);
		return (NULL);
	}
	chunk->used_blocks = 0;
	chunk->free_list = NULL;
	chunk->next = pool->chunks;
	build_free_list(chunk, pool);
	(void)ptr;
	(void)i;
	return (chunk);
}
