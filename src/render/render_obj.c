/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:13:15 by hsim              #+#    #+#             */
/*   Updated: 2025/07/13 20:17:02 by hsim             ###   ########.fr       */
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
	// n = unit_vec3(cross_product3d(coord_u, coord_v));
	// res.quad.normal = n;
	n = cross_product3d(coord_u, coord_v);
	res.quad.normal = unit_vec3(n);
	/*debug*/debug_print_vec("plane_norm", res.quad.normal);
	res.quad.d = scalar_product(res.quad.normal, res.quad.q);
	res.quad.w = div_vec_scalar(n, scalar_product(n, n));
	create_bbox(&res, res.bbox);
	return (res);
}

/* Q, norm, material */
t_obj	new_plane_2(t_vec3 position, t_vec3 normal, t_material mat)
{
	t_obj	res;
	t_vec3	n;

	res.type = PLANE;
	res.material.albedo = mat.albedo;
	res.material.type = mat.type;

	res.quad.q = position;
	res.quad.normal = unit_vec3(normal);
	/* **************** create_orthonomal_basis ******************** */
	t_vec3 tmp;

	if (res.quad.normal.x == 1)
		tmp = new_vec3(0,0,-1);
	else if (res.quad.normal.x != 0)
		tmp = new_vec3(0,0,1);
	else
		tmp = new_vec3(1,0,0);
	// res.quad.coord[X] = unit_vec3(cross_product3d(res.quad.normal, tmp));
	// res.quad.coord[Y] = cross_product3d(res.quad.normal, res.quad.coord[X]);
	res.quad.coord[Y] = unit_vec3(cross_product3d(res.quad.normal, tmp));
	res.quad.coord[X] = cross_product3d(res.quad.normal, res.quad.coord[Y]);

	res.quad.coord[X] = mult_vec_scalar(res.quad.coord[X], -4);
	res.quad.coord[Y] = mult_vec_scalar(res.quad.coord[Y], 4);
	n = cross_product3d(res.quad.coord[X], res.quad.coord[Y]);

	// n = normal;
	// res.quad.normal = unit_vec3(n);
	/* ************************************ */
	/*debug*/debug_print_vec("\nquad_norm", res.quad.normal);
	/*debug*/debug_print_vec("plane_coord_u", res.quad.coord[X]);
	/*debug*/debug_print_vec("plane_coord_v", res.quad.coord[Y]);

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
