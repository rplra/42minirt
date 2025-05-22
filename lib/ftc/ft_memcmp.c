/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 08:42:10 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/21 13:27:05 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

/**
 * @brief		Compares first 'n' bytes between 2 memory blocks
 * 
 * @param s1	String to be searched
 * @param s2	Char to find
 * @param n		Size of bytes to compare
 * @return		-ve (s1 < s2) | 0 (s1 == s2) | +ve (s1 > s2)
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	while (n--)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		p1++;
		p2++;
	}
	return (0);
}

/*
int main(void)
{
	const void *s1 = "Hello";
	const void *s2 = "Henlo";

	int result = ft_memcmp(s1, s2, 5);
	printf("Result: %i\n", result);
	return (0);
}
*/

/*
LOGIC : 
	1. Initilize by typecasting void to unsigned char
		- WHY unsigned char
		- ensures all byte values are consistent, from 0 to 255
		- signed char ranges from -128 to 127, incorrect comparison
		- avoid negative values
	2. Loop through bytes
		- Iterate over first 'n' bytes of memory blocks pointed by s1 and s2
		- For each byte, compare corresponding bytes from s1 and s2
	3. Compare bytes
		- If bytes differ, return the diff value
		- If bytes are equal, return 0
*/
