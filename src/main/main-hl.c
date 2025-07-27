/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-hl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:07:37 by hsim              #+#    #+#             */
/*   Updated: 2025/07/22 13:03:26 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(void)
{
	t_rt	vars;

	initialize_mlx(&vars);
	init_variable(&vars);

	/* _____________ rendering _____________ */
	my_render_image(&vars);

	/* _____________ keymaps _____________ */
	mlx_hook(vars.mlx_win, ON_KEYDOWN, 1L << 0, key_press, &vars);
	mlx_hook(vars.mlx_win, 17, 0, close_window_x, &vars);
	mlx_key_hook(vars.mlx_win, close_window, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
