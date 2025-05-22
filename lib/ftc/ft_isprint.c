/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 08:26:55 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/21 12:40:20 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

/**
 * @brief		Checks if char is a printable
 * 
 * @param c		Char to check
 * @return		True (1) / False (0)
*/
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

/*
int main(void)
{
	int c1 = 'A';
	int c2 = '\0';

	int result1 = ft_isprint(c1);
	printf("Result: %i\n", result1);

	int result2 = ft_isprint(c2);
	printf("Result: %i\n", result2);
	return (0);

}
*/