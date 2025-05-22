/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:21:38 by rraja-az          #+#    #+#             */
/*   Updated: 2025/01/07 14:33:32 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include "libft.h"

/**
 * @brief			Extract a portion of a string.
 * 
 * @param s 		string to be extracted
 * @param start		specified index (position) of string to extract
 * @param len		specified length of string to extract
 * @return			(char *) Pointer to a newly extracted string 
*/
char	*ft_substr(const char *s, size_t start, size_t len)
{
	char	*substring;
	size_t	slen;
	size_t	n;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (start + len > slen)
		len = slen - start;
	substring = malloc((len + 1) * sizeof(char));
	if (substring == NULL)
		return (NULL);
	n = 0;
	while (n < len)
	{
		substring[n] = s[start + n];
		n++;
	}
	substring[len] = '\0';
	return (substring);
}

/*
int main(void)
{
	const char *s = "Expacto Patronum!";
	char *substring = ft_substr(s, 7, 12);
	if (substring != NULL)
	{
		printf("Substring: %s\n", substring);
		free(substring);
		return (0);
	}
	else
	{
		printf("Substring not found.\n");
		return (1);
	}
}
*/

/*
	LOGIC :
	1. Check if string is empty > if true > return NULL
	2. Calculate the length of string (used for bounds checking and malloc)
	3. Check if start index is beyond length of input string
		- if start is beyond end of string, return NULL
	4. Adjust the length (if necessary) to avoid going out of bounds
		- ensures sublen is not beyond end of slen
		- if (start + len > slen); means substr will go beyond end of slen
		- len is then adjust to ensure substr stays within the bounds of s
	2. Allocate memory
		- size of memory block to match strlen + 1 (null terminator)
	3. Copy Characters
		- copies specified substring from src to memory block
	4. Return pointer to newly created substring in memory

	DEBUG :
	if (start >= slen)
			return (ft_strdup("")); // instead of returning NULL
	WHY return ("")?
		- returns a pointer to a newly allocated empty string
		- the caller receives a valid pointer to an empty string
			which can be used and manipulated like any other string
		- since the return value is a pointer
	IF return NULL
		- NULL signals failure of invalid input
*/