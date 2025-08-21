/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:34:19 by dlesieur          #+#    #+#             */
/*   Updated: 2025/04/28 10:30:12 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdlib.h>

static int	*create_int_content(int value)
{
	int	*content;

	content = malloc(sizeof(int));
	if (!content)
		return (NULL);
	*content = value;
	return (content);
}

static t_list	*create_list_recursive(int *arr, int index, int n)
{
	t_list	*node;
	int		*content;

	if (index >= n)
		return (NULL);
	content = create_int_content(arr[index]);
	if (!content)
		return (NULL);
	node = create_node(content);
	if (!node)
	{
		free(content);
		return (NULL);
	}
	node->next = create_list_recursive(arr, index + 1, n);
	return (node);
}

t_list	*create_linked_list(int *arr, int n)
{
	if (n <= 0)
		return (NULL);
	return (create_list_recursive(arr, 0, n));
}
