/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:58:35 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 01:58:48 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include <stddef.h>
# include <stdlib.h>

typedef struct s_arena_block
{
	struct s_arena_block	*next;
	size_t					size;
	char					data[];
}							t_arena_block;

typedef struct s_arena
{
	t_arena_block	*blocks;
	size_t			total_allocated;
}					t_arena;

void	arena_init(t_arena *arena);
void	*arena_alloc(t_arena *arena, size_t size);
void	arena_destroy(t_arena *arena);

#endif