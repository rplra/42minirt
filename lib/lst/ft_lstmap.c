/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:48:47 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/25 15:27:03 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
#include "libft.h"

/**
 * @brief 		Maps a function to a linked list, returns a new list.
 * 
 * @param lst 	Pointer to the linked list
 * @param f		Pointer to function that will be applied to each node's content
 * @param del	Pointer to function to delete the content of node if needed
 * @return		The new list. NULL if malloc fails
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*head;

	if (!lst || !f || !del)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (NULL);
	head = new;
	lst = lst->next;
	while (lst)
	{
		new->next = ft_lstnew(f(lst->content));
		if (!new->next)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		lst = lst->next;
		new = new->next;
	}
	new->next = NULL;
	return (head);
}
/*
LOGIC :
	1. Declare 2 pointers
		- New ; Points at new node
		- Head ; Points at the beginning of new list
	2. Create new node using ft_lstnew > CHECK IF SUCCESSFULY ALLOCATED
	3. Assign pointer head to point at new node
	4. Move list to next node
	5. Iterate through list
		- create new node; assign list content with applied fx
		- check if creation of node fails
		- if fails > ft_lstclear to delete list (give head address)
		- if not, move both new and list to next node
	6. When list is null > null terminate the last node in new
	7. Return pointer head that pointed to new (returns new list)
*/