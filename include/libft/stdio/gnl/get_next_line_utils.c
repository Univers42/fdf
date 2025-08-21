/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syzygy <syzygy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 00:41:06 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/19 17:51:14 by syzygy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Forward declaration for libft function */
size_t	ft_strlen(const char *s);

char	*ft_strjoin_gnl(char *s1, const char *s2)
{
	char		*new_str;
	char		*ptr;
	size_t		len2;
	size_t		len1;
	char		*orig_s1;

	if (s1)
		len1 = ft_strlen(s1);
	else
		len1 = 0;
	len2 = ft_strlen(s2);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	ptr = new_str;
	orig_s1 = s1;
	while (s1 && *s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	if (orig_s1)
		free(orig_s1);
	return (new_str);
}

t_fd_list	*ft_get_fd_node(t_fd_list **fd_list, size_t fd)
{
	t_fd_list	*current;
	t_fd_list	*new_node;

	current = *fd_list;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	new_node = malloc(sizeof(t_fd_list));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->memory = NULL;
	new_node->next = *fd_list;
	*fd_list = new_node;
	return (new_node);
}

void	ft_remove_fd_node(t_fd_list **fd_list, size_t fd)
{
	t_fd_list	*prev;
	t_fd_list	*current;

	prev = NULL;
	current = *fd_list;
	while (current)
	{
		if (current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else
				*fd_list = current->next;
			(free(current->memory), free(current));
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	free_all_gnl(void)
{
	t_fd_list	**fd_list_ptr;
	t_fd_list	*current;
	t_fd_list	*next;

	fd_list_ptr = get_gnl_fd_list();
	current = *fd_list_ptr;
	while (current)
	{
		next = current->next;
		free(current->memory);
		free(current);
		current = next;
	}
	*fd_list_ptr = NULL;
}
