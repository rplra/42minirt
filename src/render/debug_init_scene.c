/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_init_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:56:24 by hsim              #+#    #+#             */
/*   Updated: 2025/07/11 18:58:21 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    init_sph_scene(t_rt *rt)
{
	rt->obj_count = 4; // + other_obj_count
	malloc_obj_ptr(&rt->obj, rt->obj_count);

// 	float r = cos(M_PI / 4);
// 	vars->sph[0] = new_sphere(new_vector3d(-r, 0, -1), r, \
// new_vector3d(0, 0, 1), DIFFUSE); //left
// 	vars->sph[1] = new_sphere(new_vector3d(r, 0, -1), r, \
// new_vector3d(1, 0, 0), DIFFUSE); //right

	rt->obj[0] = new_sphere(new_vec3(0, 0, -1.2), 0.5, \
new_vec3(0.1, 0.2, 0.5), DIFFUSE);	//center
	rt->obj[1] = new_sphere(new_vec3(0, -100.5, -1), 100, \
new_vec3(0.8, 0.8, 0), DIFFUSE);	//ground
	rt->obj[2] = new_sphere(new_vec3(-1, 0, -1), 0.5, \
new_vec3(0.8, 0.8, 0.8), METAL);	//left
	rt->obj[3] = new_sphere(new_vec3(1, 0, -1), 0.5, \
new_vec3(0.8, 0.6, 0.2), METAL);	//right

	// vars->obj[4] = new_sphere(new_vec3(-0.5, 2, -2), 0.6, \
// new_vec3(0.4, 0.4, 0.4), METAL);	//left
// 	vars->obj[5] = new_sphere(new_vec3(5, 0, -1), 1, \
// new_vec3(0.8, 0.6, 0.2), METAL);	//right
}

void    init_plane_scene(t_rt *rt)
{
    rt->obj_count = 5;
	malloc_obj_ptr(&rt->obj, rt->obj_count);

    t_material  left_red = new_material(new_vec3(1, 0.2, 0.2), DIFFUSE);
    t_material  back_green = new_material(new_vec3(0.2, 1, 0.2), DIFFUSE);
    t_material  right_blue = new_material(new_vec3(0.2, 0.2, 1), DIFFUSE);
    t_material  up_orange = new_material(new_vec3(1, 0.5, 0), DIFFUSE);
    t_material  down_teal = new_material(new_vec3(0.2, 0.8, 0.8), DIFFUSE);

    rt->obj[0] = new_plane(new_vec3(-3,-2,5), new_vec3(0,0,-4), new_vec3(0,4,0), left_red);
    rt->obj[1] = new_plane(new_vec3(-2,-2,0), new_vec3(4,0,0), new_vec3(0,4,0), back_green);
    rt->obj[2] = new_plane(new_vec3(3,-2,1), new_vec3(0,0,4), new_vec3(0,4,0), right_blue);
    rt->obj[3] = new_plane(new_vec3(-2,3,1), new_vec3(4,0,0), new_vec3(0,0,4), up_orange);
    rt->obj[4] = new_plane(new_vec3(-2,-3,5), new_vec3(4,0,0), new_vec3(0,0,-4), down_teal);
}
