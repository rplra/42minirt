/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:02:00 by hsim              #+#    #+#             */
/*   Updated: 2025/06/24 19:17:48 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* prints error message, no \n needed*/
int	ft_perror(char *err_str, char *err_str2, int return_value)
{
	if (err_str && err_str[0])
		ft_putstr_fd(err_str, 2);
	if (err_str2 && err_str2[0])
		ft_putstr_fd(err_str2, 2);
	ft_putchar_fd('\n', 2);
	return (return_value);
}
