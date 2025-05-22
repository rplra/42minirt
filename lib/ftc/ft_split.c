/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:14:52 by rraja-az          #+#    #+#             */
/*   Updated: 2024/11/25 14:01:24 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

/**
 * @brief		Splits original string 's' into substrings,
 * 				using char 'c' as delimiter.
 * 
 * @param s		String to to split
 * @param c		The delimiter
 * @return		None
*/
static size_t	sft_strcount(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (count);
}

char	**ft_split(const char *s, char c)
{
	char	**str;
	size_t	i;
	size_t	len;

	if (s == NULL)
		return (0);
	str = malloc((sft_strcount(s, c) + 1) * sizeof(char *));
	if (str == NULL)
		return (0);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				++s;
			str[i++] = ft_substr(s - len, 0, len);
		}
		else
			++s;
	}
	str[i] = 0;
	return (str);
}

/* int main(void)
{
	const char s[] = "never too small!";
	char c = ' ';
	char **result = ft_split(s, c); // Corrected function call

	if (!result)
	{
		fprintf(stderr, "Memory allocation failed.\n");
		return 1;
	}

	printf("String Count: %zu\n", sft_strcount(s, c));

	int i = 0;
	while (result[i] != NULL)
	{
		printf("%s\n", result[i]);
		free(result[i]);
		i++;
	}
	free(result); // Free the array of pointers

	return 0;
} */

/* char	**ft_split(const char *s, char c)
{
	char	**str; // points to substrings
	size_t	i; // index
	size_t	len; // length of substring

	if (s == NULL)
		return (0);
	
	// Allocate malloc for substrings, s[x], s[last] = NULL;
	str = malloc((sft_strcount(s, c) + 1) * sizeof(char *));
	if (str == NULL)
		return (0);
	i = 0;
	// Iterate through string
	while (*s)
	{
		// To skip c if they occur in front of string
		if (*s != c)
		{
			// Calculate length of substring
			len = 0;
			while (*s && *s != c && ++len)
				++s; // move pointer
			str[i++] = ft_substr(s - len, 0, len); // creates substring
			// s - len (pointer arithmetic)
		}
		else
			++s;
	}
	str[i] = 0; // null terminate the substring
	return (str);
} */

/*
LOGIC :
COUNT NO OF SUBSTRINGS
1. Declare var count and initialize to 0
2. Iterate string
	- Check if index string is not same as delimiter
	- Increment no of count to 1
	- Loop string and string != c // Iterate through substring
		- Move to next index
	- Else if str == c move to next index then enter if to add count
3. Return count

FT_SPLIT
1. Declare 3 variables
	- char **str; pointer to an array of char pointers (stores substring)
	- size_t i	; index
	- size_t len; legnth of substring
2. CHECK FOR NULL
3. Initialize index = 0
4. Allocate memory for substrings (+ 1 for null) > CHECK IF SUCCESSFUL
5. Iterate through string to split
	- if string is not delimiter
		- len = 0; (for substring)
			- move 's' pointer forward & increments len until it reaches null / c
		- if string pointer points at delimiter
		- create substring
	- if string is delimiter, move pointer s
6. Null terminate once 's' reaches null
7. Return pointer to substrings
*/