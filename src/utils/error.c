/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:30:15 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/13 11:29:16 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	print_error(t_parse *file, char *msg, int param_idx, char **params)
{
	if (msg)
	{
		ft_putstr_fd(RED "Error: ", 2);
		ft_putstr_fd(msg, 2);
	}
	if (file && file->line_num)
	{
		ft_putstr_fd(" [line: ", 2);
		ft_putnbr_fd(file->line_num, 2);
		if (param_idx >= 0)
		{
			ft_putstr_fd(", param: ", 2);
			ft_putnbr_fd(param_idx + 1, 2);
		}
		ft_putstr_fd("]", 2);
	}
	ft_putendl_fd(RESET "", 2);
	if (params && (!file || params != file->tokens))
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