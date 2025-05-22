/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:54:17 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/25 14:50:49 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <stdlib.h>
//#include <stddef.h>
//#include <string.h>
#include "libft.h"

/**
 * @brief		Allocates memory for a new string; 
 * 				concatenation of s1 and s2
 * 
 * @param s1	String to join
 * @param s2	String to join
 * @return		Pointer to new string with joined s1 and s2
*/
char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*string;
	size_t	len;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	string = malloc((len + 1) * sizeof(char));
	if (string == NULL)
		return (NULL);
	i = 0;
	while (*s1)
		string[i++] = *s1++;
	while (*s2)
		string[i++] = *s2++;
	string[i] = '\0';
	return (string);
}

/*
int	main(void)
{
	const char *s1 = "Hello, ";
	const char *s2 = "World!";

	// Calls fx
	char *result = ft_strjoin(s1, s2);

	if (result != NULL)
	{
		printf("After strjoin: %s\n", result);
		free(result);
	}
	else
		printf("Malloc failed.\n");
	return (0);
}
*/

/*
    LOGIC :
    1. Check if either s1 or s2 is NULL > if true > return NULL
    2. Calculate total length
        - sum the length of all strings
        - (IF NEEDED) add the length of delimiter * n of delimiters needed 
            (which is one less than the number of string)
	3. Allocate memory for the resulting string
    4. Concatenate strings (and delimiters)
        - copy each string (and delimiter) into allocated mem sequence
	5. Null terminate the string
	6. Return string
*/