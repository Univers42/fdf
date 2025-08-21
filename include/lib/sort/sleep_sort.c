/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/28 16:52:01 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

static void	*sleep_and_store(void *arg)
{
	t_thread_data	*data;
	int				current_index;

	data = (t_thread_data *)arg;
	usleep(data->value * 1000);
	pthread_mutex_lock(data->mutex);
	current_index = (*data->index)++;
	data->result_array[current_index] = data->value;
	pthread_mutex_unlock(data->mutex);
	return (NULL);
}

static int	*allocate_resources(int size, pthread_t **threads,
	t_thread_data **thread_data)
{
	int	*result;

	*threads = malloc(size * sizeof(pthread_t));
	*thread_data = malloc(size * sizeof(t_thread_data));
	result = malloc(size * sizeof(int));
	if (!*threads || !*thread_data || !result)
	{
		free(*threads);
		free(*thread_data);
		free(result);
		return (NULL);
	}
	return (result);
}

static void	setup_thread_data(t_thread_data *thread_data, int *arr,
	int *result, pthread_mutex_t *mutex)
{
	int	*index;
	int	i;

	index = malloc(sizeof(int));
	*index = 0;
	i = 0;
	while (i < 10)
	{
		thread_data[i].value = arr[i];
		thread_data[i].result_array = result;
		thread_data[i].index = index;
		thread_data[i].mutex = mutex;
		i++;
	}
}

static void	join_threads(pthread_t *threads, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

int	*ft_sleep_sort(int *arr, int size)
{
	pthread_t		*threads;
	t_thread_data	*thread_data;
	pthread_mutex_t	mutex;
	int				*result;
	int				i;

	if (!arr || size <= 0)
		return (NULL);
	result = allocate_resources(size, &threads, &thread_data);
	if (!result)
		return (NULL);
	pthread_mutex_init(&mutex, NULL);
	setup_thread_data(thread_data, arr, result, &mutex);
	i = 0;
	while (i < size)
	{
		pthread_create(&threads[i], NULL, sleep_and_store, &thread_data[i]);
		i++;
	}
	join_threads(threads, size);
	pthread_mutex_destroy(&mutex);
	free(threads);
	free(thread_data);
	return (result);
}
