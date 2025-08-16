/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:05:22 by hsim              #+#    #+#             */
/*   Updated: 2025/08/16 23:44:04 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// //debug
// void	init_obj(t_rt *rt)
// {
// 	// init_sph_scene(rt);
// 	init_plane_scene(rt);
// 	// init_cyl_scene(rt);
// }

void	set_render_quality(t_rt *rt)
{
	if (rt->b_preview_mode)
	{
		rt->camera.ray_bounce = SAMPLE_PREVIEW;
		rt->camera.sample_per_pixel = SAMPLE_PREVIEW;
	}
	else
	{
		rt->camera.ray_bounce = SAMPLE_RAY_BOUNCE;
		rt->camera.sample_per_pixel = SAMPLE_PER_PIXEL;
		printf(">> Rendering image...\n");
	}
}

/* w is a vector pointing opposite lookat */
void	set_cam_vup(t_rt *rt)
{
	t_vec3	w;

	w = mult_vec_scalar(rt->camera.lookat, -1);
	if (fabs(scalar_product(w, rt->camera.vup)) > 0.9999)
		rt->camera.vup = cross_product(new_vec3(1,0,0), rt->camera.lookat);
	else
		rt->camera.vup = new_vec3(0, 1, 0);
	rt->camera.vup_ori = rt->camera.vup;
	// /*debug*/debug_print_vec("cam_vup", rt->camera.vup);
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
	// rt->camera.lookat = add_vec(rt->camera.pos, new_vec3(0, 0, -1));
	// /*debug*/debug_print_vec("lookat", rt->camera.lookat);

	set_cam_vup(rt);
	// /*debug*/debug_print_vec("cam_vup", rt->camera.vup);
	rt->camera.defoc_ang = DEFOC_ANG;
	rt->camera.defoc_disk[X] = new_vec3(DEFOC_XX, DEFOC_XY, DEFOC_XZ);
	rt->camera.defoc_disk[Y] = new_vec3(DEFOC_YX, DEFOC_YY, DEFOC_YZ);
	// rt->camera.focus_dist = len_vec3(subtract_vec(rt->camera.pos, rt->camera.lookat));
	rt->camera.focus_dist = 1;
	// /*debug*/printf("focus_dist:%f\n", rt->camera.focus_dist);
	set_render_quality(rt);
	rt->ray.orig = rt->camera.pos;
	rt->ray.vector = new_vec3(0, 0, 0);
}

void	init_hit(t_rt *rt)
{
	rt->hit.surf_norm = new_vec3(0, 0, 0);
	rt->hit.t = 0;
	rt->hit.index = -1;
	rt->hit.setting = 1;
}

/* reassign material to other types than default */
void	assign_custom_material(t_rt *rt)
{
	int	x;

	x = 0;
	while (x + 1 < (int)rt->obj_count)
	{
		if (x % 2 == 0)
			update_material(&rt->obj[x], DIFFUSE, 0);
		else
			update_material(&rt->obj[x], METAL, 0);
		x++;
	}
}

void	init_light(t_rt *rt)
{
	t_obj	light;

	light.type = SPHERE;
	light.sph.pos = rt->light.pos;
	light.sph.rad = 0.5;
	light.material.albedo = mult_vec_scalar(rt->light.colour, rt->light.brightness * 6);
	light.material.type = LIGHT;
	assign_rotation(&light);
	assign_bbox(&light);
	light.id = rt->obj_count;
	add_object(rt, &light);
}

void	init_bg_color(t_rt *rt, float intensity)
{
	if (intensity <= 0)
		intensity = 0.05;
	rt->color_bg[0] = mult_vec_scalar(new_vec3(0.4, 0.6, 1), intensity);
	rt->color_bg[1] = mult_vec_scalar(rt->ambient.colour, intensity);
}

void	init_rt(t_rt *rt)
{
	int	dimension[2];

	rt->b_preview_mode = 1;
	rt->b_show_light = 1;
	rt->b_animate = 0;
	rt->b_style = 0;

	rt->sel.type = SEL_CAMERA;
	rt->sel.obj_index = 0;
	rt->seed = 12345;
	init_cam(rt);
	init_light(rt);
	// assign_custom_material(rt);
	/* ************** need to comment out below when include parser ************************ */
	// init_obj(rt);				//not parser
	/* ************** need to comment out above when include parser ************************ */
	init_bvh_node(rt);
	init_hit(rt);
	init_bg_color(rt, rt->ambient.intensity);
	ft_create_img(rt, &rt->img);
	assign_int(dimension, PANEL_WIDTH, WIN_HEIGHT);
	load_menu(rt, &rt->img_menu, MENU, dimension);
	assign_int(dimension, LOADBAR_W, WIN_HEIGHT);
	load_menu(rt, &rt->img_load, LOADBAR, dimension);
	load_menu(rt, &rt->img_intro, INTRO, dimension);
	load_menu_label_info(rt);
}
