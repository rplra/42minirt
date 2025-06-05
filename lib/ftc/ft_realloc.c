/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:13:41 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/05 13:08:58 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief			Reallocates memory for an array of elements and
 * 					initialize all bytes to zero.
 * 
 * @param ptr		Pointer to memory previously allocated
 * @param new_size	New size of variable(type/byte)
 * @return			Pointer to the newly allocated memory
*/
void *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*memory;
	size_t	copy_size;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0)
		return (free(ptr), NULL);
	memory = malloc(new_size);
	if (memory == NULL)
		return (NULL);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(memory, ptr, copy_size);
	free(ptr);
	return (memory);
}

