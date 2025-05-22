/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:23:24 by rraja-az          #+#    #+#             */
/*   Updated: 2024/07/25 20:35:29 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
#include "libft.h"

/**
 * @brief		Copies overlapping memory block safely
 * 
 * @param dest	String to copy to
 * @param src	String to copt from
 * @param n		Size of bytes to copy
 * @return		Pointer to typacasted dest (str copied)
*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (char *)dest;
	s = (const char *)src;
	if (s < d && d < s + n)
	{
		while (n--)
			d[n] = s[n];
	}
	else
	{
		while (n--)
			*d++ = *s++;
	}
	return (dest);
}

/*
int main(void)
{
	const char *src = "Hello, World!";
	char d[20];

	ft_memmove(d, src, 5);
	printf("MSN5: %s\n", d);
	// Output: Hello

	ft_memmove(d + 1, src, 5);
	printf("MSN5a: %s\n", d);
	// Output: HHello

	ft_memmove(d + 1, src + 3, 5);
	printf("MSN5b: %s\n", d);
	// Output: Hlo, W

	ft_memmove(d + 3, src + 1, 5);
	printf("MSN5b: %s\n", d);
	// Output: Hloello,

	ft_memmove(d, src, strlen(src) + 1);
	printf("MS1: %s\n", d);
	// Output: Hello, World!


	ft_memmove(d + 3, src, strlen(src) + 1);
	printf("MS2: %s\n", d);
	// Output: HelHello, World!
	
	return (0);

}
*/

/*
LOGIC:
	1. Check if dest comes before src
		- copies memory from src to dest, from beginning
	2. Check if src comes before dest
		- copy memory from src to dest, starting from end
	3. If no overlap
		- copies src to dest (memcpy)
*/

/*
	1. Check for NULL or zero length
	2. Typecast dest and src pointers to char pointers
		- WHY?
		- void * is a generic pointer type that can point to any data type, 
		but it cant be used for pointer arithmetic / dereferencing because the
		compiler doesn't know the size of the data it points to
		- by casting pointers to char *, we're telling the compiler to treat
		these pointers as pointers to characters (bytes), which allows to perform
		byte-wise operations
		- we can access the memory byte by byte
		- once casted, can ++ / -- (move), enabling us to copy memory in a loop
		- summary, allow to access and manipulate memory byte by byte
	3. Check if src and dest memory regions overlap, if yes, copy backwards
		- (s < d)
		- 	checks if source region is before the start of destination region
		- (d < s + n)
		-	checks if start of destination region is before
			the end of source region (s + n)
	4. Else if no overlap, copy forward
	5. Return dest
*/