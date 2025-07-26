/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:13:15 by hsim              #+#    #+#             */
/*   Updated: 2025/07/25 20:33:32 by rraja-az         ###   ########.fr       */
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

t_mat	new_material(t_vec3 color, t_mat_type type)
{
	t_mat	mat;

	mat.albedo = color;
	mat.type = type;
	return (mat);
}

/* Q,u,v, color, mat_type */
t_obj	new_plane(t_vec3 position, t_vec3 coord_u, t_vec3 coord_v, t_mat mat)
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

/* Q, norm, material */
t_obj	new_plane_2(t_vec3 position, t_vec3 normal, t_mat mat)
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
	res.plane.coord[X] = mult_vec_scalar(res.plane.coord[X], -4);
	res.plane.coord[Y] = mult_vec_scalar(res.plane.coord[Y], 4);
	n = cross_product(res.plane.coord[X], res.plane.coord[Y]);
	/* ************************************************************* */
	// /*debug*/debug_print_vec("\nquad_norm", res.plane.normal);
	// /*debug*/debug_print_vec("plane_coord_u", res.plane.coord[X]);
	// /*debug*/debug_print_vec("plane_coord_v", res.plane.coord[Y]);

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
