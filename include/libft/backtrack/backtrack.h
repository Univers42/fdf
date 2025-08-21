/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:27:56 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/21 19:14:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKTRACK_H
# define BACKTRACK_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct s_tree_node
{
	void				*content;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}						t_tree_node;

char	**binaryTreePaths(t_tree_node *root, int *returnSize);

#endif