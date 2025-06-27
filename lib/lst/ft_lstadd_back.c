/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:35:00 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/27 13:31:17 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
#include "libft.h"

/**
 * @brief 		Adds the node 'new' at the end of the list
 * 
 * @param lst 	Pointer to the first link of list
 * @param new 	Pointer of node 'new' to be added to end of list
 * @return		None
*/
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = ft_lstlast(*lst);
	if (temp == NULL)
		*lst = new;
	else
		temp->next = new;
}

/* int main(void)
{
	t_list *list = NULL; // Initialize an empty list

	// Create some nodes
	t_list *node1 = ft_lstnew("Node 1");
	t_list *node2 = ft_lstnew("Node 2");
	t_list *node3 = ft_lstnew("Node 3");

	// Add nodes to the list
	ft_lstadd_back(&list, node1);
	ft_lstadd_back(&list, node2);
	ft_lstadd_back(&list, node3);

	// Print the list to verify
	t_list *last = list;
	while (last != NULL)
	{
		printf("%s\n", (char *)last->content); // print the data in last link
		last = last->next; // go to next to terminate
	}
	return (0);
} */

/*
LOGIC :
	1. CHECK FOR NULL
	2. Assign the temp var to contain pointer to last node in list
	3. Check if list is null > true > assign new node to list
	4. If not > access the temp link, assign new node to temp link
	5. VOILA
*/