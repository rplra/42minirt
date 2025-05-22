/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:31:17 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/21 13:05:44 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
#include "libft.h"

/**
 * @brief 		Frees a node and its content in a linked list,
 * 				but not the next node in the list.
 * 
 * @param lst 	Pointer to node to be freed
 * @param new	Function that frees the content of the node
 * @return		None
*/
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst != NULL && del != NULL)
	{
		del(lst->content);
		free(lst);
	}
}

/* int main(void)
{
	// Initialize an empty list
	t_list *list = NULL; 

	// Create some nodes
	t_list *node1 = ft_lstnew("Node 1");
	t_list *node2 = ft_lstnew("Node 2");
	t_list *node3 = ft_lstnew("Node 3");

	// Add nodes to the list
	ft_lstadd_back(&list, node1);
	ft_lstadd_back(&list, node2);
	ft_lstadd_back(&list, node3);

	// Prints original list
	t_list *current = list;
	printf("Original list: ");
	
	while (current != NULL)
		printf("%s ", (char *)current->content);
		current = current->next;
	printf("\n");

	// Delete the first node
	if (list != NULL)
	{
    t_list *temp = list;
    list = list->next;
    ft_lstdelone(temp, free);
	}

	// Print the updated list
	if (list != NULL)
	{
		current = list;
		printf("Updated list: ");
		while (current != NULL)
		{
			printf("%s ", (char *)current->content);
			current = current->next;
		}
		printf("\n");
	}
	else
		printf("Updated list: Empty\n");
	
	return (0);
} */

/*
LOGIC : 
	1. Check if list is not NULL
	2. Call the function del(list->content) // deletes the content in that node
	3. free(lst) // once deleted, free the node in list
*/