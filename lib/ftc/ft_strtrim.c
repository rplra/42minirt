/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:59:05 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/25 15:01:10 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
#include "libft.h"

static int	ft_isset(char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

/**
 * @brief		Allocates memory for a new string,
 * 				Trims set chars from start and end of given string
 * 
 * @param str	String to trim
 * @param set	Char set to trim
 * @return		Pointer to newly malloced trimmed string
*/
char	*ft_strtrim(const char *s1, const char *set)
{
	char	*start;
	char	*end;
	char	*strim;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = (char *)s1;
	end = start + ft_strlen(s1);
	while (*start && ft_isset(*start, set))
		start++;
	while (start < end && ft_isset(*(end - 1), set))
		end--;
	strim = ft_substr(start, 0, end - start);
	return (strim);
}

/* int main(void)
{
    const char *s1 = "!***Expacto Patronum***!";
    const char *set = "!*";

    char *trimmed = ft_strtrim(s1, set);
    printf("Trimmed string: %s\n", trimmed);
    return (0);
} */

/*
LOGIC :
	1. Check if string is NULL > if true > return  NULL
	2. Initialize start to beginning of s1
		-   Iterate start & check if start == set
		-   If true, immediately move to next char in s1, 
			continues until a char not in set is found, or end of s1 is reached
	3. Initialize end to end of s1
		- Iterate end, check if start < end && ft(*(end - 1<null>), set)
		- If true, immediately move to earlier char in s1
	4. Extract substring by calling ft_substr
		- malloc already allocated in the fx ft_substr
		- extract starting from first nonset to last nonset
		- return a new substring / trimmed string
*/