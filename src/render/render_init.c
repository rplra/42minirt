/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:05:22 by hsim              #+#    #+#             */
/*   Updated: 2025/07/19 11:30:12 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * initialize mlx windows for image rendering
 * mlx_init uses malloc
 */
void	initialize_mlx(t_rt *rt)
{
	rt->mlx = mlx_init();
	if (rt->mlx == NULL)
	{
		free(rt->mlx);
		exit (1);
	}
	rt->mlx_win = mlx_new_window(rt->mlx, WIN_WIDTH, WIN_HEIGHT, \
"miniRT");
}

void	init_obj(t_rt *rt)
{
	// init_sph_scene(rt);
	init_plane_scene(rt);
}

void	init_cam(t_rt *rt)
{
	// rt->camera.pos = new_vec3(0, 0, 9); //-2,2,1
	// rt->camera.lookat = new_vec3(0, 0, 0);
	/* ************** need to comment out above when include parser ************************ */

	rt->camera.vfov = radian(rt->camera.vfov);
	rt->camera.vup = new_vec3(0, 1, 0);
	rt->camera.lookat = add_vec(rt->camera.pos, new_vec3(0, 0, -1)); // fixed
	rt->camera.defoc_ang = DEFOC_ANG;
	rt->camera.defoc_disk[X] = new_vec3(DEFOC_XX, DEFOC_XY, DEFOC_XZ);
	rt->camera.defoc_disk[Y] = new_vec3(DEFOC_YX, DEFOC_YY, DEFOC_YZ);
	rt->camera.focus_dist = len_vec3(subtract_vec(rt->camera.pos, rt->camera.lookat));
	/*debug*/printf("focus_dist:%f\n", rt->camera.focus_dist);
	rt->camera.ray_bounce = SAMPLE_RAY_BOUNCE;
	rt->camera.sample_per_pixel = SAMPLE_PER_PIXEL;
	rt->ray.orig = rt->camera.pos; //be careful with this one, maybe copy safer?
	rt->ray.vector = new_vec3(0, 0, 0);
}

void	init_hit(t_rt *rt)
{
	rt->hit.surf_norm = new_vec3(0, 0, 0);
	rt->hit.t = 0;
	rt->hit.index = -1;
}

/* reassign material to other types than default */
void	edit_material(t_rt *rt)
{
	update_material(&rt->obj[4], DIFFUSE, 0);
}

void	init_variable(t_rt *rt)
{
	init_cam(rt);
	// init_obj(rt);			//replace with info from parser
	// edit_material(rt);		//custom assign material
	debug_print_arr("init_var", rt->obj, rt->obj_count);
	init_bvh_node(rt);
	init_hit(rt);
	rt->color_bg[0] = new_vec3(0.5, 0.7, 1);
	rt->color_bg[1] = new_vec3(1, 1, 1);
	rt->seed = 12345;
	my_create_image(rt, &rt->img);
}
