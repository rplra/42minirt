/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_aabb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:56:09 by hsim              #+#    #+#             */
/*   Updated: 2025/08/22 08:44:52 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   aabb = axis-aligned bounding box
 * ************************************************************************** */

#include "minirt.h"

/* expand res range by num, res need to passed as &res */
void	expand_box(float num, t_interval *res)
{
	float	fin;

	fin = num / 2;
	*res = new_interval(res->min - fin, res->max + fin);
}

/* adds padding if bbox thickness on any axis (xyz) = 0 */
void	add_padding(t_interval res[3])
{
	float	num;

	num = 0.001f;
	if (res[X].max - res[X].min < num)
		expand_box(num, &res[X]);
	if (res[Y].max - res[Y].min < num)
		expand_box(num, &res[Y]);
	if (res[Z].max - res[Z].min < num)
		expand_box(num, &res[Z]);
}

void	aabb(t_vec3 pt_a, t_vec3 pt_b, t_interval res[3])
{
	res[X] = assign_min_max(pt_a.x, pt_b.x);
	res[Y] = assign_min_max(pt_a.y, pt_b.y);
	res[Z] = assign_min_max(pt_a.z, pt_b.z);
	add_padding(res);
}

/*
 * comparing box0[X].min & box1[X].min
 * sets res[X].min to smallest value between them
 * sets res[X].max to biggest value between them
 * same applies to Y.min/max & Z.min/max
 */
void	update_aabb_box(t_interval box_0[3], t_interval box_1[3], \
t_interval res[3])
{
	res[X] = interval(box_0[X], box_1[X]);
	res[Y] = interval(box_0[Y], box_1[Y]);
	res[Z] = interval(box_0[Z], box_1[Z]);
}

/*
 * initializes res to (0,0)
 * bbox value of obj (ranges frm 0 to argc) will be stored in res[3]
 */
void	get_bbox_val(t_obj *obj, int argc, t_interval res[3])
{
	int	x;

	x = -1;
	// /*debug*/printf("get_bbox_val:ac:%d\n", argc);
	// assign_bbox(obj[0].bbox, res);
	copy_bbox(res, obj[0].bbox);
	while (++x < argc)
	{
		// /*debug*/printf("combining: %d\n", x);
		// /*debug*/debug_print_bbox(NULL, obj[x].bbox);
		update_aabb_box(res, obj[x].bbox, res);
	}
	// 5/2 =2 (mid)
	// ac-mid = 5-2=3
}
