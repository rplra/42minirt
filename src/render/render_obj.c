/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:13:15 by hsim              #+#    #+#             */
/*   Updated: 2025/07/25 08:45:10 by hsim             ###   ########.fr       */
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

t_obj	new_cyl(t_vec3 position, t_vec3 normal, float radius, float height, t_material mat)
{
	t_vec3	n;
	t_obj	res;
	t_vec3	tmp_vec;

	res.type = CYLINDER;
	res.material.fuzz = 0;
	res.material.albedo = mat.albedo;
	res.material.type = mat.type;

	res.cyl.rad = radius;
	res.cyl.height = height;

	res.cyl.pos = position;
	res.cyl.axis = unit_vec3(normal);

	tmp_vec = set_tmp_vec(res.cyl.axis);
	res.cyl.coord[Y] = unit_vec3(cross_product(res.cyl.axis, tmp_vec));
	res.cyl.coord[X] = cross_product(res.cyl.axis, res.cyl.coord[Y]);
	//scale to certain size
	res.cyl.coord[X] = mult_vec_scalar(res.cyl.coord[X], radius * -2); //-2 diameter
	res.cyl.coord[Y] = mult_vec_scalar(res.cyl.coord[Y], radius * 2);
	n = cross_product(res.cyl.coord[X], res.cyl.coord[Y]);

	// corner of bottom cap, corner of top cap
	// t_vec3 corner = subtract_vec(subtract_vec(res.cyl.pos, \
// div_vec_scalar(res.cyl.coord[X], 2)), div_vec_scalar(res.cyl.coord[Y], 2));

	// /*debug*/debug_print_vec("\ncyl_corner_center", res.cyl.corner);
	// /*debug*/debug_print_vec("cyl_cap_norm", res.cyl.axis);
	// /*debug*/debug_print_vec("cap_coord_u", res.cyl.coord[X]);
	// /*debug*/debug_print_vec("cap_coord_v", res.cyl.coord[Y]);
	// /*debug*/debug_print_vec("norm_u", unit_vec3(res.cyl.coord[X]));
	// /*debug*/debug_print_vec("norm_v", unit_vec3(res.cyl.coord[Y]));

	res.cyl.d[0] = scalar_product(res.cyl.axis, subtract_vec(res.cyl.pos, mult_vec_scalar(res.cyl.axis, height / 2))); //official use corner
	res.cyl.d[1] = scalar_product(res.cyl.axis, add_vec(res.cyl.pos, mult_vec_scalar(res.cyl.axis, height / 2))); //official use corner
	res.cyl.w = div_vec_scalar(n, scalar_product(n, n));
	create_bbox(&res, res.bbox);
	return (res);
}

t_material	new_material(t_vec3 color, t_mat_type type)
{
	t_material	mat;

	mat.albedo = color;
	mat.type = type;
	return (mat);
}

/* Q,u,v, color, mat_type */
t_obj	new_plane_2(t_vec3 position, t_vec3 coord_u, t_vec3 coord_v, t_material mat)
{
	t_obj	res;
	t_vec3	n;

	res.type = PLANE;
	res.material.albedo = mat.albedo;
	res.material.type = mat.type;

	res.plane.pos = position;
	res.plane.coord[X] = coord_u;
	res.plane.coord[Y] = coord_v;
	n = cross_product(coord_u, coord_v);
	res.plane.normal = unit_vec3(n);
	// /*debug*/debug_print_vec("plane_norm", res.quad.normal);
	res.plane.d = scalar_product(res.plane.normal, res.plane.pos);
	res.plane.w = div_vec_scalar(n, scalar_product(n, n));
	create_bbox(&res, res.bbox);
	return (res);
}

// use this
/* Q, norm, material */
t_obj	new_plane(t_vec3 position, t_vec3 normal, t_material mat)
{
	t_obj	res;
	t_vec3	n;

	res.type = PLANE;
	res.material.albedo = mat.albedo;
	res.material.type = mat.type;

	res.plane.pos = position;
	res.plane.normal = unit_vec3(normal);
	/* **************** create_orthonomal_basis ******************** */
	t_vec3	tmp_vec;

	tmp_vec = set_tmp_vec(res.plane.normal);
	res.plane.coord[Y] = unit_vec3(cross_product(res.plane.normal, tmp_vec));
	res.plane.coord[X] = cross_product(res.plane.normal, res.plane.coord[Y]);
	//scale to certain size
	res.plane.coord[X] = mult_vec_scalar(res.plane.coord[X], -4); //4
	res.plane.coord[Y] = mult_vec_scalar(res.plane.coord[Y], 4);
	n = cross_product(res.plane.coord[X], res.plane.coord[Y]);
	/* ************************************************************* */
	/*debug*/debug_print_vec("\nquad_norm", res.plane.normal);
	/*debug*/debug_print_vec("plane_coord_u", res.plane.coord[X]);
	/*debug*/debug_print_vec("plane_coord_v", res.plane.coord[Y]);

	res.plane.d = scalar_product(res.plane.normal, res.plane.pos);
	res.plane.w = div_vec_scalar(n, scalar_product(n, n));
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
