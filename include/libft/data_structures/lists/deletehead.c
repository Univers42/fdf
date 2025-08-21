/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletehead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:40:53 by dlesieur          #+#    #+#             */
/*   Updated: 2025/04/27 17:42:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdlib.h>

t_list	*delete_head(t_list *head)
{
	t_list	*new_head;

	if (!head)
		return (NULL);
	new_head = head->next;
	return (free(head), new_head);
}
