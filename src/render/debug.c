/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:52:37 by hsim              #+#    #+#             */
/*   Updated: 2025/07/06 16:08:42 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	debug_print_vec(char *str, t_vec3 vec)
{
	printf("%s: %f %f %f\n", str, vec.x, vec.y, vec.z);
}

// void	debug_print_lst(char *str, t_obj *lst)
// {
// 	t_obj	*tmp;

// 	tmp = lst;
// 	while (tmp)
// 	{
// 		if (str)
// 			printf("%s: ", str);
// 		if (tmp->type == SPHERE)
// 			debug_print_vec("sph", tmp->sph.orig);
// 		tmp = tmp->next;
// 	}
// }

void	debug_print_arr(char *str, t_obj *obj, int obj_count)
{
	int	x;

	x = -1;
	while (++x < obj_count)
	{
		if (str)
			printf("%s: %d: ", str, x);
		if (obj->type == SPHERE)
			debug_print_vec("sph", obj[x].sph.orig);
		else if (obj->type == CYLINDER)
			debug_print_vec("cyl", obj[x].cyl.position);
		else if (obj->type == PLANE)
			debug_print_vec("pl", obj[x].plane.position);
	}
}

void	debug_print_bvh(char *str, t_bvh_tree *bvh)
{
	if (!bvh)
		return ;
	if (bvh->l_type != BVH)
		debug_print_arr("bvh_l", (t_obj *)bvh->left, 1);
	else
		debug_print_bvh(str, bvh->left);
	if (bvh->r_type != BVH)
		debug_print_arr("bvh_r", (t_obj *)bvh->right, 1);
	else
		debug_print_bvh(str, bvh->right);
}
