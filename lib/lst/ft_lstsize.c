/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:10:00 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/21 17:05:49 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
#include "libft.h"

/**
 * @brief 		Counts the number of nodes inside a linked list
 * 
 * @param lst 	Pointer to list that contains the nodes 
 * @return		No of nodes
*/
int	ft_lstsize(t_list *lst)
{
	size_t	count;

	count = 0;
	if (lst == NULL)
		return (0);
	while (lst != NULL && ++count)
		lst = lst->next;
	return (count);
}

/* 
int main(void)
{
	t_list *list = NULL;

	// Create nodes
	t_list *node1 = ft_lstnew("Node 1");
	t_list *node2 = ft_lstnew("Node 2");
	t_list *node3 = ft_lstnew("Node 3");

	// Add nodes to list pointer
	ft_lstadd_front(&list, node1);
	ft_lstadd_front(&list, node2);
	ft_lstadd_front(&list, node3);

	printf("%i\n", ft_lstsize(list));
	return (0);
} */

/*
LOGIC : 
	1. Initialize var to count
	2. CHECK FOR NULL
	3. Iterate through list and increment count simultaneously
	4. Move to next link
	5. Return count
*/