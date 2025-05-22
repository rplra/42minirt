/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:12:29 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/20 19:33:11 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

/**
 * @brief		Counts the length of given string
 * 
 * @param s		String to count length
 * @return		Number of char of a string
*/
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		s++;
		len++;
	}
	return (len);
}
/*
int	main(void)
{
	char *str = "Hello, world!\n";
	size_t strlen = ft_strlen(str);
	
	// Write string
	printf("String length: %zu\n", strlen);
	return (0);
}
*/