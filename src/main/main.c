/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:09:38 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/02 16:50:01 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Convert parsed scene to render format
/* static void	convert_scene_to_render(t_scene *scene, t_rt *rt)
{
	convert_camera(scene, rt);
	convert_objects(scene, rt);
	convert_ambient(scene, rt);
	
	// Initialize render variables
	rt->ray.orig = rt->cam.orig;
	rt->ray.vector = new_vec3(0, 0, 0);
	rt->rec.surf_norm = new_vec3(0, 0, 0);
	rt->rec.t = 0;
} */

int main(int ac, char **av)
{
	t_scene scene;
	t_rt	rt;

	
	if (ac != 2)
		exit_with_error(ERROR_ARGFORMAT);
	
	// parsing
	ft_memset(&scene, 0, sizeof(scene));
	if (open_file(av[1], &scene))
		cleanup_and_exit(&scene);
	
	// init render?
	ft_memset(&rt, 0, sizeof(rt));
	initialize_mlx(&rt);
	init_variable(&rt);
	
	// render
	my_render_image(&rt);
	
	// event hooks
	mlx_key_hook(rt.mlx_win, key_close, &rt);
	mlx_hook(rt.mlx_win, 17, 0, key_close, &rt);
	
	// render loop
	mlx_loop(rt.mlx);
	
	// cleanup
	free_scene(&scene);
	free_malloc(&rt, 1);
	return (0);
}

