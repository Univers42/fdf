/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doubly_list.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:15:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:48:08 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DOUBLY_LIST_H
# define FT_DOUBLY_LIST_H

# include <stdlib.h>
# include <stdbool.h>

typedef struct s_dll_node
{
	void				*data;
	struct s_dll_node	*next;
	struct s_dll_node	*prev;
}						t_dll_node;

typedef struct s_doubly_list
{
	t_dll_node	*head;
	t_dll_node	*tail;
	size_t		size;
}				t_doubly_list;

// Core functions
t_doubly_list	*ft_dll_create(void);
void			ft_dll_destroy(t_doubly_list *list);
bool			ft_dll_push_front(t_doubly_list *list, void *data);
bool			ft_dll_push_back(t_doubly_list *list, void *data);
void			*ft_dll_pop_front(t_doubly_list *list);
void			*ft_dll_pop_back(t_doubly_list *list);

// Access functions
void			*ft_dll_front(t_doubly_list *list);
void			*ft_dll_back(t_doubly_list *list);
void			*ft_dll_get(t_doubly_list *list, size_t index);
bool			ft_dll_set(t_doubly_list *list, size_t index, void *data);

// Insertion and removal
bool			ft_dll_insert(t_doubly_list *list, size_t index, void *data);
void			*ft_dll_remove(t_doubly_list *list, size_t index);
bool			ft_dll_remove_data(t_doubly_list *list, void *data);

// Utility functions
size_t			ft_dll_size(t_doubly_list *list);
bool			ft_dll_is_empty(t_doubly_list *list);
void			ft_dll_clear(t_doubly_list *list);
void			ft_dll_reverse(t_doubly_list *list);

// Search functions
int				ft_dll_find(t_doubly_list *list, void *data);
bool			ft_dll_contains(t_doubly_list *list, void *data);

// Advanced functions
void			ft_dll_print_addresses(t_doubly_list *list);
void			ft_dll_print_reverse(t_doubly_list *list);

#endif
