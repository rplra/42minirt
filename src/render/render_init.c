/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:05:22 by hsim              #+#    #+#             */
/*   Updated: 2025/07/07 13:25:53 by rraja-az         ###   ########.fr       */
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

//void	init_obj(t_rt *vars, t_scene *scene)
//{
// 	vars->obj = NULL;
// 	new_obj(vars, &vars->obj, new_sph(new_vec3(0, 0, -1.2), 0.5, \
// new_vec3(0.1, 0.2, 0.5), DIFFUSE)); //center
// 	new_obj(vars, &vars->obj, new_sph(new_vec3(0, -100.5, -1), 100, \
// new_vec3(0.8, 0.8, 0), DIFFUSE)); //ground
// 	new_obj(vars, &vars->obj, new_sph(new_vec3(-1, 0, -1), 0.5, \
// new_vec3(0.8, 0.8, 0.8), METAL)); //left
// 	new_obj(vars, &vars->obj, new_sph(new_vec3(1, 0, -1), 0.5, \
// new_vec3(0.8, 0.6, 0.2), METAL)); //right

	/* init sphere objects, use malloc */
	// vars->count_sph = 4;
	// malloc_sph_ptr(&vars->sph, vars->count_sph);

// 	float r = cos(M_PI / 4);
// 	vars->sph[0] = new_sphere(new_vector3d(-r, 0, -1), r, \
// new_vector3d(0, 0, 1), DIFFUSE); //left
// 	vars->sph[1] = new_sphere(new_vector3d(r, 0, -1), r, \
// new_vector3d(1, 0, 0), DIFFUSE); //right

// 	vars->sph[0] = new_sphere(new_vec3(0, 0, -1.2), 0.5, \
// new_vec3(0.1, 0.2, 0.5), DIFFUSE); //center
// 	vars->sph[1] = new_sphere(new_vec3(0, -100.5, -1), 100, \
// new_vec3(0.8, 0.8, 0), DIFFUSE); //ground
// 	vars->sph[2] = new_sphere(new_vec3(-1, 0, -1), 0.5, \
// new_vec3(0.8, 0.8, 0.8), METAL); //left
// 	vars->sph[3] = new_sphere(new_vec3(1, 0, -1), 0.5, \
// new_vec3(0.8, 0.6, 0.2), METAL); //right
//}

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

void	init_bbox(t_rt *vars)
{
	aabb(new_vec3(0, 0, 0), new_vec3(0, 0, 0), vars->bbox);
}

void	init_variable(t_rt *vars)
{
	init_cam(vars);
	init_bbox(vars);
	vars->color_bg[0] = new_vec3(0.5, 0.7, 1);
	vars->color_bg[1] = new_vec3(1, 1, 1);
	// vars->color_bg[0] = new_vector3d(0, 178, 255);
	// vars->color_bg[1] = new_vector3d(0, 255, 255);
	// vars->color_bg[1] = create_hsv(225, 62, 40);
	// vars->color_bg[1] = create_hsv(166, 38, 100);

	// vars->color_bg[0] = create_hsv(199, 100, 100);
	// vars->color_bg[1] = create_hsv(166, 10, 90);

	vars->hit.surf_norm = new_vec3(0, 0, 0);
	vars->hit.t = 0;
	//init_obj(vars);
	my_create_image(vars, &vars->img);
}
