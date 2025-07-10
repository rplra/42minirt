/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_aabb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:56:09 by hsim              #+#    #+#             */
/*   Updated: 2025/07/09 22:14:28 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   aabb = axis-aligned bounding box
 * ************************************************************************** */

#include "minirt.h"

/* compares which smaller and returns in as 1st param in t_interval */
static t_interval	assign_min_max(float a, float b)
{
	t_interval	range;

	if (a <= b)
	{
		range.min = a;
		range.max = b;
	}
	else
	{
		range.min = b;
		range.max = a;
	}
	return (range);
}

void	aabb(t_vec3 a, t_vec3 b, t_interval range[3])
{
	range[X] = assign_min_max(a.x, b.x);
	range[Y] = assign_min_max(a.y, b.y);
	range[Z] = assign_min_max(a.z, b.z);
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

/* assigns value in src to res */
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
void	get_bbox_val(t_obj *obj, int argc, t_interval res[3])
{
	int	x;

	x = -1;
	/*debug*/printf("get_bbox_val:ac:%d\n", argc);
	assign_bbox(obj[0].bbox, res);
	while (++x < argc)
		update_aabb_box(res, obj[x].bbox, res);
}
