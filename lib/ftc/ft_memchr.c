/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:20:40 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/25 18:12:11 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

/**
 * @brief		Finds the first occurence of a byte(c) in a memory block
 * 
 * @param s		String to be searched
 * @param c		Char to find
 * @param n		No of bytes to search
 * @return		Pointer to malloc(ed) string starting from the found char
 * 				NULL if not char not found within 'n' bytes
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ps;
	unsigned char		uc;

	ps = (const unsigned char *)s;
	uc = (unsigned char)c;
	while (n--)
	{
		if (*ps == uc)
			return ((void *)ps);
		ps++;
	}
	return (NULL);
}

/*
int main(void)
{
    char string[] = "Hello, World!";
    char *result = ft_memchr(string, 'W', sizeof(char *));

    if (result != NULL)
        printf("Position: %li\n", result - string);
        // Output - Position : 7 
    else
        printf("Not found\n");
    return (0);
}
*/

/*
LOGIC :
	1. Pointer Casting
		- pointer s to unsigned char s to handle memory as bytes
		- converts int c to unsigned char
		- of the same type to ensure same value
	2. Loop through memory
		- while (n--)
		- inside loop, check current byte
	3. Compare each byte
		- if current byte matches, return void pointer to that byte
		- WHY VOID? generic pointer type, prototype compatibility (same as param)
	4. Increment pointer
		- move next byte in memory block
	5. Return NULL if loop completes but no match
*/
