/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_geometry.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:57:35 by hsim              #+#    #+#             */
/*   Updated: 2025/08/14 23:36:54 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * when a ray hits the plane,
	we need to know if it landed on the visible part of the plane
 * these 2 functions make sure we have a clear map of the visible part
 * picks a direction that is NOT the same as "up" (normal)
 */
t_vec3	set_tmp_vec(t_vec3 normal)
{
	t_vec3	tmp;

	if (normal.x == 1) // i think this is additional
		tmp = new_vec3(0, 0, -1);
	else if (normal.x != 0)
		tmp = new_vec3(0, 0, 1);
	else
		tmp = new_vec3(1, 0, 0);
	return (tmp);
}

/* 
 * brief: use the normal and the temp vec,
 * 		to calc two perpendicular directions (forward and right)
 */
void	setup_plane_geometry(t_obj *obj)
{
	t_vec3	n;
	t_vec3	tmp_vec;

	obj->type = PLANE;
	tmp_vec = set_tmp_vec(obj->plane.normal);
	obj->plane.coord[Y] = unit_vec3(cross_product(obj->plane.normal, tmp_vec));
	obj->plane.coord[X] = cross_product(obj->plane.normal, obj->plane.coord[Y]);
	obj->plane.coord[X] = mult_vec_scalar(obj->plane.coord[X], PLANE_X);
	obj->plane.coord[Y] = mult_vec_scalar(obj->plane.coord[Y], PLANE_Y);
	n = cross_product(obj->plane.coord[X], obj->plane.coord[Y]);
	obj->plane.d = scalar_product(obj->plane.normal, obj->plane.pos);
	obj->plane.w = div_vec_scalar(n, scalar_product(n, n));
}

void	setup_cylinder_geometry(t_obj *obj)
{
	t_vec3	n;
	t_vec3	tmp_vec;

	obj->type = CYLINDER;
	tmp_vec = set_tmp_vec(obj->cyl.axis);
	obj->cyl.coord[Y] = unit_vec3(cross_product(obj->cyl.axis, tmp_vec));
	obj->cyl.coord[X] = cross_product(obj->cyl.axis, obj->cyl.coord[Y]);
	// scale to certain size
	obj->cyl.coord[X] = mult_vec_scalar(obj->cyl.coord[X], obj->cyl.rad * -2);
	obj->cyl.coord[Y] = mult_vec_scalar(obj->cyl.coord[Y], obj->cyl.rad * 2);
	n = cross_product(obj->cyl.coord[X], obj->cyl.coord[Y]);
	obj->cyl.axis_height = mult_vec_scalar(obj->cyl.axis, obj->cyl.height / 2);
	obj->cyl.d[0] = scalar_product(obj->cyl.axis, subtract_vec(obj->cyl.pos,
				obj->cyl.axis_height)); //official use corner
	obj->cyl.d[1] = scalar_product(obj->cyl.axis, add_vec(obj->cyl.pos,
				obj->cyl.axis_height)); // official use corner
	obj->cyl.w = div_vec_scalar(n, scalar_product(n, n));
}
