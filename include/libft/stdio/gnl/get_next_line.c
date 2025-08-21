/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 00:41:34 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/20 18:18:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Forward declarations for libft functions */
void	*ft_memmove(void *dst, const void *src, size_t n);
size_t	ft_strclen(const char *s, int c);
char	*ft_strndup(const char *s, size_t n);

static char	*ft_store_chunks(int fd, char *memory)
{
	char		*buffer;
	t_ssize		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (ft_strclen(memory, '\n') == ft_strclen(memory, '\0'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			if (bytes_read == 0)
				return (memory);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		memory = ft_strjoin_gnl(memory, buffer);
		if (!memory)
			return (free(buffer), NULL);
	}
	return (free(buffer), memory);
}

static char	*ft_get_line(char *memory)
{
	char	*line;
	size_t	newline_idx;

	if (!memory || !*memory)
		return (NULL);
	newline_idx = ft_strclen(memory, '\n');
	line = malloc(newline_idx + 2);
	if (!line)
		return (NULL);
	ft_memmove(line, memory, newline_idx + 1);
	line[newline_idx + 1] = '\0';
	return (line);
}

static char	*ft_get_leftover(char *memory)
{
	char	*ptr;
	char	*leftover;

	ptr = memory;
	while (*ptr && *ptr != '\n')
		ptr++;
	if (!*ptr)
		return (free(memory), NULL);
	leftover = ft_strndup(ptr + 1, ft_strclen(ptr + 1, '\0'));
	return (free(memory), leftover);
}

t_fd_list	**get_gnl_fd_list(void)
{
	static t_fd_list	*fd_list = NULL;

	return (&fd_list);
}

char	*get_next_line(int fd)
{
	t_fd_list	**fd_list_ptr;
	t_fd_list	*fd_node;
	char		*line;

	fd_list_ptr = get_gnl_fd_list();
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	fd_node = ft_get_fd_node(fd_list_ptr, (size_t)fd);
	if (!fd_node)
		return (NULL);
	fd_node->memory = ft_store_chunks(fd, fd_node->memory);
	if (!fd_node->memory)
		return (ft_remove_fd_node(fd_list_ptr, (size_t)fd), NULL);
	line = ft_get_line(fd_node->memory);
	fd_node->memory = ft_get_leftover(fd_node->memory);
	if (!line)
		ft_remove_fd_node(fd_list_ptr, (size_t)fd);
	return (line);
}
