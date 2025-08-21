/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:59:17 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/08 12:36:53 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdarg.h>
#include <stdlib.h>
#include "../memory/ft_memory.h"

// Helper function to compute the total length of all strings
static size_t	ft_strnjoin_total_length(const char *first, va_list args)
{
	size_t			total_length;
	const char		*str;

	total_length = 0;
	str = first;
	while (str)
	{
		total_length += ft_strlen(str);
		str = va_arg(args, const char *);
	}
	return (total_length);
}

// Helper function to copy all strings into the result buffer
static void	ft_strnjoin_copy(char *result, const char *first, va_list args)
{
	const char	*str;
	char		*ptr;
	size_t		len;

	str = first;
	ptr = result;
	while (str)
	{
		len = ft_strlen(str);
		ft_memcpy(ptr, str, len);
		ptr += len;
		str = va_arg(args, const char *);
	}
	*ptr = '\0';
}

/**
 * Concatenate multiple strings into a single string.
 * The first argument is the first string, followed by a variable number of
 * additional strings. The last string must be NULL to indicate the end.
 * 
 * @param first The first string to concatenate.
 * @return A newly allocated string containing all concatenated strings,
 *         or NULL if memory allocation fails.
 */
char	*ft_strnjoin(const char *first, ...)
{
	char		*result;
	va_list		args;
	size_t		total_length;

	total_length = 0;
	if (!first)
		return (NULL);
	va_start(args, first);
	total_length = ft_strnjoin_total_length(first, args);
	va_end(args);
	result = (char *)malloc(total_length + 1);
	if (!result)
		return (NULL);
	va_start(args, first);
	ft_strnjoin_copy(result, first, args);
	va_end(args);
	return (result);
}
