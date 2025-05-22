/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:21:59 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/21 13:57:35 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

/**
 * @brief		Counts the length of copied string
 * 
 * @param dest	String to copy to
 * @param src	String to copy from
 * @param size	Size limit of dest buffer size
 * @return		Length of source / copied string
*/
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	while (src[src_len])
		src_len++;
	if (size > 0)
	{
		i = 0;
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (src_len);
}

/*
int	main(void)
{
	char src[] = "Hello, world!";
	char dest[15]; // Allocate proper buffer size for dest

	// Call function
	size_t copied_len = ft_strlcpy(dest, src, sizeof(dest));
	
	// Print results
	printf("Copied string: %s\n", dest);
	printf("Length of string: %zu\n", copied_len);
	return (0);
}
*/

/*
LOGIC :
	1. Iterate through source string and counts the length
	2. Check if limit 'n' is zero, if zero (no space in dest buffer),
		fx returns srclen
	3. Else, copies char from src to dest buffer whilst checking src is not null
	4. Continues until 'n' is zero / null terminator in src is reached >
		adds '\0' to dest to properly terminate dest
	5. Returns length of srclen
*/