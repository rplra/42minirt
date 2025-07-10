/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:05:22 by hsim              #+#    #+#             */
/*   Updated: 2025/07/10 08:30:26 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * initialize mlx windows for image rendering
 * mlx_init uses malloc
 */
void	initialize_mlx(t_rt *vars)
{
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
	{
		free(vars->mlx);
		exit (1);
	}
	vars->mlx_win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, \
"miniRT");
}

// void	init_obj(t_rt *vars)
// {
// 	/* init sphere objects, use malloc */
// 	vars->obj_count = 4; // + other_obj_count
// 	malloc_obj_ptr(&vars->obj, vars->obj_count);

// // 	float r = cos(M_PI / 4);
// // 	vars->sph[0] = new_sphere(new_vector3d(-r, 0, -1), r, \
// // new_vector3d(0, 0, 1), DIFFUSE); //left
// // 	vars->sph[1] = new_sphere(new_vector3d(r, 0, -1), r, \
// // new_vector3d(1, 0, 0), DIFFUSE); //right

// 	vars->obj[0] = new_sphere(new_vec3(0, 0, -1.2), 0.5, \
// new_vec3(0.1, 0.2, 0.5), DIFFUSE);	//center
// 	vars->obj[1] = new_sphere(new_vec3(0, -100.5, -1), 100, \
// new_vec3(0.8, 0.8, 0), DIFFUSE);	//ground
// 	vars->obj[2] = new_sphere(new_vec3(-1, 0, -1), 0.5, \
// new_vec3(0.8, 0.8, 0.8), METAL);	//left
// 	vars->obj[3] = new_sphere(new_vec3(1, 0, -1), 0.5, \
// new_vec3(0.8, 0.6, 0.2), METAL);	//right

// 	// vars->obj[4] = new_sphere(new_vec3(-0.5, 2, -2), 0.6, \
// // new_vec3(0.4, 0.4, 0.4), METAL);	//left
// // 	vars->obj[5] = new_sphere(new_vec3(5, 0, -1), 1, \
// // new_vec3(0.8, 0.6, 0.2), METAL);	//right

// 	get_bbox_val(vars->obj, vars->obj_count, vars->bbox);
// }

void	init_cam(t_rt *vars)
{
	// vars->cam.orig = new_vec3(0, 0, 0); //-2,2,1
	// vars->cam.lookat = new_vec3(0, 0, -1);
	vars->camera.vup = new_vec3(0, 1, 0);
	vars->camera.lookat = add_vec(vars->camera.pos, new_vec3(0, 0, -1)); // fixed
	//vars->cam.vfov = radian(90);
	vars->camera.vfov = radian(vars->camera.vfov);
	vars->camera.defoc_ang = radian(0);
	vars->camera.defoc_disk[X] = new_vec3(0, 0, 0);
	vars->camera.defoc_disk[Y] = new_vec3(0, 0, 0);
	vars->camera.focus_dist = len_vec3(subtract_vec(vars->camera.pos, vars->camera.lookat));
	/*debug*/printf("focus_dist:%f\n", vars->camera.focus_dist);

	vars->camera.ray_bounce = 5;
	vars->camera.sample_per_pixel = 5;

	vars->ray.orig = vars->camera.pos; //be careful with this one, maybe copy safer?
	vars->ray.vector = new_vec3(0, 0, 0);
}

void	init_hit(t_rt *vars)
{
	vars->hit.surf_norm = new_vec3(0, 0, 0);
	vars->hit.t = 0;
	vars->hit.index = -1;
}

void	init_variable(t_rt *vars)
{
	init_cam(vars);
	// init_obj(vars);		//replace with info from parser
	debug_print_arr("init_var", vars->obj, vars->obj_count);
	init_bvh_node(vars);
	init_hit(vars);
	vars->color_bg[0] = new_vec3(0.5, 0.7, 1);
	vars->color_bg[1] = new_vec3(1, 1, 1);
	vars->seed = 12345;

	my_create_image(vars, &vars->img);
}
