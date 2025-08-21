/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:18:06 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:36:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SORT_H
# define FT_SORT_H

# include "ft_memory.h"
# include "ft_debug.h"
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include "ft_stdio.h"

# define RUN 32

typedef struct s_stck
{
	int	*data;
	int	size;
}		t_stck;

typedef struct s_tagged_element
{
	int	value;
	int	tag;
}		t_tagged_element;

typedef struct s_thread_data
{
	int				value;
	int				*result_array;
	int				*index;
	pthread_mutex_t	*mutex;
}					t_thread_data;

typedef struct s_tree_node
{
	int					data;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}						t_tree_node;

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct s_norm_params
{
	int	min;
	int	max;
}		t_norm_params;

void	ft_chunk_sort(int *arr, int size);
void	ft_merge_sort(int *arr, int l, int r);
void	merge(int *arr, int l, int m, int r);
void	cocktail_shaker_sort(int *arr, int size);
void	comb_sort(int *arr, int size);
void	counting_sort(int *arr, int size);
void	greed_sort(int *arr, int size);
void	ft_gnome_sort(int *arr, int size);
void	hybrid_sort(int *arr, int size);
void	hybrid2_sort(int *arr, int size, int *tag_to_value);
void	insertion_sort(int arr[], int left, int right);
void	ksort(int *arr, int n, int k);
void	radi_sort(int *arr, int size, int max_bits);
void	ft_selection_sort(int *arr, int n);
void	tag_sort(int *arr, int size);
void	tim_sort(int *arr, int n);
void	handle_duplicates(int *arr, int *pos, int item);
void	shell_sort(int *arr, int size);
void	heap_sort(int *arr, int size);
void	odd_even_sort(int *arr, int size);
void	bitonic_sort(int *arr, int size);
void	stooge_sort(int *arr, int size);
void	pancake_sort(int *arr, int size);
void	pigeonhole_sort(int *arr, int size);
void	intro_sort(int *arr, int size);
void	three_way_merge_sort(int *arr, int size);
void	mini_pushswap_hybrid(int *arr, int size, int *tag_to_value);

// Wrapper functions
void	insertion_sort_wrapper(int *arr, int size);
void	merge_sort_wrapper(int *arr, int size);
void	quick_sort_wrapper(int *arr, int size);
void	radix_sort_wrapper(int *arr, int size);
void	cycle_sort_wrapper(int *arr, int size);
void	ksort_wrapper(int *arr, int size);
void	bubble_sort_wrapper(int *arr, int size);
void	sleep_sort_wrapper(int *arr, int size);

int		*ft_sleep_sort(int *arr, int size);
int		*ft_bubble_sort(int *arr, int size);
int		ft_cycle_sort(int *arr, int size);
int		get_min(int *arr, int size);
int		*ft_quick_sort(int *arr, int low, int high);
int		get_max(int *arr, int size);
int		find_min_index(t_stck *stack);
int		ft_min(int a, int b);
int		cmp_int(const void *a, const void *b);

void	three_way_merge_sort_rec(int *arr, int *bounds, int *temp);
void	merge_three_way(int *arr, int *temp, int *bounds);
void	merge_and_copy_remaining(int *arr, int *temp, int *bounds,
			int *indices);
void	merge_remaining_elements(int *arr, int *temp, int *bounds,
			int *indices);
void	merge_three_parts(int *arr, int *temp, int *bounds, int *indices);

// Chunk sort helpers
void	distribute_elements(int *arr, int size, int **chunks, int *counts);
void	sort_and_merge_chunks(int *arr, int **chunks, int *counts, int num);
void	cleanup_chunks(int **chunks, int *chunk_counts, int num_chunks);
void	choose_chunk_size_and_process(int *normalized_arr, int size);
void	process_chunks(int *normalized_arr, int size, int num_chunks);

// Bitonic sort helpers

// Greedy sort helpers
void	initialize_stacks(t_stck *a, t_stck *b, int *arr, int size);
void	copy_result_back(int *arr, t_stck *a, int size);

// Cycle sort helpers

#endif