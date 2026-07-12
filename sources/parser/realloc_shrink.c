/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_shrink.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

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

static bool	realloc_bytes(void **ptr, size_t old_bytes, size_t new_bytes)
{
	void	*newp;

	if (new_bytes == 0)
	{
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
	}
	free(*ptr);
	*ptr = newp;
	return (true);
}

bool	ft_realloc_shrink_to(void **ptr, size_t elem_size,
				size_t *cap, size_t new_cap)
{
	size_t	old_bytes;
	size_t	new_bytes;

	if (ptr == NULL || cap == NULL || elem_size == 0)
		return (false);
	if (new_cap == *cap)
		return (true);
	if (mul_overflow_size_t(*cap, elem_size, &old_bytes))
		return (false);
	if (mul_overflow_size_t(new_cap, elem_size, &new_bytes))
		return (false);
	if (!realloc_bytes(ptr, old_bytes, new_bytes))
		return (false);
	*cap = new_cap;
	return (true);
}
