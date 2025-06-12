/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:09:38 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/11 17:24:00 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int main(int ac, char **av)
{
	t_scene scene;
	
	ft_memset(&scene, 0, sizeof(scene));
	if (ac != 2)
		exit_with_error(ERROR_ARGFORMAT);
	open_file(av[1], &scene);
	// open file to check for error > free scene > return 1
	// render
	free_scene(&scene);
	return (0);
}

