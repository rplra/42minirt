/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:09:38 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/17 12:53:54 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_rt	rt;

	if (ac != 2)
		exit_with_error(ERROR_ARGFORMAT);
	ft_memset(&rt, 0, sizeof(rt));
	if (open_file(av[1], &rt))
		cleanup_and_exit(&rt, 1);
	init_mlx(&rt);
	init_rt(&rt);
	render(&rt);
	event_loop(&rt);
	return (0);
}
