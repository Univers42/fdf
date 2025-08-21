/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:44:49 by dlesieur          #+#    #+#             */
/*   Updated: 2025/05/28 10:22:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H
# include <stddef.h>
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

// Add the prototype for ft_lstnew
t_list	*ft_lstnew(void *content);
t_list	*create_node(void *content);
t_list	*create_linked_list(int *arr, int n);
t_list	*deleteatposition(t_list *head, int pos);
t_list	*sorted_merge(t_list *head1, t_list *head2);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
t_list	*delete_head(t_list *head);
t_list	*remove_duplicates(t_list *head);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
int		ft_lstsize(t_list *lst);
int		issorted(t_list *head);
int		kth_end_from_linked_list(t_list *head, int k);
int		search_content_lst(t_list *head, int x);

#endif