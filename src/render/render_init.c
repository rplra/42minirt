/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:05:22 by hsim              #+#    #+#             */
/*   Updated: 2025/07/09 20:36:12 by hsim             ###   ########.fr       */
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

// void	init_bbox(t_interval bbox[3])
// {
// 	aabb(new_vec3(0, 0, 0), new_vec3(0, 0, 0), bbox);
// }

void	init_obj(t_rt *vars)
{
	/* init sphere objects, use malloc */
	vars->obj_count = 4; // + other_obj_count
	malloc_obj_ptr(&vars->obj, vars->obj_count);

// 	float r = cos(M_PI / 4);
// 	vars->sph[0] = new_sphere(new_vector3d(-r, 0, -1), r, \
// new_vector3d(0, 0, 1), DIFFUSE); //left
// 	vars->sph[1] = new_sphere(new_vector3d(r, 0, -1), r, \
// new_vector3d(1, 0, 0), DIFFUSE); //right

	vars->obj[0] = new_sphere(new_vec3(0, 0, -1.2), 0.5, \
new_vec3(0.1, 0.2, 0.5), DIFFUSE);	//center
	vars->obj[1] = new_sphere(new_vec3(0, -100.5, -1), 100, \
new_vec3(0.8, 0.8, 0), DIFFUSE);	//ground
	vars->obj[2] = new_sphere(new_vec3(-1, 0, -1), 0.5, \
new_vec3(0.8, 0.8, 0.8), METAL);	//left
	vars->obj[3] = new_sphere(new_vec3(1, 0, -1), 0.5, \
new_vec3(0.8, 0.6, 0.2), METAL);	//right

	// vars->obj[4] = new_sphere(new_vec3(-0.5, 2, -2), 0.6, \
// new_vec3(0.4, 0.4, 0.4), METAL);	//left
// 	vars->obj[5] = new_sphere(new_vec3(5, 0, -1), 1, \
// new_vec3(0.8, 0.6, 0.2), METAL);	//right

	get_bbox_val(vars->obj, vars->obj_count, vars->bbox);
}

void	init_cam(t_rt *vars)
{
	vars->cam.orig = new_vec3(0, 0, 0); 			//-2,2,1
	vars->cam.lookat = new_vec3(0, 0, -1);
	vars->cam.vup = new_vec3(0, 1, 0);				//orientation
	vars->cam.vfov = radian(90);					//fov
	vars->cam.defoc_ang = radian(0);				//blur intensity
	vars->cam.defoc_disk[X] = new_vec3(0, 0, 0);	//lens max_width in vec3
	vars->cam.defoc_disk[Y] = new_vec3(0, 0, 0);	//lens max_height in vec3
	vars->cam.focus_dist = len_vec3(subtract_vec(vars->cam.orig, vars->cam.lookat));	//obj within this distance = sharp
	/*debug*/printf("focus_dist:%f\n", vars->cam.focus_dist);

	vars->cam.ray_bounce = 5;
	vars->cam.sample_per_pixel = 5;

	vars->ray.orig = vars->cam.orig;				//helper pointer for ray
	vars->ray.vector = new_vec3(0, 0, 0);
}

void	init_rec(t_rt *vars)
{
	vars->hit.surf_norm = new_vec3(0, 0, 0);
	vars->hit.t = 0;
	vars->hit.index = -1;
}

void	init_variable(t_rt *vars)
{
	init_cam(vars);
	init_obj(vars);		//replace with info from parser
	init_bvh_node(vars);
	init_rec(vars);
	vars->color_bg[0] = new_vec3(0.5, 0.7, 1);
	vars->color_bg[1] = new_vec3(1, 1, 1);

	vars->seed = 12345;
	my_create_image(vars, &vars->img);
}
