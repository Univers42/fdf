/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grow_buf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:54:08 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/29 22:54:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

/**
specific helpers for this project, not truly reusable, it copies `*cap`
but `*cap` is used as a `caapcity` (number of elements) elsewhere in our
project, not as byte count. a general purpose `realloc` would need to know the
size of each element. it only grows the buffer, doesn't shrink
This function is not safe or flex enough. 
let's suppose we have an array of float with *cap = 100 meaning 100 floats
*/
bool	grow_buf(void **ptr, size_t *cap, size_t start)
{
	size_t	new_cap;
	void	*temp;

	if (*cap == 0)
		new_cap = start;
	else
		new_cap = *cap * 2;
	temp = malloc(new_cap);
	if (temp == NULL)
		return (false);
	ft_memcpy(temp, *ptr, *cap);
	free(*ptr);
	*ptr = temp;
	*cap = new_cap;
	return (true);
}
