/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-hl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:07:37 by hsim              #+#    #+#             */
/*   Updated: 2025/08/16 23:31:48 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(void)
{
	t_rt	vars;

	init_mlx(&vars);
	init_rt(&vars);

	/* _____________ rendering _____________ */
	render(&vars);

	/* _____________ keymaps _____________ */
	mlx_hook(vars.mlx_win, ON_KEYDOWN, 1L << 0, key_press, &vars);
	mlx_hook(vars.mlx_win, 17, 0, close_window_x, &vars);
	mlx_key_hook(vars.mlx_win, close_window, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
