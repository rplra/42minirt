/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:09:38 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/06 15:17:40 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int main(int ac, char **av)
{
	t_rt	rt;

	if (ac != 2)
		exit_with_error(ERROR_ARGFORMAT);
	
	// parsing
	ft_memset(&rt, 0, sizeof(rt));
	if (open_file(av[1], &rt))
		cleanup_and_exit(&rt);
	/*debug*/printf("Main: Parsed file\n");

	// init render
	initialize_mlx(&rt);
	/*debug*/printf("Main: Init mlx\n");

	// init vars to render_image
	init_variable(&rt);
	/*debug*/printf("Main: Init variables\n");

	// render
	my_render_img(&rt);
	/*debug*/printf("Main: Render image\n");
	printf(">> use tabs to select cam/light/obj, then → translate/rotate/scale keys to transform\n");
	mlx_put_image_to_window(rt.mlx, rt.mlx_win,
rt.img_intro.img, (WIN_WIDTH / 2) - (INTRO_W / 2), WIN_HEIGHT / 2);
	
	// event hooks
	mlx_hook(rt.mlx_win, ON_KEYDOWN, 1L << 0, key_press, &rt);
	mlx_hook(rt.mlx_win, 17, 0, close_window_x, &rt);
	mlx_key_hook(rt.mlx_win, close_window, &rt);

	// render loop
	mlx_loop(rt.mlx);
	// mlx_loop_hook(rt.mlx, animate_loading, &rt);
	
	// cleanup
	cleanup(&rt);	//might not need to free when translation & rotation
	//free_malloc(&rt, 1);
	return (0);
}

