/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:06:42 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/03 00:55:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slab.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 1024

typedef struct s_fd_list
{
    int fd;
    char *memory;
    struct s_fd_list *next;
} t_fd_list;

static t_slab_allocator slab;

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dst;
	s = src;
	if (d == s || n == 0)
		return (dst);
	if (d < s)
		while (n--)
			*d++ = *s++;
	else
	{
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
	}
	return (dst);
}

size_t	ft_strclen(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s && s[i] && s[i] != (char)c)
		i++;
	return (i);
}

char *ft_strndup_slab(const char *s, size_t n)
{
    char *dup = slab_alloc(&slab, n + 1);
    if (!dup)
        return NULL;
    
    memmove(dup, s, n);
    dup[n] = '\0';
    return dup;
}

char *ft_strjoin_slab(char *s1, const char *s2)
{
    size_t len1 = s1 ? strlen(s1) : 0;
    size_t len2 = s2 ? strlen(s2) : 0;
    char *new_str = slab_alloc(&slab, len1 + len2 + 1);
    
    if (!new_str)
        return NULL;
    
    char *ptr = new_str;
    if (s1)
        while (*s1)
            *ptr++ = *s1++;
    if (s2)
        while (*s2)
            *ptr++ = *s2++;
    *ptr = '\0';
    return new_str;
}

t_fd_list *ft_get_fd_node_slab(t_fd_list **fd_list, int fd)
{
    t_fd_list *current = *fd_list;
    
    while (current)
    {
        if (current->fd == fd)
            return current;
        current = current->next;
    }
    
    t_fd_list *new_node = slab_alloc(&slab, sizeof(t_fd_list));
    if (!new_node)
        return NULL;
    
    new_node->fd = fd;
    new_node->memory = NULL;
    new_node->next = *fd_list;
    *fd_list = new_node;
    return new_node;
}

static char	*ft_store_chunks(int fd, char *memory)
{
    char		*buffer;
	ssize_t		bytes_read;

	buffer = slab_alloc(&slab, BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    while (ft_strclen(memory, '\n') == ft_strclen(memory, '\0'))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
        {
            if (bytes_read == 0)
                return (memory);
            return (NULL);
        }
        buffer[bytes_read] = '\0';
        memory = ft_strjoin_slab(memory, buffer); // Use slab version
        if (!memory)
            return (NULL);
    }
    return (memory);
}

static char	*ft_get_line(char *memory)
{
	size_t	newline_idx;
	char	*line;

    if (!memory || !*memory)
        return (NULL);
    newline_idx = ft_strclen(memory, '\n');
    line = slab_alloc(&slab, newline_idx + 2);
    if (!line)
        return (NULL);
    ft_memmove(line, memory, newline_idx + 1);
    line[newline_idx + 1] = '\0';
    return (line);
}

static char	*ft_get_leftover(char *memory)
{
    char	*ptr;

	ptr	= memory;
    while (*ptr && *ptr != '\n')
        ptr++;
    if (!*ptr)
        return (NULL);
    return (ft_strndup_slab(ptr + 1, ft_strclen(ptr + 1, '\0'))); // Use slab version
}

char *get_next_line_slab(int fd)
{
    static t_fd_list *fd_list = NULL;
    t_fd_list *fd_node;
    char *line;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    
    fd_node = ft_get_fd_node_slab(&fd_list, fd);
    if (!fd_node)
        return NULL;
    
    fd_node->memory = ft_store_chunks(fd, fd_node->memory);
    if (!fd_node->memory)
        return NULL;
    
    line = ft_get_line(fd_node->memory);
    fd_node->memory = ft_get_leftover(fd_node->memory);
    
    return line;
}

int main(int argc, char **argv)
{
    clock_t start, end;
    double cpu_time_used;
    char *line;
    int fd, i = 0;
    
    if (argc < 2)
        return (fprintf(stderr, "Usage: %s <filename>\n", argv[0]), 1);
    
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (perror("open"), 1);
    
    // Initialize slab allocator with different cache sizes
    printf("=== Slab Allocator Test ===\n");
    slab_init(&slab);
    slab_add_cache(&slab, 64, 200);    // Small strings
    slab_add_cache(&slab, 128, 100);   // Medium strings
    slab_add_cache(&slab, 256, 50);    // Large strings
    slab_add_cache(&slab, 512, 25);    // Very large strings
    slab_add_cache(&slab, 1024, 10);   // Huge strings
    slab_add_cache(&slab, 2048, 5);    // Buffer size
    slab_add_cache(&slab, 4096, 3);    // Extra large
    
    start = clock();
    
    while ((line = get_next_line_slab(fd)) && i < 1000) // Add safety limit
    {
        printf("Line %d: %s", ++i, line);
        // In slab allocator, we can free individual allocations
        // But be careful - don't free the same pointer twice
        if (line)
        {
            slab_free(&slab, line);
            line = NULL; // Prevent double free
        }
    }
    
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("\n=== Slab Performance Results ===\n");
    printf("Lines processed: %d\n", i);
    printf("Time taken: %f seconds\n", cpu_time_used);
    
    slab_stats(&slab);
    slab_destroy(&slab);
    
    close(fd);
    return 0;
}