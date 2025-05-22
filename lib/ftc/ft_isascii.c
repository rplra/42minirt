/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 08:03:08 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/21 12:40:03 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

/**
 * @brief		Checks if char is an ascii (0 ~ 127)
 * 
 * @param c		Char to check
 * @return		True (1) / False (0)
*/
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/*
int main(void)
{
	int c = 'A';
	
	int result = ft_isascii(c);
	printf("Result: %i\n", result);
	return (0);
}
*/