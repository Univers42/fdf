/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slab_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:40:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 01:41:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slab.h"
#include <stdlib.h>

void	slab_destroy(t_slab_allocator *slab)
{
	size_t			i;
	t_slab_cache	*cache;
	t_slab_chunk	*chunk;
	t_slab_chunk	*next;

	if (slab == NULL)
		return ;
	i = 0;
	while (i < slab->cache_count)
	{
		cache = &slab->caches[i];
		chunk = cache->chunks;
		while (chunk != NULL)
		{
			next = chunk->next;
			free(chunk->memory);
			free(chunk);
			chunk = next;
		}
		cache->chunks = NULL;
		i += 1;
	}
}
