/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 08:24:17 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/21 13:38:05 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <fcntl.h>
// #include <unistd.h>
#include "libft.h"

/**
 * @brief		Writes a char to a file descriptor
 * 
 * @param c		Char to write
 * @param fd	File descriptor on which to write
 * @return		None
*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/* int	main(void)
{
	// Outputting to stdout
	ft_putchar_fd('A', 1); // Outputs 'A' to stdout
	ft_putchar_fd('\n', 1);
	return (0);
} */

/* int main(void)
{
	// Outputting to a File
	int fd = open("output.txt", 0_WRONLY | 0_CREAT, 0644);
	if (fd == -1)
		return (1);

	ft_putchar_fd('A', 1); // Writes 'B' to the file "output.txt"
	close(fd);
	return (0);
}

int main(void)
{
	// Output to stderr
	ft_putchar_fd('A', 2); // Prints 'A' to the terminal as an error message
	return (0);
} */

/*
LOGIC : 
Use 'write' system call to output char 'c' to the specified fd
*/

/*
**
SIMPLIFIED :
Simple utility that directs a char to a specified fd using 'write'
Particularly useful for outputting char to files, stdout, stderr streams

fd - file descriptor where the char will be written
Eg;	(0) Standard input / stdin
					(1) Standard output / stdout
					(2) Standard error / stderr

&c - a pointer to char c (address of c)
1 - no of bytes(since c is single char, we write 1 byte)
*/