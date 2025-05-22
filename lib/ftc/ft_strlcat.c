/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:52:19 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/21 16:44:26 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

/**
 * @brief		Concatenates two strings, with size limit for dest.
 * 				Added safety feature to prevent buffer overflow.
 * 
 * @param dest	Pointer to destination string
 * @param src	Pointer to src string
 * @param size	Size limit for dest, including null
 * @return		Returns the total length of string it tried to create; 
				the initial length of dest + length of src,
				with the goal to facilitate truncation detection.
*/
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	d;
	size_t	s;
	size_t	i;

	if (dest == NULL && size == 0)
		return (ft_strlen(src));
	d = 0;
	while (dest && dest[d] && d < size)
		d++;
	s = 0;
	while (src[s])
		s++;
	if (size == 0 || d >= size)
		return (size + s);
	i = 0;
	while (src[i] && (d + i) < (size - 1))
	{
		dest[d + i] = src[i];
		i++;
	}
	if (d + i < size)
		dest[d + i] = '\0';
	return (d + s);
}

/*
int	main(void)
{
	char dest[20] = "Mary had a ";
	char src[] = "little lamb";
	size_t size = sizeof(dest);

	size_t result = ft_strlcat(dest, src, 10);

	printf("strlcat : %zu\n", ft_strlcat(dest, src, 10));
	printf("ft_strlcat: %zu\n", result);
	return (0);
}
*/

/*
LOGIC :
	1. Calculate length of dest up to size
	2. Calculate length of src
	3. Check if size is zero, or d is greater than or equal to size
	(if true, return size + s) WHY?
		if size == 0;
		- gives length of str it tried to create
		if d >= size
		- d is atleast 'size', indicating len of str
		that would have been created if enough space
	4. append src to dest up to size - 1 (buffer for null terminator)
	5. null terminate dest
	6. return total length of string tried to create
*/

/*
DEBUG :
your strlcat crush when null parameter is sent with a size of 0

if (dest == NULL && size == 0)
		return (ft_strlen(src));
1. Check if dest && size is zero > true? >
	return src length (len it is supposed to create)

while (dest && dest[d] && d < size)
		d++;
2. ALSO check if dest is not null
	- dest[d] ; current index is not null
	- d < size ; ensures no overflow
*/