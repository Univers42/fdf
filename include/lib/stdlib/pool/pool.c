/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:55:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 01:57:55 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pool.h"
#include "pool_internal.h"

/* init */
void	pool_init(t_pool *pool, size_t block_size, size_t blocks_per_chunk)
{
	if (pool == NULL)
		return ;
	pool->block_size = block_size;
	pool->blocks_per_chunk = blocks_per_chunk;
	pool->total_allocated = 0;
	pool->total_freed = 0;
	pool->chunks = NULL;
}

/* alloc */
void	*pool_alloc(t_pool *pool)
{
	t_pool_chunk	*chunk;
	t_pool_block	*block;

	if (pool == NULL)
		return (NULL);
	chunk = pool->chunks;
	while (chunk != NULL && chunk->free_list == NULL)
		chunk = chunk->next;
	if (chunk == NULL)
	{
		chunk = create_chunk(pool);
		if (chunk == NULL)
			return (NULL);
		pool->chunks = chunk;
	}
	block = chunk->free_list;
	chunk->free_list = block->next;
	block->is_free = false;
	chunk->used_blocks += 1;
	pool->total_allocated += 1;
	return (block->data);
}

static int	pool_free_in_chunk(t_pool *pool, t_pool_chunk *chunk, void *ptr)
{
	char			*start;
	char			*end;
	size_t			bsz;
	t_pool_block	*block;

	bsz = sizeof(t_pool_block) + pool->block_size;
	start = chunk->memory;
	end = start + pool->blocks_per_chunk * bsz;
	if ((char *)ptr >= start && (char *)ptr < end)
	{
		block = (t_pool_block *)((char *)ptr - sizeof(t_pool_block));
		if (block->is_free == false)
		{
			block->is_free = true;
			block->next = chunk->free_list;
			chunk->free_list = block;
			chunk->used_blocks -= 1;
			pool->total_freed += 1;
		}
		return (1);
	}
	return (0);
}

void	pool_free(t_pool *pool, void *ptr)
{
	t_pool_chunk	*chunk;

	if (pool == NULL || ptr == NULL)
		return ;
	chunk = pool->chunks;
	while (chunk != NULL)
	{
		if (pool_free_in_chunk(pool, chunk, ptr))
			return ;
		chunk = chunk->next;
	}
}

/* destroy */
void	pool_destroy(t_pool *pool)
{
	t_pool_chunk	*chunk;
	t_pool_chunk	*next;

	if (pool == NULL)
		return ;
	chunk = pool->chunks;
	while (chunk != NULL)
	{
		next = chunk->next;
		free(chunk->memory);
		free(chunk);
		chunk = next;
	}
	pool->chunks = NULL;
}
