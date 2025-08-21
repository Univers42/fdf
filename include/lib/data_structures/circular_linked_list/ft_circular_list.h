/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_circular_list.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:20:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/15 17:34:48 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CIRCULAR_LIST_H
# define FT_CIRCULAR_LIST_H

# include <stdlib.h>
# include <stdbool.h>

typedef struct s_cl_node
{
	void				*data;
	struct s_cl_node	*next;
}						t_cl_node;

typedef struct s_circular_list
{
	t_cl_node	*last; //Points to last node (last->next is first)
	size_t		size;
}				t_circular_list;

// Core functions
t_circular_list	*ft_cl_create(void);
void			ft_cl_destroy(t_circular_list *list);
bool			ft_cl_push_front(t_circular_list *list, void *data);
bool			ft_cl_push_back(t_circular_list *list, void *data);
void			*ft_cl_pop_front(t_circular_list *list);
void			*ft_cl_pop_back(t_circular_list *list);

// Access functions
void			*ft_cl_front(t_circular_list *list);
void			*ft_cl_back(t_circular_list *list);
void			*ft_cl_get(t_circular_list *list, size_t index);
bool			ft_cl_set(t_circular_list *list, size_t index, void *data);

// Insertion and removal
bool			ft_cl_insert(t_circular_list *list, size_t index, void *data);
void			*ft_cl_remove(t_circular_list *list, size_t index);
bool			ft_cl_remove_data(t_circular_list *list, void *data);

// Utility functions
size_t			ft_cl_size(t_circular_list *list);
bool			ft_cl_is_empty(t_circular_list *list);
void			ft_cl_clear(t_circular_list *list);
void			ft_cl_rotate_forward(t_circular_list *list, size_t steps);
void			ft_cl_rotate_backward(t_circular_list *list, size_t steps);

// Search functions
int				ft_cl_find(t_circular_list *list, void *data);
bool			ft_cl_contains(t_circular_list *list, void *data);

// Advanced functions
void			ft_cl_print_addresses(t_circular_list *list);
void			ft_cl_print_n_times(t_circular_list *list, size_t n);

#endif
