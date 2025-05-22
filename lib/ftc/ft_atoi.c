/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:48:41 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/20 14:30:29 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

/**
 * @brief		Converts a string char to int.
 * 
 * @param str	String to be converted.
 * @return		(int) The converted int.
*/
int	ft_atoi(const char *str)
{
	int	negative;
	int	result;

	negative = 1;
	result = 0;
	if (*str == '\0')
		return (0);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negative *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * negative);
}

/* int main(void)
{
    char str1[] = "   -++--9881lo91";
	char str2[] = "12-23";
	char str3[] = "12+23";
	char str4[] = "-12+23";
	char str5[] = "--12+23";

    printf("Result: %i\n", ft_atoi(str1);
	printf("Result: %i\n", ft_atoi(str2);
	printf("Result: %i\n", ft_atoi(str3);
	printf("Result: %i\n", ft_atoi(str4);
	printf("Result: %i\n", ft_atoi(str5);

    return (0);
} */

/*
	LOGIC : 
	1. check for white space
	2. check for '-' sign USING IF
		- WHY IF?
		- ensures the fx only considers the sign once
		- WHY ONCE?
		- atoi in libc is designed to handle simplest single integer
			- integer that may be preceded by whitespace
			- integer that may be preceded by SINGLE sign char (+ / -)
		- atoi in libc is not required to handle multiple signs
		- numbers in text are formatted with at most one sign char
			- handling multiple signs is not common and unnecessary
	3. check for numeric > * 10 to get base number, 
   		minus '0' to convert char to integer
	4. return result * negative
*/