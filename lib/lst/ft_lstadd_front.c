/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:20:34 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/21 12:43:27 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
#include "libft.h"

/**
 * @brief 		Adds a new node to the beginning of a linked list.
 * 				[NEW]->[.]->[.]->[.]->[NULL]
 * 
 * @param lst 	Pointer to pointer to the first node of the list
 * 				Allows function to modify the original list pointer
 * @param new	Pointer to the new node to be added to the list 
 * @return		None
*/
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
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
	t_list *current = list;
	while (current != NULL)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	return (0);
} */

/*
LOGIC :
	1. CHECK FOR NULL
	2. Access the new node's link and assign pointer (head)
	3. Assign new node to head pointer
*/