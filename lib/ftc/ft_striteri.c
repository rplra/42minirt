/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:53:56 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/21 17:12:34 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

/* Dummy fx tester
void	sft_toupper(unsigned int i, char *c)
{
	(void)i;
	if (*c >= 'a' && *c <= 'z')
		*c = *c - 32;
} */

/**
 * @brief		Applies a function to each char in string
 * 
 * @param s		String to iterate
 * @param f		Function to apply
 * @return		None
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;
	size_t	slen;

	if (s == NULL)
		return ;
	slen = 0;
	while (s[slen])
		slen++;
	i = 0;
	while (i < slen)
	{
		f(i, &s[i]);
		i++;
	}
}

/* int	main(void)
{
	char s[] = "Expacto Patronum!";
    
    ft_striteri(s, sft_toupper);

    printf("Result: %s\n", s);
    return (0);
} */

/*
LOGIC : 
	1. Declare variables
		- i  to iterate
		- slen for string length
	2. Checks if string / function is null
	3. Calculate strlen
	4. Loop while i < slen
		- call function
		- iterate (increment) index of string
*/

/*
MAIN function :
	1. declare char s[] as an array for it to be mutable (modifiable)
		- WHY?
		- char * will only point to string literal
		(immutable string / unmodifiable)
*/