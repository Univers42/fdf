/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:50:25 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

static t_tagged_element	*create_tagged_array(int *arr, int size)
{
	t_tagged_element	*tag;
	int					i;
	int					j;
	int					rank;

	tag = malloc(size * sizeof(t_tagged_element));
	if (!tag)
		return (NULL);
	i = 0;
	while (i < size)
	{
		rank = 0;
		j = 0;
		while (j < size)
		{
			if (arr[j] < arr[i] || (arr[j] == arr[i] && j < i))
				rank++;
			j++;
		}
		tag[i].value = arr[i];
		tag[i].tag = rank;
		i++;
	}
	return (tag);
}

static void	place_by_tags(int *arr, t_tagged_element *tagged, int size)
{
	int	*temp_arr;
	int	i;

	temp_arr = malloc(size * sizeof(int));
	if (!temp_arr)
		return ;
	i = 0;
	while (i < size)
	{
		if (tagged[i].tag >= 0 && tagged[i].tag < size)
			temp_arr[tagged[i].tag] = tagged[i].value;
		i++;
	}
	i = 0;
	while (i < size)
	{
		arr[i] = temp_arr[i];
		i++;
	}
	free(temp_arr);
}

void	tag_sort(int *arr, int size)
{
	t_tagged_element	*tagged;

	tagged = create_tagged_array(arr, size);
	if (!tagged)
		return ;
	place_by_tags(arr, tagged, size);
	free(tagged);
}

//int main(void)
//{
//    int arr[] = {64, 34, 25, 12, 22, 11, 90};
//    int size = sizeof(arr) / sizeof(arr[0]);
//    
//   	ft_printf("=== Tag Sort Test ===\n");
//    print_array(arr, size);
//    tag_sort(arr, size);
//    print_array(arr, size);
//    
//    return (0);
//}