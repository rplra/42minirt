/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:23:04 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/21 13:02:51 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

/**
 * @brief		Checks if char is an alphabet
 * 
 * @param c		Char to check
 * @return		True (1) / False (0)
*/
int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

/*
int main(void)
{
	int c = 'A';
	
	int result = ft_isalpha(c);
	printf("Result: %i\n", result);
	return (0);
}
*/