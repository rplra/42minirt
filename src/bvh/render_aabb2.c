/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_aabb2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 22:23:53 by hsim              #+#    #+#             */
/*   Updated: 2025/07/18 23:54:04 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
// bvh

// brief; organize and sort objects in 3d space based on their bb

/*
 * compares 2 objs by min value of their bb of a given axis
 * checks which object comes first
 */
static bool	box_compare(t_obj a, t_obj v, int axis)
{
	t_interval	a_axis_interval[3];
	t_interval	b_axis_interval[3];

	// /*debug*/debug_print_vec("a", a.sph.orig);
	// /*debug*/debug_print_vec("b", b.sph.orig);
	create_bbox(&a, a_axis_interval);
	create_bbox(&v, b_axis_interval);

	// /*debug*/printf("a.[%d].min: %f, b.[%d].min: %f\n", axis, a_axis_interval[axis].min, axis, b_axis_interval[axis].min);
	// return (a.sph.orig.z < b.sph.orig.z);
	return (a_axis_interval[axis].min < b_axis_interval[axis].min);
}

/* compares 2 objs by min X val of bb */
static bool	box_compare_x(t_obj a, t_obj v)
{
	return (box_compare(a, v, X));
}

static bool	box_compare_y(t_obj a, t_obj v)
{
	return (box_compare(a, v, Y));
}

static bool	box_compare_z(t_obj a, t_obj v)
{
	return (box_compare(a, v, Z));
}

void	init_box_compare(bool (*box_compare[])(t_obj, t_obj))
{
	box_compare[X] = box_compare_x;
	box_compare[Y] = box_compare_y;
	box_compare[Z] = box_compare_z;
}