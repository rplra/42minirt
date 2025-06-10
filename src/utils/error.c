/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:30:15 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/09 15:18:57 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	print_error(t_parse *scene, char *msg, int param, char **params)
{
	ft_putstr_fd(RED "Error: ", 2);
	ft_putstr_fd(msg, 2);
	if (scene && scene->line_num)
	{
		ft_putstr_fd(" [line: ", 2);
		ft_putnbr_fd(scene->line_num, 2);
		if (param >= 0)
		{
			ft_putstr_fd(", param: ", 2);
			ft_putnbr_fd(param + 1, 2);
		}
		ft_putstr_fd("]", 2);
	}
	ft_putendl_fd(RESET "", 2);
	free_array(params);
	return (1);
}

void	exit_with_error(char *msg)
{
	ft_putstr_fd(RED, 2);
	ft_putendl_fd(msg, 2);
	ft_putstr_fd(RESET, 2);
	exit(EXIT_FAILURE);
}

void	perror_exit(char *perrmsg)
{
	perror(perrmsg);
	exit(EXIT_FAILURE);
}