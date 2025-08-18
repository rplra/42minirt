/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:05:22 by hsim              #+#    #+#             */
/*   Updated: 2025/08/18 16:22:18 by rraja-az         ###   ########.fr       */
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

void	init_hit(t_rt *rt)
{
	rt->hit.surf_norm = new_vec3(0, 0, 0);
	rt->hit.t = 0;
	rt->hit.index = -1;
	rt->hit.body = 0;
	rt->hit.cap = 0;
	rt->hit.setting = 1;
}

/* ********* need to comment out above when include parser ********** */
/* reassign material to other types than default */
// void	assign_custom_material(t_rt *rt)
// {
// 	int	x;

// 	x = 0;
// 	while (x + 1 < (int)rt->obj_count)
// 	{
// 		if (x % 2 == 0)
// 			update_material(&rt->obj[x], DIFFUSE, 0);
// 		else
// 			update_material(&rt->obj[x], METAL, 0);
// 		x++;
// 	}
// }

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
		/* ********* need to comment out above when include parser ********** */
	// init_obj(rt);				//not parser
		/* ********* need to comment out above when include parser ********** */
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
