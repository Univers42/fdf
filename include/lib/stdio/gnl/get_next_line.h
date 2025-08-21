/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 00:41:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/20 18:18:39 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef unsigned long int	t_size;
typedef long				t_ssize;

typedef struct s_fd_list
{
	t_size				fd;
	char				*memory;
	struct s_fd_list	*next;
}	t_fd_list;

char		*get_next_line(int fd);
char		*ft_strjoin_gnl(char *s1, const char *s2);
t_fd_list	*ft_get_fd_node(t_fd_list **fd_list, t_size fd);
void		ft_remove_fd_node(t_fd_list **fd_list, t_size fd);
void		free_all_gnl(void);

/* Forward declarations for libft functions used in GNL */
t_size		ft_strlen(const char *s);
t_size		ft_strclen(const char *s, int c);
char		*ft_strndup(const char *s, t_size n);
t_fd_list	**get_gnl_fd_list(void);
#endif
