/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:05:22 by hsim              #+#    #+#             */
/*   Updated: 2025/08/01 13:05:05 by hsim             ###   ########.fr       */
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
	rt->mlx_win = mlx_new_window(rt->mlx, WIN_WIDTH + PANEL_WIDTH, WIN_HEIGHT, \
"miniRT");
}

//debug
void	init_obj(t_rt *rt)
{
	// init_sph_scene(rt);
	init_plane_scene(rt);
	// init_cyl_scene(rt);
}

void	init_cam(t_rt *rt)
{
	
	// rt->camera.pos = new_vec3(0, 0, 9); //not parser
	// rt->camera.pos = new_vec3(-2, 0, 11); //not parser
	// rt->camera.vfov = radian(90);	//not parser
	/* ************** need to comment out above when include parser ************************ */

	rt->camera.transform.rotate = new_vec3(0, 0, 0);
	rt->camera.transform.translate = new_vec3(0, 0, 0);
	rt->camera.ori = new_vec3(rt->camera.pos.x, rt->camera.pos.y, rt->camera.pos.z);
	rt->camera.lookat = add_vec(rt->camera.pos, new_vec3(0, 0, -1));
	rt->camera.vup = new_vec3(0, 1, 0);
	rt->camera.defoc_ang = DEFOC_ANG;
	rt->camera.defoc_disk[X] = new_vec3(DEFOC_XX, DEFOC_XY, DEFOC_XZ);
	rt->camera.defoc_disk[Y] = new_vec3(DEFOC_YX, DEFOC_YY, DEFOC_YZ);
	rt->camera.focus_dist = len_vec3(subtract_vec(rt->camera.pos, rt->camera.lookat));
	// /*debug*/printf("focus_dist:%f\n", rt->camera.focus_dist);

	rt->camera.ray_bounce = 5;
	rt->camera.sample_per_pixel = 5;

	rt->ray.orig = rt->camera.pos;
	rt->ray.vector = new_vec3(0, 0, 0);
}

void	init_hit(t_rt *rt)
{
	rt->hit.surf_norm = new_vec3(0, 0, 0);
	// rt->hit.t = 2147483648;
	rt->hit.t = 0;
	rt->hit.index = -1;
	rt->hit.setting = -1;
}

/* reassign material to other types than default */
void	edit_mat(t_rt *rt)
{
	update_material(&rt->obj[0], METAL, 0);
	update_material(&rt->obj[1], DIFFUSE, 0);
	update_material(&rt->obj[2], METAL, 0);
}

void	init_variable(t_rt *rt)
{
	
	rt->preview_mode = 1;
	init_cam(rt);
	// edit_material(rt);		//custom assign material

	/* ************** need to comment out below when include parser ************************ */
	// init_obj(rt);				//not parser
	/* ************** need to comment out above when include parser ************************ */

	// /*debug*/debug_print_arr("init_var", rt->obj, rt->obj_count);
	init_bvh_node(rt);
	// /*debug*/debug_print_arr("init_bvh", rt->obj, rt->obj_count);
	init_hit(rt);
	rt->sel.type = SEL_CAMERA;
	rt->sel.obj_index = 0;
	rt->color_bg[0] = new_vec3(0.5, 0.7, 1);
	rt->color_bg[1] = new_vec3(1, 1, 1);
	rt->seed = 12345;
	my_create_image(rt, &rt->img);
}
