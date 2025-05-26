/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:30:15 by rraja-az          #+#    #+#             */
/*   Updated: 2025/05/26 18:25:53 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	print_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (1);
}

void	exit_with_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void	perror_exit(char *perrmsg)
{
	perror(perrmsg);
	exit(EXIT_FAILURE);
}