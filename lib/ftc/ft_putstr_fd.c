/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 08:58:14 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/21 13:40:48 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>
//#include <string.h>
#include "libft.h"

/**
 * @brief		Writes the string 's' to the given file descriptor
 * 
 * @param s		String to write
 * @param fd	File descriptor on which to write
 * @return		None
*/
void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		write(fd, s, ft_strlen(s));
	return ;
}

/*
int	main(void)
{
	ft_putstr_fd("Hello!\n", 1);
	return (0);
}
*/

/*
LOGIC :
1. ALWAYS CHECK FOR NULL
2. Get strlen to determine how many bytes
3. Use write
** no need '&' because c is a pointer (address by itself)
*/
