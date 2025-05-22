/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:09:59 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/20 19:38:44 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

/**
 * @brief		Compares not more than 'n' chars of strings s1 & s2
 * 
 * @param s1	String to compare
 * @param s2	String to compare
 * @return		Int difference in ASCII values up to 'n' constraint
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/* int	main(void)
{
	char s1[] = "Hello!";
	char s2[] = "Henlo!";

	int result = ft_strncmp(s1, s2, 5);

	printf("Result: %i\n", result);
	return (0);
} */

/*
LOGIC :
1. loop while i < n (iterate through n desired)
2. loop while 
	- s1 is not equal to s2, OR
	- s1 is not empty, OR
	- s2 is not empty
3. if one of the conditions fulfill, return the difference
4. increment i
*/