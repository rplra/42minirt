/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:23:55 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/21 17:05:13 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
#include "libft.h"

/**
 * @brief		Finds the last occurrence of a character in a string
 * 
 * @param str	String to search
 * @param c		Char to search
 * @return		Pointer to located char. NULL if not found.
*/
char	*ft_strrchr(char const *str, int c)
{
	char	*last;

	last = NULL;
	while (*str)
	{
		if (*str == (char)c)
			last = (char *)str;
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (last);
}

/* int main(void)
{
	const char *str = "Expecto Patronum!";
	int c = 'o';

	printf("%s\n", strrchr(str, c));
	printf("%s\n", ft_strrchr(str, c));
	return (0);
} */

/*
LOGIC :
1. Create a pointer to point to last 
	- set NULL to pointer if c is not found in str
2. Iterate string
3. Check if string == c
	- if true > assign pointer to pointer last
	- if not then move pointer
4. Check if c is NULL
	- if true > return pointer to string

*/