/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_aabb2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 22:23:53 by hsim              #+#    #+#             */
/*   Updated: 2025/07/29 08:25:52 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

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