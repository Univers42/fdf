/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slab_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:40:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 01:41:03 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLAB_INTERNAL_H
# define SLAB_INTERNAL_H

# include "slab.h"
# include <stddef.h>

t_slab_chunk	*create_slab_chunk(t_slab_cache *cache);
t_slab_cache	*find_best_cache(t_slab_allocator *slab, size_t size);

#endif
