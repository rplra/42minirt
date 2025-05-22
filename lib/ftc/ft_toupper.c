/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:34:56 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/20 19:53:56 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

/**
 * @brief		Converts char to uppercase
 * 
 * @param c		Char to set
 * @return		Uppercased char
*/
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

/* int main(void)
{
	int c = 'h';
	
	printf("Uppercase: %c\n", ft_toupper(c));
	return (0);
} */