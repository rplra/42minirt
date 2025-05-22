/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:39:36 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/21 13:12:52 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief		Moves to last node of the list
 * 
 * @param lst	The beginning of the list
 * @return		Last node of the list
*/
t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

/* int main(void)
{
	t_list *list = NULL; // Initialize an empty list

	// Create some nodes
	t_list *node1 = ft_lstnew("Node 1");
	t_list *node2 = ft_lstnew("Node 2");
	t_list *node3 = ft_lstnew("Node 3");

	// Add nodes to the list
	ft_lstadd_front(&list, node1);
	ft_lstadd_front(&list, node2);
	ft_lstadd_front(&list, node3);

	// Print the list to verify
	t_list *last = ft_lstlast(list);
	if (last != NULL)
		printf("%s\n", (char *)last->content);
	return (0);
} */

/*
LOGIC :
	1. CHECK FOR NULL
	2. Iterate while next node is not null
		- Move node
	3. Return node once NULL found
*/