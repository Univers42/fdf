/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:38:07 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/04 18:14:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../render/ft_stddef.h"
#include <stdlib.h>
#include "ft_string.h"

char	*ft_strndup(const char *s1, t_size n)
{
	char	*dup;
	t_size	len;
	t_size	i;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	if (n < len)
		len = n;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}
