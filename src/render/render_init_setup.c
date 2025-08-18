/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init_setup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 10:06:53 by hsim              #+#    #+#             */
/*   Updated: 2025/08/18 14:22:36 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_bg_color(t_rt *rt, float intensity)
{
	if (intensity <= 0)
		intensity = 0.05;
	rt->color_bg[0] = mult_vec_scalar(new_vec3(0.4, 0.6, 1), intensity);
	rt->color_bg[1] = mult_vec_scalar(rt->ambient.colour, intensity);
}

/* w is a vector pointing opposite lookat */
void	set_cam_vup(t_rt *rt)
{
	t_vec3	w;

	w = mult_vec_scalar(rt->camera.lookat, -1);
	if (fabs(scalar_product(w, rt->camera.vup)) > 0.9999)
		rt->camera.vup = cross_product(new_vec3(1, 0, 0), rt->camera.lookat);
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
	/* ********* need to comment out above when include parser ********** */
	rt->camera.transform.rotate = new_vec3(0, 0, 0);
	rt->camera.transform.translate = new_vec3(0, 0, 0);
	rt->camera.ori = new_vec3(rt->camera.pos.x, rt->camera.pos.y,
			rt->camera.pos.z);
	// rt->camera.lookat = add_vec(rt->camera.pos, new_vec3(0, 0, -1));
	// /*debug*/debug_print_vec("lookat", rt->camera.lookat);
	set_cam_vup(rt);
	// /*debug*/debug_print_vec("cam_vup", rt->camera.vup);
	rt->camera.defoc_ang = DEFOC_ANG;
	rt->camera.defoc_disk[X] = new_vec3(DEFOC_XX, DEFOC_XY, DEFOC_XZ);
	rt->camera.defoc_disk[Y] = new_vec3(DEFOC_YX, DEFOC_YY, DEFOC_YZ);
	// rt->camera.focus_dist = len_vec3(subtract_vec(rt->camera.pos, 
	//		rt->camera.lookat));
	rt->camera.focus_dist = 1;
	// /*debug*/printf("focus_dist:%f\n", rt->camera.focus_dist);
	set_render_quality(rt);
	rt->ray.orig = rt->camera.pos;
	rt->ray.vector = new_vec3(0, 0, 0);
}

void	init_light(t_rt *rt)
{
	t_obj	light;

	light.type = SPHERE;
	light.sph.pos = rt->light.pos;
	light.sph.rad = LIGHT_RADIUS;
	light.material.albedo = mult_vec_scalar(rt->light.colour,
			rt->light.brightness * 6);
	light.material.type = LIGHT;
	assign_rotation(&light);
	assign_bbox(&light);
	light.id = rt->obj_count;
	add_object(rt, &light);
}
