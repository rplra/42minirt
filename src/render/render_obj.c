/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:13:15 by hsim              #+#    #+#             */
/*   Updated: 2025/07/11 17:13:33 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	new_sphere(t_vec3 position, float sph_radius, t_vec3 color, t_mat_type mat_type)
{
	t_obj	target;

	target.type = SPHERE;
	target.sph.pos = position;
	target.sph.rad = sph_radius;
	target.material.albedo = color;
	target.material.type = mat_type;
	create_bbox(&target, target.bbox);
	return (target);
}

t_material	new_material(t_vec3 color, t_mat_type type)
{
	t_material	mat;

	mat.albedo = color;
	mat.type = type;
	return (mat);
}

/* Q,u,v, color, mat_type */
t_obj	new_plane(t_vec3 position, t_vec3 coord_u, t_vec3 coord_v, t_material mat)
{
	t_obj	res;
	t_vec3	n;

	res.type = PLANE;
	res.material.albedo = mat.albedo;
	res.material.type = mat.type;

	res.quad.q = position;
	res.quad.coord[X] = coord_u;
	res.quad.coord[Y] = coord_v;
	n = cross_product3d(coord_u, coord_v);
	res.quad.normal = unit_vec3(n);
	res.quad.d = scalar_product(res.quad.normal, res.quad.q);
	res.quad.w = div_vec_scalar(n, scalar_product(n, n));
	create_bbox(&res, res.bbox);
	return (res);
}

/*
 * custom plugin to assign material to objs
 * t_obj need to be passed as &obj[num]
 */
void	update_material(t_obj *obj, t_mat_type type, float fuzz)
{
	obj->material.type = type;
	if (type == METAL)
		obj->material.fuzz = fuzz;
}

// /*
//  * returns obj function that returns a malloc-ed pointer
//  * for specified obj_type
//  */
// void	init_new_obj_func(t_obj (*add_obj[])(t_vec3, float, t_vec3, t_uchar))
// {
// 	add_obj[SPHERE] = new_sphere;
// }
