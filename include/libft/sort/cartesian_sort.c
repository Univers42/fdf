/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartesian_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:13:35 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/11 10:42:57 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

static t_node	*create_node(int value, int index)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->value = value;
	node->index = index;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static t_node	*insert_cartesian(t_node *root, int value, int index)
{
	if (!root)
		return (create_node(value, index));
	if (index < root->index)
	{
		if (value > root->value)
		{
			root->left = create_node(value, index);
			root->left->right = root;
			return (root->left);
		}
		root->left = insert_cartesian(root->left, value, index);
	}
	else
		root->right = insert_cartesian(root->right, value, index);
	return (root);
}

static void	inorder_traversal(t_node *root, int *result, int *idx)
{
	if (!root)
		return ;
	inorder_traversal(root->left, result, idx);
	result[(*idx)++] = root->value;
	inorder_traversal(root->right, result, idx);
}

static void	free_tree(t_node *root)
{
	if (!root)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	free(root);
}

void	cartesian_sort(int *arr, int size)
{
	t_node	*root;
	int		*result;
	int		i;
	int		idx;

	if (!arr || size <= 1)
		return ;
	root = NULL;
	result = malloc(size * sizeof(int));
	if (!result)
		return ;
	i = -1;
	while (++i < size)
		root = insert_cartesian(root, arr[i], i);
	idx = 0;
	inorder_traversal(root, result, &idx);
	i = -1;
	while (++i < size)
		arr[i] = result[i];
	(free(result), free_tree(root));
}
