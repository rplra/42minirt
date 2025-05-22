/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:19:48 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/21 13:39:50 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <string.h>
//#include <unistd.h>
#include "libft.h"

/** 
 * @brief 		Writes integer 'n' to the given file descriptor.
 *
 * @param n 	Integer to input 
 * @param fd 	File descriptor on which to write
 * @return 		None
*/
void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}

/* int main(void)
{
	ft_putnbr_fd(9881, 1);
	return (0);
} */

/*
LOGIC :
	1. Check for int min
	2. Check for negative
		- add sign
		- print nb with - sign
	3. Positive number
		- nb / 10 
		- n % 10 + '0' (convert to char) > write
	4. Remaining number (n < 10)
		- n + '0 (convert to char) > write
*/