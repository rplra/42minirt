/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:45:50 by hsim              #+#    #+#             */
/*   Updated: 2025/07/04 19:36:35 by hsim             ###   ########.fr       */
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
// t_obj	*return_ptr(t_rt *vars)
// {
// 	int		x = -1;
// 	t_obj	*tmp;
// 	t_obj	*res;

// 	tmp = vars->obj;
// 	while (++x < 2)
// 	{
// 		if (x == 1)
// 			res = tmp;
// 		tmp = tmp->next;
// 	}
// 	return (res);
// }

void	incr_ptr(t_rt *vars)
{
	// while (vars->obj->next)
		// vars->obj = vars->obj->next;
	vars->ray.orig = new_vec3(10, 10, 10);
}

void	incr_obj(t_obj *obj)
{
	// while (obj->next)
		// obj = obj->next;
	obj[0].sph.orig = new_vec3(10, 10, 10);
	// /*debug*/debug_print_vec("incr_obj", obj->sph.orig);
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

	/* __________________ rand_int __________________*/
	// unsigned int seed = 12345; // You can change this seed
	// int	x = 0;
	// while (x++ < 20)
	// {
	// 	int i = rand_int(&seed, 0, 2);
	// 	printf("%d, seed:%u\n", i, seed);
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
	
	/* __________________ copy_array __________________*/
	// t_rt	vars;
	// t_obj	*lst = NULL;
	// int n = 2;
	
	// init_obj(&vars);
	// copy_array(&lst, vars.obj, n);
	// debug_print_lst(NULL, lst);
	// ft_lstclear_obj(&lst);
	// ft_lstclear_obj(&vars.obj);
	
	/* __________________ merge_sort_obj __________________*/
	// t_rt	vars;

	// init_obj(&vars);
	// merge_sort(vars.obj, ft_lstsize_obj(vars.obj), 0, box_compare);
	// // merge_sort(vars.obj, 2, box_compare);
	// ft_lstclear_obj(&vars.obj);

	/* __________________ incr_obj __________________*/
	// t_rt	vars;
	
	// init_obj(&vars);
	// incr_obj(vars.obj);
	// if (vars.obj)
	// 	printf("yes! %f %f %f\n", vars.obj->sph.orig.x, vars.obj->sph.orig.y, vars.obj->sph.orig.z);
	// ft_lstclear_obj(&vars.obj);

	/* __________________ return_ptr __________________*/
	// t_rt	vars;
	// t_obj	*tmp;
	
	// init_obj(&vars);
	// tmp = return_ptr(&vars);
	// printf("sph= %f %f %f\n", tmp->sph.orig.x, tmp->sph.orig.y, tmp->sph.orig.z);
	// ft_lstclear_obj(&vars.obj);
	
	/* __________________ lst_move_forward __________________*/
	// t_rt	vars;
	// t_obj	*tmp;
	
	// init_obj(&vars);
	// tmp = lst_forward(vars.obj, 2);
	// printf("obj: sph= %f %f %f\n", vars.obj->sph.orig.x, vars.obj->sph.orig.y, vars.obj->sph.orig.z);
	// printf("tmp: sph= %f %f %f\n", tmp->sph.orig.x, tmp->sph.orig.y, tmp->sph.orig.z);
	
	/* __________________ build_bvh_tree __________________*/
	// t_rt	vars;
	// t_obj	node[2];
	// size_t	range[2];

	// init_obj(&vars);
	// range[0] = 0;
	// range[1] = 2;
	// build_bvh_tree(node, *vars.obj, range);
	// printf("node L: sph= %f %f %f\n", node[L].sph.orig.x, node[L].sph.orig.y, node[L].sph.orig.z);
	// printf("node R: sph= %f %f %f\n", node[R].sph.orig.x, node[R].sph.orig.y, node[R].sph.orig.z);

	/* __________________ merge_sort __________________*/
	t_rt	vars;
	init_obj(&vars);	//array ptr vs linked_lst ptr
	bool	(*box_compare[3])();

	init_box_compare(box_compare);
	merge_sort(vars.obj, vars.sph_count, box_compare[X]);
	printf("sorted:\n");
	debug_print_arr("arr", vars.obj, vars.sph_count);
	free(vars.obj);

	return (0);	
}
