/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_aabb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:56:09 by hsim              #+#    #+#             */
/*   Updated: 2025/07/18 23:53:59 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   aabb = axis-aligned bounding box
 *   brief: optimization - creating and managing bb to make rt more efficient
 * ************************************************************************** */

#include "minirt.h"
// bvh

/*
 * brief: packages them into range structure, small to big
 * compares which smaller and returns in as 1st param in t_interval
 */
static t_interval	assign_min_max(float a, float v)
{
	t_interval	range;

	if (a <= v)
	{
		range.min = a;
		range.max = v;
	}
	else
	{
		range.min = v;
		range.max = a;
	}
	return (range);
}

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

/* 
 * creates a bounding box between 2 3d points
 * (smallest box to fit 2 points)
 */
void	aabb(t_vec3 a, t_vec3 v, t_interval res[3])
{
	res[X] = assign_min_max(a.x, v.x);
	res[Y] = assign_min_max(a.y, v.y);
	res[Z] = assign_min_max(a.z, v.z);
	add_padding(res);
}

/*
 * comparing box0[X].min & box1[X].min
 * sets res[X].min to smallest value between them
 * sets res[X].max to biggest value between them
 * same applies to Y.min/max & Z.min/max
 * combines 2 bounding box into one
 */
void	update_aabb_box(t_interval box_0[3], t_interval box_1[3], \
t_interval res[3])
{
	res[X] = interval(box_0[X], box_1[X]);
	res[Y] = interval(box_0[Y], box_1[Y]);
	res[Z] = interval(box_0[Z], box_1[Z]);
}

/* copies value in src to res */
void	assign_bbox(t_interval src[3], t_interval res[3])
{
	res[X].min = src[X].min;
	res[Y].min = src[Y].min;
	res[Z].min = src[Z].min;
	res[X].max = src[X].max;
	res[Y].max = src[Y].max;
	res[Z].max = src[Z].max;
}

/*
 * initializes res to (0,0)
 * bbox value of obj (ranges frm 0 to argc) will be stored in res[3]
 */
// init res with bb of first obj, then iteratively expand to include bb of all arg object in array
// computes bb for group of obj
void	get_bbox_val(t_obj *obj, int argc, t_interval res[3])
{
	int	x;

	x = -1;
	// /*debug*/printf("get_bbox_val:ac:%d\n", argc);
	assign_bbox(obj[0].bbox, res);
	while (++x < argc)
	{
		// /*debug*/printf("combining: %d\n", x);
		// /*debug*/debug_print_bbox(NULL, obj[x].bbox);
		update_aabb_box(res, obj[x].bbox, res);
	}
	//5/2 =2 (mid)
	// ac-mid = 5-2=3
}

