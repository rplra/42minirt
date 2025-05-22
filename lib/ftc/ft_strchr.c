/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:36:56 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/20 20:00:31 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

/**
 * @brief		Locates the first occurence of char c in the string str.
				Terminating null char is considered part of str,
				if char c is '\0', the fx locate the terminating '\0'.
 * 
 * @param str	String to search
 * @param c		Char to find
 * @return		Pointer to located char. NULL if c is not found.
*/
char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (NULL);
}

/* int main(void)
{
	const char *str = "Expecto Patronum!";
	int c = 'P';

	printf("%c\n", )
 */

/*
string literal  = read only
const = string should not (and cannot) be modified

const char *s = pointer to the string which you want to search for character
int c = the character to search for (passed as int, internally converter to char)

HOW :
1. Fx starts searching from beginning of string
2. Checks each character in str one by one
3. If first occurence of char 'c' is found,
	returns pointer to that char within the string
4. If not found, return NULL
*/