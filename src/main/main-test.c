/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:45:50 by hsim              #+#    #+#             */
/*   Updated: 2025/06/28 23:04:57 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include <stdio.h>

// unsigned int lcg(unsigned int *seed) {
//     const unsigned int a = 1664525;
//     const unsigned int c = 1013904223;
//     const unsigned int m = 4294967295; // 2^32 - 1
//     // const unsigned int m = 0xFFFFFFFF; // 2^32 - 1

//     *seed = (a * (*seed) + c) % m;
//     return *seed;
// }

// double lcg_rand(unsigned int *seed) {
//     // return (double)lcg(seed) / 0xFFFFFFFF;
//     return (double)lcg(seed) / 4294967295;
// }

/* for debug purposes */
t_obj	*return_ptr(t_rt *vars)
{
	int		x = -1;
	t_obj	*tmp;
	t_obj	*res;

	tmp = vars->obj;
	while (++x < 2)
	{
		if (x == 1)
			res = tmp;
		tmp = tmp->next;
	}
	return (res);
}

void	incr_ptr(t_rt *vars)
{
	// while (vars->obj->next)
		// vars->obj = vars->obj->next;
	vars->ray.orig = new_vec3(10, 10, 10);
}

int main()
{
	/* __________________ rand test __________________*/
	// unsigned int seed = 12345; // You can change this seed
	
	// for (int i = 0; i < 3; i++) {
		//     printf("Pseudo-random[%d]: %f\n", i, rand_lcg(&seed));
		// }
		
	/* __________________ sample_sq_rand __________________*/
	// unsigned int seed = 12345; // You can change this seed
	// sample_sq_rand(&seed);
	// sample_sq_rand(&seed);
	// sample_sq_rand(&seed);
	/* __________________ rand_vec __________________*/
	// unsigned int seed = 12345; // You can change this seed
	// t_vec3	res;
	// int	x = -1;
	// // res = rand_vec(&seed);
	
	// // res = new_vector3d(-2, -2, -2);
	// while (++x < 10)
	// {
	// 	res = rand_unit_vec(&seed);
	// 	printf("res: %f %f %f\n", res.x, res.y, res.z);
	// }

	/* __________________ rand_on_hemisphere __________________*/
	// unsigned int seed = 12345; // You can change this seed
	// t_vec3	res;
	// int	x = -1;
	// while (++x < 3)
	// {
	// 	res = rand_on_hemisphere(&seed, new_vector3d(0.5, 1, 1));
		// printf("res: %f %f %f\n", res.x, res.y, res.z);
	// }

	/* __________________ near_zero __________________*/
	// t_vec3 vec = new_vec3(0.001, 0.001, 0.00018);
	// printf("%d\n", is_near_zero(vec));
	
	/* __________________ retrieve_rgb __________________*/
	// int	c[3];
	// split_rgb(0xFF8080, c);
	// printf("rgb: %d %d %d\n", c[R], c[G], c[B]);
	
	/* __________________ bound_box __________________*/
	// t_sph		*sph;
	// t_interval	bbox[3];
	
	// sph = (t_sph *)malloc(sizeof(t_sph));
	// sph->rad = 3;
	// sph->orig = new_vec3(0, 0, 0);
	// bounding_box(SPHERE, sph, bbox);
	// printf("bbox_x: %f %f", bbox[X].min, bbox[X].max);

	/* __________________ init_obj __________________*/
	// t_rt	vars;
	// t_obj	*tmp;
	
	// init_obj(&vars);
	// tmp = vars.obj;
	// while (tmp)
	// {
	// 	printf("sph_rad: %f\n", tmp->sph.rad);
	// 	tmp = tmp->next;
	// }
	// ft_lstclear_obj(&vars.obj);
	// return (0);

	/* __________________ test_incr_ptr __________________*/
	// t_rt	vars;
	// t_obj	*tmp;
	
	// init_obj(&vars);
	// tmp = vars.obj;
	// printf("sph: %f %f %f\n", tmp->sph.orig.x, tmp->sph.orig.y, tmp->sph.orig.z);
	// ft_lstclear_obj(&vars.obj);

	// vars.ray.orig = new_vec3(0, -1, 0);
	// printf("ray_init: %f %f %f\n", vars.ray.orig.x, vars.ray.orig.y, vars.ray.orig.z);
	// incr_ptr(&vars);
	// printf("ray: %f %f %f\n", vars.ray.orig.x, vars.ray.orig.y, vars.ray.orig.z);

	// return (0);
	
	/* __________________ return_ptr __________________*/
	// t_rt	vars;
	// t_obj	*tmp;

	// init_obj(&vars);
	// tmp = return_ptr(&vars);
	// printf("sph= %f %f %f\n", tmp->sph.orig.x, tmp->sph.orig.y, tmp->sph.orig.z);
	// ft_lstclear_obj(&vars.obj);

	// return (0);	
}
