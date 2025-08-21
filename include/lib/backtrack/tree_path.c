/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:27:37 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backtrack.h"

//// Utility to create a new tree node
//t_tree_node *create_node(int val)
//{
//    t_tree_node *node;
//
//    node = malloc(sizeof(t_tree_node));
//    if (!node)
//        return (NULL);
//    int *pval = malloc(sizeof(int));
//    if (!pval) {
//        free(node);
//        return (NULL);
//    }
//    *pval = val;
//    node->content = pval;
//    node->left = NULL;
//    node->right = NULL;
//    return (node);
//}
//
//int  count_leaves(t_tree_node *root)
//{
//    if (root == NULL)
//        return (0);
//    if (root->left == NULL && root->right == NULL)
//        return  1;
//    return (count_leaves(root->left) + count_leaves(root->right));
//}
//
//void free_all(t_tree_node *root)
//{
//    if (root == NULL)
//        return;
//    free_all(root->left);
//    free_all(root->right);
//    free(root->content);
//    free(root);
//}

//void buildPaths(t_tree_node *node, char **paths,
//int *returnSize, char *currentPath, int pathLen)
//{
//    if (!node) return;
//
//    // Append current node's value to currentPath
//    int len = sprintf(currentPath + pathLen, "%d", *(int *)(node->content));
//    pathLen += len;
//
//    // If leaf, save the path string
//    if (!node->left && !node->right) {
//        paths[*returnSize] = strdup(currentPath); // allocate and copy string
//        (*returnSize)++;
//        return;
//    }
//
//    // If not leaf, add "->" and recurse
//    currentPath[pathLen++] = '-';
//    currentPath[pathLen++] = '>';
//    currentPath[pathLen] = '\0';
//    buildPaths(node->left, paths, returnSize, currentPath, pathLen);
//    buildPaths(node->right, paths, returnSize, currentPath, pathLen);
//}
//
//char **binaryTreePaths(t_tree_node *root, int *returnSize)
//{
//    char    **paths;
//    int     size;
//    char    currentPath[100];
//
//    if (!root) 
//    {
//        *returnSize = 0;
//        return (NULL);
//    }
//    size = count_leaves(root);
//    paths = malloc(sizeof(char*) * size);
//    *returnSize = 0;
//    currentPath[0] = '\0';
//    buildPaths(root, paths, returnSize, currentPath, 0);
//    return (paths);
//}
//
//int main(void)
//{
//    int returnSize;
//    char **paths;
//    t_tree_node *root = create_node(1);
//    root->left = create_node(2);
//    root->right = create_node(3);
//    root->left->right = create_node(5);
//    paths = binaryTreePaths(root, &returnSize);
//    for (int i = 0; i < returnSize; i++)
//    {
//       	ft_printf("%s\n", paths[i]);
//        free(paths[i]);
//    }
//    free(paths);
//    free_all(root);
//    return 0;
//}