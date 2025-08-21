/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-way-merge_sort_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/11 10:55:55 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

void	merge_three_parts(int *arr, int *temp, int *bounds, int *indices)
{
	while (indices[0] <= bounds[1] && indices[1] <= bounds[2]
		&& indices[2] <= bounds[3])
	{
		if (arr[indices[0]] <= arr[indices[1]]
			&& arr[indices[0]] <= arr[indices[2]])
			temp[indices[3]++] = arr[indices[0]++];
		else if (arr[indices[1]] <= arr[indices[0]]
			&& arr[indices[1]] <= arr[indices[2]])
			temp[indices[3]++] = arr[indices[1]++];
		else
			temp[indices[3]++] = arr[indices[2]++];
	}
}

void	merge_remaining_elements(int *arr, int *temp, int *bounds,
	int *indices)
{
	while (indices[0] <= bounds[1] && indices[1] <= bounds[2])
	{
		if (arr[indices[0]] <= arr[indices[1]])
			temp[indices[3]++] = arr[indices[0]++];
		else
			temp[indices[3]++] = arr[indices[1]++];
	}
	while (indices[1] <= bounds[2] && indices[2] <= bounds[3])
	{
		if (arr[indices[1]] <= arr[indices[2]])
			temp[indices[3]++] = arr[indices[1]++];
		else
			temp[indices[3]++] = arr[indices[2]++];
	}
	while (indices[0] <= bounds[1] && indices[2] <= bounds[3])
	{
		if (arr[indices[0]] <= arr[indices[2]])
			temp[indices[3]++] = arr[indices[0]++];
		else
			temp[indices[3]++] = arr[indices[2]++];
	}
}

void	merge_and_copy_remaining(int *arr, int *temp, int *bounds,
	int *indices)
{
	merge_remaining_elements(arr, temp, bounds, indices);
	while (indices[0] <= bounds[1])
		temp[indices[3]++] = arr[indices[0]++];
	while (indices[1] <= bounds[2])
		temp[indices[3]++] = arr[indices[1]++];
	while (indices[2] <= bounds[3])
		temp[indices[3]++] = arr[indices[2]++];
}

void	merge_three_way(int *arr, int *temp, int *bounds)
{
	int	indices[4];
	int	i;

	indices[0] = bounds[0];
	indices[1] = bounds[1] + 1;
	indices[2] = bounds[2] + 1;
	indices[3] = bounds[0];
	merge_three_parts(arr, temp, bounds, indices);
	merge_and_copy_remaining(arr, temp, bounds, indices);
	i = bounds[0];
	while (i <= bounds[3])
	{
		arr[i] = temp[i];
		i++;
	}
}

void	three_way_merge_sort_rec(int *arr, int *bounds, int *temp)
{
	int	mid_bounds[4];

	if (bounds[1] - bounds[0] < 1)
		return ;
	mid_bounds[0] = bounds[0];
	mid_bounds[1] = bounds[0] + (bounds[1] - bounds[0]) / 3;
	mid_bounds[2] = bounds[0] + 2 * (bounds[1] - bounds[0]) / 3;
	mid_bounds[3] = bounds[1];
	bounds[1] = mid_bounds[1];
	three_way_merge_sort_rec(arr, bounds, temp);
	bounds[0] = mid_bounds[1] + 1;
	bounds[1] = mid_bounds[2];
	three_way_merge_sort_rec(arr, bounds, temp);
	bounds[0] = mid_bounds[2] + 1;
	bounds[1] = mid_bounds[3];
	three_way_merge_sort_rec(arr, bounds, temp);
	merge_three_way(arr, temp, mid_bounds);
}
