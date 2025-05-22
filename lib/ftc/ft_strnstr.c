/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:56:17 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/21 16:33:17 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
#include "libft.h"

/**
 * @brief			Locates a substring within a string, but only within
 *					the first 'n' characters of main string.
 * 
 * @param haystack	String to search
 * @param needle	Substring to search
 * @param n			N chars to search
 * @return			Pointer to substring in string
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	if (*needle == '\0' || haystack == needle)
		return ((char *)haystack);
	if (haystack == NULL && n == 0)
		return (NULL);
	i = 0;
	while (haystack[i] && i < n)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < n && needle[j])
			j++;
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}

/* int main (void)
{
	char *haystack = "Burgers and fries";
	char *needle = "fries";

	char *result1 = ft_strnstr(haystack, needle, 20);
	char *result2 = strnstr(haystack, needle, 20);

	printf("%s %s\n", result1, result2);
	return (0);
} */

/*
DEBUG : 

if (haystack == NULL && n == 0)
		return (NULL);
1. Check if haystack is empty and size is 0
	- no string to search
	- search size is zero
	- THEN? nothing to do > return NULL
*/

/*
LOGIC : 
	1. Check if haystack equals to needle OR needle is empty
		- return haystack
	2. Check if haystack && n is empty
		- return NUKK
	3. Iterate through haystack && i < n
	4. Loop (haystack == needle? && i + j < n ? && needle != null)
		- if true > increment j
		- if needle == null
			- return pointer of haystack 
	5. Otherwise move to next index in haystack
	6. Return NULL if haystack == NULL && n == 0
*/