/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 07:48:17 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/25 15:19:17 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
#include "libft.h"

static unsigned int	sft_ilen(int n)
{
	unsigned int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

/**
 * @brief		Allocates memory for a new string,
 * 				Converts integer n to a string of char
 * 
 * @param n		Integer to be converted
 * @return		Malloc(ed) string of converted string
 * 				Negative numbers must be handled.
*/
char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	nb;
	unsigned int	len;

	len = sft_ilen(n);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		nb = -n;
	}
	else
		nb = n;
	if (n == 0)
		str[0] = '0';
	str[len] = '\0';
	while (nb != 0)
	{
		str[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}

/* int main(void)
{
	int n = -911;
	char *result = ft_itoa(n);

	printf("Result: %s\n", result);
	free(result);
	return (0);
} */

/*
LOGIC : 
	**ft_strlen
	1. Calculate length of string
		- initialize len to 0
		- check for negative / zero, allocate 1 space
		- check if n != 0
			- continuously divide and increment to get len
	**ft_itoa
	1. Initialize var
		- str to return result string
		- nb to handle abs value of n
		- len to assign nb in str
	2. Handle negative numbers
		- check for negative (n < 0)
		- if true, assign '-' to string
		- then assign abs value n to nb
		- else, assign abs value n to nb
	3. Handle zero
		- if n == 0, assign zero to string
		- null terminate string
	4. Convert integer to string (construct string)
		- immediately decrement len to store last digit (mod)
		- keep /10 to extract digit > mod
	5. Add null terminator 
		- because str[len] was already assigned null in step 3
		- thus no need
	6. Return the resulting string
*/