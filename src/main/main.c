/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:09:38 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/02 15:46:35 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	test_file_functions(const char *filepath);

int main(int ac, char **av)
{
	char	*filepath;
	
	if (ac != 2)
		exit_with_error(ERROR_ARGFORMAT);
	filepath = av[1];
	// if (open file) > init > run mlx
	// clean
	return (0);
}

