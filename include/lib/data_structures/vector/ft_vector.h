/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:22:34 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/01 09:03:48 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include <stdlib.h>
# include <stdbool.h>

# define VECTOR_INITIAL_CAPACITY 4
# define VECTOR_GROWTH_FACTOR 2

typedef struct s_vector
{
	void	**data;
	size_t	size;
	size_t	capacity;
}			t_vector;

t_vector	*ft_vector_create(void);
void		ft_vector_destroy(t_vector *vector);
bool		ft_vector_add_back(t_vector *vector, void *element);
void		*ft_vector_pop_back(t_vector *vector);
void		*ft_vector_get(t_vector *vector, size_t index);
bool		ft_vector_set(t_vector *vector, size_t index, void *element);

// Utility functions
size_t		ft_vector_size(t_vector *vector);
size_t		ft_vector_capacity(t_vector *vector);
bool		ft_vector_is_empty(t_vector *vector);
void		ft_vector_clear(t_vector *vector);
bool		ft_vector_resize(t_vector *vector, size_t new_capacity);
bool		ft_vector_reserve(t_vector *vector, size_t capacity);

// Advanced functions
bool		ft_vector_insert(t_vector *vector, size_t index, void *element);
void		*ft_vector_remove(t_vector *vector, size_t index);
void		ft_vector_print_addresses(t_vector *vector);
int			ft_vector_binary_search(t_vector *vector, void *target,
				int (*cmp)(const void *, const void *));

#endif
