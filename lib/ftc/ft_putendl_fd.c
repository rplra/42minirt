/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:05:14 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/20 16:31:30 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <string.h>
//#include <unistd.h>
#include "libft.h"

/**
 * @brief		Outputs the string 's' to the given file descriptor
 * 				followed by a newline
 * 
 * @param s		String to write
 * @param fd	File descriptor on which to write
 * @return		None
*/
void	ft_putendl_fd(char *s, int fd)
{
	if (s != NULL)
	{
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
	}
	return ;
}

/*
int	main(void)
{
	ft_putendl_fd("Hello!", 1);
	return (0);
}
*/

/*
LOGIC :
1. ALWAYS CHECK FOR NULL
2. Get strlen to determine how many bytes
3. Use write
4. Add another write to specifically write newline
** no need '&' because c is a pointer (address by itself)
*/
