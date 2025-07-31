/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:52:37 by hsim              #+#    #+#             */
/*   Updated: 2025/07/31 11:35:05 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	debug_print_vec(char *str, t_vec3 vec)
{
	printf("%s: %f %f %f\n", str, vec.x, vec.y, vec.z);
}

void	debug_print_arr(char *str, t_obj *obj, int obj_count)
{
	int	i;

	i = -1;
	while (++i < obj_count)
	{
		if (str)
			printf("%s: %d: ", str, obj[i].id);
		if (obj[i].type == SPHERE)
		{
			printf("sph!\n");
			// printf("rad: %f\n%s: %d: bbox:\n", obj[i].sph.rad, str, obj[i].id);
			// debug_print_bbox(" |sph_bbox", obj[i].bbox);
			// debug_print_vec(" |sph", obj[i].sph.pos);
			// printf("----------------\n");
		}
		else if (obj[i].type == CYLINDER)
		{
			printf("cyl!\n");
			// printf("bbox:\n");
			// debug_print_bbox(" |cyl_bbox", obj[i].bbox);
			// // printf(" |d: %f\n", obj[i].cyl.d);
			// // printf(" |cyl_height: %f\n |cyl_rad: %f\n", obj[i].cyl.height, obj[i].cyl.rad);
			// debug_print_vec(" |cyl", obj[i].cyl.pos);
			// // debug_print_vec(" |cyl_axis", obj[i].cyl.axis);
			// // debug_print_vec(" |cyl_coord[X]", obj[i].cyl.coord[X]);
			// // debug_print_vec(" |cyl_coord[Y]", obj[i].cyl.coord[Y]);
			// // debug_print_vec(" |cyl_col", obj[i].material.albedo);
		}
		else if (obj[i].type == PLANE)
		{
			debug_print_vec("pl", obj[i].plane.pos);
			// printf(" |d: %f\n", obj[i].plane.d);
			// debug_print_vec(" |pl_u", obj[i].quad.coord[X]);
			// debug_print_vec(" |pl_v", obj[i].quad.coord[Y]);
			debug_print_bbox(" |pl_bbox", obj[i].bbox);
		}
	}
}

void	debug_print_bbox(char *str, t_interval bbox[3])
{
	printf("%s[X]: %f %f\n", str, bbox[X].min, bbox[X].max);
	printf("%s[Y]: %f %f\n", str, bbox[Y].min, bbox[Y].max);
	printf("%s[Z]: %f %f\n", str, bbox[Z].min, bbox[Z].max);
}

void	debug_print_bvh(char *str, t_bvh_tree *bvh)
{
	if (!bvh)
		return ;
	printf("%s: BVH_NODE %d~%d:\n", str, bvh->id[L], bvh->id[R]);
	debug_print_bbox(" |bvh_bbox", bvh->bbox);

	if (bvh->type[L] != BVH)
	{
		printf("%s: bvh_id: %d:\n", str, bvh->id[L]);
		// debug_print_arr(" |bvh_l", (t_obj *)bvh->left, 1);
	}
	else
	{
		// printf("%s: bvh_id_l: BVH_NODE %d:\n", str, bvh->id[L]);
		// debug_print_bbox(" |bvh_bbox", bvh->bbox);
		// printf("|bvh_bbox[X]: %f %f\n\n", bvh->bbox[X].min, bvh->bbox[X].max);
		debug_print_bvh(str, bvh->left);
	}
	if (bvh->type[R] != BVH)
	{
		printf("%s: bvh_id: %d:\n", str, bvh->id[R]);
		// debug_print_arr(" |bvh_r", (t_obj *)bvh->right, 1);
	}
	else
	{
		// printf("%s: bvh_id_r: BVH_NODE %d:\n", str, bvh->id[R]);
		// debug_print_bbox(" |bvh_bbox", bvh->bbox);
		// printf("|bvh_bbox[X]: %f %f\n\n", bvh->bbox[X].min, bvh->bbox[X].max);
		debug_print_bvh(str, bvh->right);
	}
}
