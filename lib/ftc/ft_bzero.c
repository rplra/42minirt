/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:17:20 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/20 15:30:59 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"
/**
 * @brief		Set n bytes of string to zero
 * 
 * @param str	Pointer to string to reset to zero
 * @param n		No of bytes to reset to zero
 * @return		None
*/
void	ft_bzero(void *str, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)str;
	while (n--)
		*ptr++ = 0;
}

/*
int main(void)
{
	int i;

    // Allocate n bytes
	char buffer[10];
	
    // Fill n bytes
	i = 0;
	while (i < 10)
		buffer[i++] = 'A';

    // Print n bytes before bzero
	i = 0;
    printf("Before: \n");
	while (i < 10)
		printf("%c ", buffer[i++]);
	printf("\n");

    // Call function
	ft_bzero(buffer, 10);

    // Print n bytes after bzero
	i = 0;
    printf("After: \n");
	while (i < 10)
		printf("%c", buffer[i++]);
	printf("\n");
	
	return (0);
}
*/

/*
    LOGIC : 
    1. Pointer declaration and initialization of void str to unsigned char str
    2. Iterates the first 'n' bytes of memory area pointed to by 'str'
    3. For each byte, bzero sets it to the value of 0 (0 == '\0')

	HOW & WHY :
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
    	-   in each iteration, current byte pointed by ptr is set to 0
    	-   p incremented to move to next byte
*/