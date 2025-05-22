/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:42:34 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/21 13:15:44 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
#include "libft.h"

/**
 * @brief			Creates a new node with a given value
 * 
 * @param content 	Data / Value to store in the new node 
 * @return 			New node
*/
t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

/* int main(void)
{
	// Create a new node with a string content
	t_list *node1 = ft_lstnew("Hello, world!");
	if (node1 == NULL)
		return (1); // handle malloc failure
	
	// Create another node with an integer content
	int num = 42;

	// add & because it expects pointer (address)
	t_list *node2 = ft_lstnew(&num);
	if (node2 == NULL)
		return (1); // handle malloc failure

	// Link the two nodes together
	node1->next = node2;

	// Print contents of the nodes
	printf("Node 1: %s\n", (char *)node1->content); // typecast void to char
	printf("Node 2: %d\n", *(int *)node2->content); // adds * to dereference

	// Free malloc
	free(node1);
	free(node2);

	return (0);
} */

/*
LOGIC :
	1. Declare new variable for pointer to point at new node
	2. Allocate memory for pointer at new node
		- CHECK IF MALLOC FAILS
	3. Access content(data) and assign content (data input by user)
	4. Access next(link) and assign NULL if there's no linkage / end of node
	5. Return pointer pointing to new node
*/