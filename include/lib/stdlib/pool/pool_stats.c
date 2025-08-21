/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool_stats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:55:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:33:53 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pool.h"
#include <stdio.h>
#include "ft_stdio.h"

void	pool_stats(t_pool *pool)
{
	if (pool == NULL)
		return ;
	ft_printf("Pool Stats:\n");
	ft_printf("  Block size: %zu bytes\n", pool->block_size);
	ft_printf("  Total allocated: %zu\n", pool->total_allocated);
	ft_printf("  Total freed: %zu\n", pool->total_freed);
	ft_printf("  Active allocations: %zu\n",
		pool->total_allocated - pool->total_freed);
}
