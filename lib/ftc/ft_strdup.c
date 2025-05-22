/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:57:22 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/20 19:54:55 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

/**
 * @brief		Allocates memory for a new string, copies the contents
 * 				of the provided string into the newly allocated memory
 * 
 * @param str	String to be duplicated
 * @return		Pointer to duplicated string. NULL if malloc fails.
*/
char	*ft_strdup(const char *str)
{
	size_t	i;
	size_t	len;
	char	*memory;

	len = ft_strlen(str);
	memory = malloc((len + 1) * sizeof(char));
	if (memory == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		memory[i] = str[i];
		i++;
	}
	memory[len] = '\0';
	return (memory);
}
/*
int main(void)
{
	const char *str = "Expacto Patronum!";

	char *sdup = ft_strdup(str);
	printf("Duplicated string: %s\n", sdup);
	return (0);
}
*/

/*
LOGIC :
1. Memory Allocation
    - Calculates the length of string (no of elements)
    - Allocates memory using malloc, including null terminator
2. String copy
    - Copies input string into the newly allocated mem block
    - Uses a loop to copy until it encounters null terminator
3. Null Termination
    - After finished copying, manually terminates (add '\0') at the end
4. Return Pointer
*/