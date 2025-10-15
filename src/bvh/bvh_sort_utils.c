/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_sort_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:17:01 by hsim              #+#    #+#             */
/*   Updated: 2025/08/14 17:30:19 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	copy_sph(t_obj *dest, t_obj src)
{
	dest->sph.pos = src.sph.pos;
	dest->sph.rad = src.sph.rad;
}

void	copy_plane(t_obj *dest, t_obj src)
{
	dest->plane.pos = src.plane.pos;
	dest->plane.coord[X] = src.plane.coord[X];
	dest->plane.coord[Y] = src.plane.coord[Y];
	dest->plane.normal = src.plane.normal;
	dest->plane.d = src.plane.d;
	dest->plane.w = src.plane.w;
}

void	copy_cyl(t_obj *dest, t_obj src)
{
	dest->cyl.pos = src.cyl.pos;
	dest->cyl.axis = src.cyl.axis;
	dest->cyl.rad = src.cyl.rad;
	dest->cyl.height = src.cyl.height;
	dest->cyl.coord[X] = src.cyl.coord[X];
	dest->cyl.coord[Y] = src.cyl.coord[Y];
	dest->cyl.d[0] = src.cyl.d[0];
	dest->cyl.d[1] = src.cyl.d[1];
	dest->cyl.w = src.cyl.w;
	dest->cyl.axis_height = src.cyl.axis_height;
}

void	init_copy_func(void (*copy[3])(t_obj *, t_obj))
{
	copy[SPHERE] = copy_sph;
	copy[PLANE] = copy_plane;
	copy[CYLINDER] = copy_cyl;
}

void	copy_obj(t_obj *dest, t_obj src)
{
	void	(*copy[3])(t_obj *, t_obj);

	dest->id = src.id;
	dest->type = src.type;
	dest->material.albedo = src.material.albedo;
	dest->material.type = src.material.type;
	dest->material.specular = src.material.specular;
	dest->material.reflect = src.material.reflect;
	dest->material.fuzz = src.material.fuzz;
	dest->bbox_center = src.bbox_center;
	dest->b_rotate = src.b_rotate;
	dest->rotate = src.rotate;
	init_copy_func(copy);
	copy[src.type](dest, src);
	copy_bbox(dest->bbox, src.bbox);
	copy_bbox(dest->bbox_ori, src.bbox_ori);
}
