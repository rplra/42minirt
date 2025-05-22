/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:51:22 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/21 17:11:48 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

/**
 * @brief		Copies ememory from one location to another
 * 
 * @param dest	String to copy to
 * @param src	String to copy from
 * @param n		Size of bytes to copy
 * @return		Pointer to typacasted dest (str copied)
*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		i;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (char *)dest;
	s = (const char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}

/* int main(void)
{
	const void *src = "Expacto Patronum!";
	char dest[20];

	ft_memcpy(dest, src, sizeof(src));
	printf("Copied string: %s\n", dest);
	return (0);
} */
/*
LOGIC :
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
	3. Copy n bytes from src to dest
	4. Return dest
*/