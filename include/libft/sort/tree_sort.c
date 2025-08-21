/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:16:13 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

static t_tree_node	*create_tree_node(int data)
{
	t_tree_node	*tree;

	tree = malloc(sizeof(t_tree_node));
	if (!tree)
		return (NULL);
	tree->data = data;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

static t_tree_node	*insert_node(t_tree_node *root, int data)
{
	if (root == NULL)
		return (create_tree_node(data));
	if (data < root->data)
		root->left = insert_node(root->left, data);
	if (data > root->data)
		root->right = insert_node(root->right, data);
	return (root);
}

static void	inorder_traversal(t_tree_node *root, int *res, int *index)
{
	if (root == NULL)
		return ;
	inorder_traversal(root->left, res, index);
	res[(*index)++] = root->data;
	inorder_traversal(root->right, res, index);
}

static void	free_tree(t_tree_node *root)
{
	if (root == NULL)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	free(root);
}

void	tree_sort(int *arr, int size)
{
	t_tree_node	*root;
	int			index;
	int			i;

	if (!arr || size <= 1)
		return ;
	root = NULL;
	index = 0;
	i = 0;
	while (i < size)
	{
		root = insert_node(root, arr[i]);
		if (!root)
		{
			free_tree(root);
			return ;
		}
		i++;
	}
	inorder_traversal(root, arr, &index);
	free_tree(root);
}

//int main(void)
//{
//    // Test case 1: Random array
//    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
//    int size1 = sizeof(arr1) / sizeof(arr1[0]);
//    
//   	ft_printf("=== Tree Sort Test ===\n");
//    print_array_tree(arr1, size1, "Before sorting");
//    tree_sort(arr1, size1);
//    print_array_tree(arr1, size1, "After sorting");
//    
//    // Test case 2: Already sorted
//    int arr2[] = {1, 2, 3, 4, 5};
//    int size2 = sizeof(arr2) / sizeof(arr2[0]);
//    
//   	ft_printf("\n=== Already Sorted Test ===\n");
//    print_array_tree(arr2, size2, "Before sorting");
//    tree_sort(arr2, size2);
//    print_array_tree(arr2, size2, "After sorting");
//    
//    // Test case 3: Reverse sorted
//    int arr3[] = {5, 4, 3, 2, 1};
//    int size3 = sizeof(arr3) / sizeof(arr3[0]);
//    
//   	ft_printf("\n=== Reverse Sorted Test ===\n");
//    print_array_tree(arr3, size3, "Before sorting");
//    tree_sort(arr3, size3);
//    print_array_tree(arr3, size3, "After sorting");
//    
//    // Test case 4: With duplicates
//    int arr4[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
//    int size4 = sizeof(arr4) / sizeof(arr4[0]);
//    
//   	ft_printf("\n=== With Duplicates Test ===\n");
//    print_array_tree(arr4, size4, "Before sorting");
//    tree_sort(arr4, size4);
//    print_array_tree(arr4, size4, "After sorting");
//    
//    return (0);
//}