/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:19:48 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/25 15:19:51 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

// Dummy fx tester
/* char	sft_toupper(unsigned int i, char c)
{
	(void)i;
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
 */

/**
 * @brief		Allocates memory for a new string,
 * 				applies a function to each character in a string
 * 
 * @param s		String to iterate
 * @param f		Function to apply to char *
 * @return		Pointer to new string after fx-ed & malloc-ed
*/
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;
	size_t	slen;

	if (s == NULL)
		return (NULL);
	slen = 0;
	while (s[slen])
		slen++;
	str = malloc((slen + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < slen)
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[slen] = '\0';
	return (str);
}

/* int	main(void)
{
    char *s = "Expacto Patronum!";
    char *result = ft_strmapi(s, sft_toupper);

    printf("Result: %s\n", result);
    free (result);
    return (0);
} */

/*
LOGIC :
	**get length of s
	**check for NULL
	1. Allocate memory for the new string
	2. Iterate through each char of string 's'
	3. For each char, it calls the fx 'f'
		- first arg = index of char in str
		- second arg = char itself
	4. fx F returns new char
	5. New char added to new string
	6. Loop process
	7. Return string
*/