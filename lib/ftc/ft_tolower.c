/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:46:44 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/21 16:18:18 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

/**
 * @brief		Converts char to lowercase
 * 
 * @param c		Char to set
 * @return		Lowercased char
*/
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

/* int main(void)
{
	int c = 'H';
	
	printf("Lowercase: %c\n", ft_tolower(c));
	return (0);
} */