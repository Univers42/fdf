/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:01:04 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/29 20:00:31 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	arena_init(t_arena *arena)
{
	arena->blocks = NULL;
	arena->total_allocated = 0;
}

/**
 * @brief init an aux pointer to the data structure
 * init all the members and the allocate the size needed
 * @param arena pointer to structure
 * @param size size of the arena
 * @return void
 * @note This function is called an arena allocators. 
 * I tus useful for managing many short-lived allocations
 * we allocate as much as we want, and we liberate all in once when done,
 * using the same arena struct as "the manager" for all memory blocks.
 */
void	*arena_alloc(t_arena *arena, size_t size)
{
	t_arena_block	*block;

	if (size == 0)
		return (NULL);
	block = malloc(sizeof(t_arena_block) + size);
	if (!block)
		return (NULL);
	block->next = arena->blocks;
	block->size = size;
	arena->blocks = block;
	arena->total_allocated += size;
	return (block->data);
}

/**
 * @brief arena destroy is a function that enable to destroy from the
 * mem block
 * @param arena pointer to struct of arena
 * the memory is liberated from the block of allocated memory.
 */
void	arena_destroy(t_arena *arena)
{
	t_arena_block	*block;
	t_arena_block	*next;

	block = arena->blocks;
	while (block)
	{
		next = block->next;
		arena->total_allocated -= block->size;
		free(block);
		block = next;
	}
	arena->blocks = NULL;
}
