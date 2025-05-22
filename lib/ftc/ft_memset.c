/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:19:09 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/21 13:35:05 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

/**
 * @brief		Fills a block of memory with a value
 * 
 * @param str	Pointer to memory block to be filled
 * @param c		Value to set
 * @param n		Size of bytes for n to set into memory block
 * @return		Pointer to typacasted str (str set)
*/
void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)str;
	while (n--)
		*ptr++ = (unsigned char)c;
	return (str);
}

/*
int main(void)
{
    char *str;
    int c = 'A';

    printf("Set String: %s\n", ft_memset(str, c, 10));
    return (0);
}
*/

/*
LOGIC :
	1. Converts 'int c' to unsigned char
	2. Iterates the first 'n' bytes of memory area pointed to by 'str'
	3. For each byte, memset sets it to the value of 'c'
*/

/*
1. unsigned char *ptr = (unsigned char *)str // casting pointer
    -   convert the 'void *str' to 'unsigned char *'
        because we need to work with individual bytes
    -   WHY?
    -   signed char (ascii -128 to 127), unsigned (ascii 0 to 255),
        avoids potential issues with sign extension (value > 127)
    -   avoid negative values; memaddress and values stored at those
        address are typically non-negative
    -   ensures every byte is treated as a simple, positive number
2. while (n--) // loop through memory block
    -   loop runs 'n' times, decrementing 'n' each time
    -   in each iteration, current byte pointed by ptr is set to value c
    -   p incremented to next byte
3. return (str) // return original pointer
*/
