/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:44:19 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/25 15:15:01 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
#include "libft.h"

/**
 * @brief 		Deletes and frees a linked list, along with its contents,
 * 				sets the list pointer to 'NULL'
 * 
 * @param lst 	Pointer to node to be freed
 * @param new	Function that deletes / free the content of the node
 * @return		None
*/
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (lst == NULL || del == NULL)
		return ;
	temp = *lst;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
}

/*
int main(void)
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

    // Print original list
    t_list *current = list;
    printf("Original list: ");
    while (current!= NULL)
    {
        printf("%s ", (char *)current->content);
        current = current->next;
    }
    printf("\n");

    // Clear the list using ft_lstclear
    ft_lstclear(&list, free);

    // Print the list after clearing
    if (list!= NULL)
    {
        current = list;
        printf("List after clearing: ");
        while (current!= NULL)
        {
            printf("%s ", (char *)current->content);
            current = current->next;
        }
        printf("\n");
    }
    else
    {
        printf("List after clearing: Empty\n");
    }

    return 0;
}
*/

/*
LOGIC :
	1. Create new temp pointer to point at list
	2. CHECK FOR NULL
	3. Iterate through list
		- assign next node to temp
		- deletes current node
		- assign temp to list
	4. Return NULL (emptied list)
*/