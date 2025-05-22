/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:30:51 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/21 13:07:17 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
#include "libft.h"

/**
 * @brief 		Applies a function to each element in a linked list
 * 
 * @param lst 	Pointer to the linked list
 * @param f		Function to apply
 * @return		None
*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*current;

	if (lst == NULL)
		return ;
	current = lst;
	while (current != NULL)
	{
		f(current->content);
		current = current->next;
	}
}

/*
LOGIC : 
	1. Declare var pointer current 
	2. CHECK FOR NULL
	3. Assign current to point at list
	4. Iterate using current pointer
	5. Apply fx(current->content)
	6. Move to next node
*/