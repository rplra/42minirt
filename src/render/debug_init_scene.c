/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_init_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:56:24 by hsim              #+#    #+#             */
/*   Updated: 2025/07/27 20:36:12 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_sph_scene(t_rt *rt)
{
	rt->obj_count = 4;
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

void	init_plane_scene(t_rt *rt)
{
	rt->obj_count = 5;
	malloc_obj_ptr(&rt->obj, rt->obj_count);

	t_mat  left_red = new_material(new_vec3(1, 0.2, 0.2), DIFFUSE);
	t_mat  back_green = new_material(new_vec3(0.2, 1, 0.2), DIFFUSE);
	t_mat  right_blue = new_material(new_vec3(0.2, 0.2, 1), DIFFUSE);
	t_mat  up_orange = new_material(new_vec3(1, 0.5, 0), METAL);
	t_mat  down_teal = new_material(new_vec3(0.2, 0.8, 0.8), METAL);

	// rt->obj[0] = new_plane(new_vec3(-3,-2,5), new_vec3(0,0,-4), new_vec3(0,4,0), left_red);
	// rt->obj[2] = new_plane(new_vec3(3,-2,1), new_vec3(0,0,4), new_vec3(0,4,0), right_blue);
	// rt->obj[1] = new_plane(new_vec3(-2,-2,0), new_vec3(4,0,0), new_vec3(0,4,0), back_green);
	// rt->obj[3] = new_plane(new_vec3(-2,3,1), new_vec3(4,0,0), new_vec3(0,0,4), up_orange);
	// rt->obj[4] = new_plane(new_vec3(-2,-3,5), new_vec3(4,0,0), new_vec3(0,0,-4), down_teal);

	rt->obj[0] = new_plane(new_vec3(-3,2,1), new_vec3(1,0,0), left_red);
	// rt->obj[0] = new_plane(new_vec3(-3,-2,5), new_vec3(1,0,0), left_red);
	rt->obj[1] = new_plane(new_vec3(-2,-2,0), new_vec3(0,0,1), back_green);
	rt->obj[2] = new_plane(new_vec3(-2,3,1), new_vec3(0,-1,0), up_orange);
	rt->obj[3] = new_plane(new_vec3(-2,-3,5), new_vec3(0,1,0), down_teal);
	rt->obj[4] = new_plane(new_vec3(3,-2,1), new_vec3(-1,0,0), right_blue);

	// rt->obj[0] = new_plane(new_vec3(-3,0,3), new_vec3(1,0,0), left_red);
	// rt->obj[1] = new_plane(new_vec3(0,0,0), new_vec3(0,0,1), back_green);
	// rt->obj[2] = new_plane(new_vec3(3,0,3), new_vec3(0,-1,0), up_orange);
	// rt->obj[3] = new_plane(new_vec3(0,3,3), new_vec3(0,1,0), down_teal);
	// rt->obj[4] = new_plane(new_vec3(0,-3,3), new_vec3(-1,0,0), right_blue);

	//(-3,-2,5), (-3,0,3) (centerpt) left
	//(-2,-2,0), (0,0,0) (centerpt) center
	//(3,-2,1), (3,0,3) (centerpt) right
	//(-2,3,1), (0,3,3) (centerpt) up
	//(-2,-3,5), (0,-3,3) (centerpt) down (0-2, -3-0, 3--2)


	//scene with plane & sphere
// 	rt->obj[0] = new_plane_2(new_vec3(-2,-1,-1), new_vec3(0,1,0), down_teal);
// 	rt->obj[1] = new_sphere(new_vec3(-1, 0, -1), 0.5, \
// new_vec3(0.8, 0.8, 0.8), METAL);	//left
// 	rt->obj[2] = new_sphere(new_vec3(0, 0, -1.2), 0.5, \
// new_vec3(0.1, 0.2, 0.5), DIFFUSE);	//center
// 	rt->obj[3] = new_sphere(new_vec3(1, 0, -1), 0.5, \
// new_vec3(0.8, 0.6, 0.2), METAL);	//right
}

void	init_cyl_scene(t_rt *rt)
{
	rt->obj_count = 4;
	malloc_obj_ptr(&rt->obj, rt->obj_count);

	t_mat  left_red = new_material(new_vec3(1, 0.2, 0.2), DIFFUSE);
	// t_mat  center_green = new_material(new_vec3(0.2, 1, 0.2), METAL);
	// t_mat  right_blue = new_material(new_vec3(0.2, 0.2, 1), METAL);
	t_mat  up_orange = new_material(new_vec3(1, 0.5, 0), METAL);
	t_mat  down_teal = new_material(new_vec3(0.2, 0.8, 0.8), METAL);

	// rt->obj[0] = new_cyl(new_vec3(0,0,-1), new_vec3(0,1,0), 2, 2, center_green);
	// rt->obj[3] = new_plane(new_vec3(-1,2,2.5), new_vec3(0,1,0), right_blue);
	// rt->obj[3] = new_plane(new_vec3(0,3,-1), new_vec3(0,1,0), right_blue);
	// rt->obj[0] = new_sphere(new_vec3(0,0,-1), 2, center_green.albedo, center_green.type);
	// rt->obj[1] = new_cyl(new_vec3(-4,0,0), new_vec3(0,1,0), 1, 0.5, left_red);
	// rt->obj[2] = new_plane(new_vec3(-2,4,-1), new_vec3(0,1,0), up_orange);
	// rt->obj[3] = new_sphere(new_vec3(2, 2, -1), 0.5, \
// new_vec3(0.8, 0.6, 0.2), METAL);

	// rt->obj[0] = new_cyl(new_vec3(-2,3,5), new_vec3(0,1,0), 2, 0.5, up_orange);
	// rt->obj[1] = new_cyl(new_vec3(-2,-3,5), new_vec3(0,1,0), 2, 0.5, down_teal);
	// rt->obj[2] = new_cyl(new_vec3(-5,0,5), new_vec3(1,0,0), 3, 0.5, left_red);
	// rt->obj[3] = new_cyl(new_vec3(2,0,5), new_vec3(-1,0,0), 3, 0.5, right_blue);
	// rt->obj[0] = new_cyl(new_vec3(-2,0,0), new_vec3(0,0,1), 2, 0.5, center_green);

	// rt->obj[0] = new_cyl_2(new_vec3(-3,-2,5), new_vec3(0,0,-4), new_vec3(0,4,0), 3, 0.5, left_red);
	// rt->obj[1] = new_cyl_2(new_vec3(3,-2,1), new_vec3(0,0,4), new_vec3(0,4,0), 3, 0.5, right_blue);
	// rt->obj[0] = new_cyl_2(new_vec3(-5,0,5), new_vec3(0,0,-4), new_vec3(0,4,0), 3, 0.5, left_red);
	// rt->obj[1] = new_cyl_2(new_vec3(0,0,5), new_vec3(0,0,4), new_vec3(0,4,0), 3, 0.5, right_blue);
	// rt->obj[2] = new_cyl_2(new_vec3(-2,3,1), new_vec3(4,0,0), new_vec3(0,0,4), 2, 0.1, up_orange);

	// rt->obj[0] = new_cyl_2(new_vec3(-3,-2,5), new_vec3(0,0,-4), new_vec3(0,4,0), 2, 0.1, left_red);
	// rt->obj[1] = new_cyl_2(new_vec3(-2,-2,0), new_vec3(4,0,0), new_vec3(0,4,0), 2, 0.1, center_green);
	// rt->obj[2] = new_cyl_2(new_vec3(3,-2,1), new_vec3(0,0,4), new_vec3(0,4,0), 2, 0.1, right_blue);
	// rt->obj[3] = new_cyl_2(new_vec3(-2,3,1), new_vec3(4,0,0), new_vec3(0,0,4), 2, 0.1, up_orange);
	// rt->obj[4] = new_cyl_2(new_vec3(-2,-3,5), new_vec3(4,0,0), new_vec3(0,0,-4), 2, 0.1, down_teal);

	// close to each other
	rt->obj[0] = new_cyl(new_vec3(2,0,0), new_vec3(1,0,0), 2, 0.2, left_red);
	rt->obj[1] = new_cyl(new_vec3(1,0,0), new_vec3(-1,0,0), 2, 0.2, up_orange);
	// rt->obj[1] = new_cyl(new_vec3(0,0,0), new_vec3(1,0,0), 2, 0.2, right_blue);
	rt->obj[2] = new_cyl(new_vec3(-1,0,0), new_vec3(-1,0,0), 2, 0.2, up_orange);
	rt->obj[3] = new_cyl(new_vec3(-2.5,0,0), new_vec3(1,0,0), 2, 0.2, down_teal);
	// rt->obj[3] = new_cyl(new_vec3(-3,0,0), new_vec3(1,0,0), 2, 0.2, right_blue);
	
	// rt->obj[0] = new_cyl(new_vec3(-3,-2,5), new_vec3(1,0,0), 2, 0.1, left_red);
	// rt->obj[1] = new_cyl(new_vec3(-2,-2,0), new_vec3(0,0,1), 2, 0.1, center_green);
	// rt->obj[2] = new_cyl(new_vec3(-2,3,1), new_vec3(0,-1,0), 2, 0.1, up_orange);
	// rt->obj[3] = new_cyl(new_vec3(-2,-3,5), new_vec3(0,1,0), 2, 0.1, down_teal);
	// rt->obj[4] = new_cyl(new_vec3(3,-2,1), new_vec3(-1,0,0), 2, 0.1, right_blue);

	//(-3,-2,5), (-3,0,3) (centerpt) left
	//(-2,-2,0), (0,0,0) (centerpt) center
	//(3,-2,1), (3,0,3) (centerpt) right
	//(-2,3,1), (0,3,3) (centerpt) up
	//(-2,-3,5), (0,-3,3) (centerpt) down (0-2, -3-0, 3--2)

	/* ************************** plane scene **************************** */
	// rt->obj[0] = new_plane_2(new_vec3(-3,-2,5), new_vec3(1,0,0), left_red);
	// rt->obj[1] = new_plane_2(new_vec3(-2,-2,0), new_vec3(0,0,1), back_green);
	// rt->obj[2] = new_plane_2(new_vec3(3,-2,1), new_vec3(-1,0,0), right_blue);
	// rt->obj[0] = new_plane_2(new_vec3(-2,3,1), new_vec3(0,-1,0), up_orange);
	// rt->obj[4] = new_plane_2(new_vec3(-2,-3,5), new_vec3(0,1,0), down_teal);

}
