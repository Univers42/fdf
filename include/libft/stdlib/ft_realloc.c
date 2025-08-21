/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:06:58 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 14:08:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_memory.h"
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>

static bool	mul_overflow_size_t(size_t a, size_t b, size_t *out)
{
	if (a == 0 || b == 0)
	{
		*out = 0;
		return (false);
	}
	if (a > SIZE_MAX / b)
		return (true);
	*out = a * b;
	return (false);
}

static bool	ft_realloc_bytes(void **ptr,
								size_t old_bytes, size_t new_bytes)
{
	void	*newp;

	if (new_bytes == 0)
	{
		if (*ptr != NULL)
			free(*ptr);
		*ptr = NULL;
		return (true);
	}
	newp = malloc(new_bytes);
	if (newp == NULL)
		return (false);
	if (*ptr != NULL && old_bytes != 0)
	{
		if (old_bytes < new_bytes)
			ft_memcpy(newp, *ptr, old_bytes);
		else
			ft_memcpy(newp, *ptr, new_bytes);
		free(*ptr);
	}
	*ptr = newp;
	return (true);
}

bool	ft_realloc(void **ptr, size_t elem_size,
					size_t old_count, size_t new_count)
{
	size_t	old_bytes;
	size_t	new_bytes;

	if (ptr == NULL || elem_size == 0)
		return (false);
	if (mul_overflow_size_t(old_count, elem_size, &old_bytes))
		return (false);
	if (mul_overflow_size_t(new_count, elem_size, &new_bytes))
		return (false);
	return (ft_realloc_bytes(ptr, old_bytes, new_bytes));
}

bool	ft_realloc_grow(void **ptr, size_t elem_size,
						size_t *cap, size_t min_needed)
{
	size_t	new_cap;

	if (ptr == NULL || cap == NULL)
		return (false);
	if (*cap >= min_needed)
		return (true);
	new_cap = *cap;
	if (new_cap == 0)
		new_cap = 1;
	while (new_cap < min_needed)
	{
		if (new_cap > SIZE_MAX / 2)
		{
			new_cap = min_needed;
			break ;
		}
		new_cap *= 2;
	}
	if (!ft_realloc(ptr, elem_size, *cap, new_cap))
		return (false);
	*cap = new_cap;
	return (true);
}

bool	ft_realloc_shrink_to(void **ptr, size_t elem_size,
								size_t *cap, size_t new_cap)
{
	if (ptr == NULL || cap == NULL)
		return (false);
	if (new_cap == *cap)
		return (true);
	if (!ft_realloc(ptr, elem_size, *cap, new_cap))
		return (false);
	*cap = new_cap;
	return (true);
}
