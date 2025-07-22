/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_aabb3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:35:35 by hsim              #+#    #+#             */
/*   Updated: 2025/07/20 15:29:13 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   functions creating bbox for different objs
 *   aabb = axis-aligned bounding box
 * ************************************************************************** */


#include "minirt.h"

//pending
/*
 * res = bound_box 
 * updates bound_box for static cylinder
 * value returned in res
 */
void	aabb_cyl(t_obj *obj, t_interval res[3])
{
	t_cylinder	cyl;
	t_vec3		tmp_vec;
	t_interval	bbox_side1[3];
	t_interval	bbox_side2[3];

	cyl = obj->cyl;
	if (cyl.rad < 0)
		cyl.rad = 0;
	tmp_vec = mult_vec_scalar(cyl.axis, cyl.height / 2);
	aabb(subtract_vec(cyl.pos, tmp_vec), add_vec(cyl.pos, tmp_vec), bbox_side1);
	tmp_vec = new_vec3(cyl.rad, cyl.rad, cyl.rad);
	aabb(subtract_vec(cyl.pos, tmp_vec), add_vec(cyl.pos, tmp_vec), bbox_side2);
	update_aabb_box(bbox_side1, bbox_side2, res);

	// aabb(cyl.pos, add_vec(add_vec(cyl.pos, cyl.coord[X]), cyl.coord[Y]), bbox_side1);
	// aabb(add_vec(cyl.pos, cyl.coord[X]), add_vec(cyl.pos, cyl.coord[Y]), bbox_side2);
	// update_aabb_box(bbox_side1, bbox_side2, res);
}

/* aabb for plane & quadrilaterals(all diff form of planes) */
void	aabb_plane(t_obj *obj, t_interval res[3])
{
	t_plane		plane;
	t_interval	bbox_side1[3];
	t_interval	bbox_side2[3];

	plane = obj->plane;
	aabb(plane.pos, add_vec(add_vec(plane.pos, plane.coord[X]), plane.coord[Y]), bbox_side1);
	aabb(add_vec(plane.pos, plane.coord[X]), add_vec(plane.pos, plane.coord[Y]), bbox_side2);
	update_aabb_box(bbox_side1, bbox_side2, res);

	//for ellipse plane shape
	// t_vec3	vec[2];
	// vec[X] = subtract_vec(subtract_vec(plane.pos, plane.coord[X]), plane.coord[Y]);
	// vec[Y] = subtract_vec(add_vec(plane.pos, plane.coord[X]), plane.coord[Y]);
	// aabb(vec[X], vec[Y], res);
}

// void	aabb_cyl(t_obj *obj, t_interval res[3])
// {
// 	t_cylinder	cyl;
// 	t_interval	bbox_horizontal;
// 	t_interval	bbox_vertical;

// 	cyl = obj->cyl;
// 	aabb(subtract_vec(sph.pos, rvec), add_vec(sph.pos, rvec), res);

// 	aabb()
// }

/*
 * res = bound_box 
 * updates bound_box for static sphere
 * value returned in res
 */
void	aabb_sph(t_obj *obj, t_interval res[3])
{
	t_sphere	sph;
	t_vec3		rvec;

	sph = obj->sph;
	if (sph.rad < 0)
		sph.rad = 0;
	rvec = new_vec3(sph.rad, sph.rad, sph.rad);
	aabb(subtract_vec(sph.pos, rvec), add_vec(sph.pos, rvec), res);
}

/*
 * child function in get_bounding_box
 * calls different function based on obj type
 */
static void	init_bbox_func(void (*aabb_obj[])(t_obj *, t_interval[3]))
{
	aabb_obj[SPHERE] = aabb_sph;
	aabb_obj[PLANE] = aabb_plane;
	aabb_obj[CYLINDER] = aabb_cyl;
	// aabb_obj[CYLINDER] = aabb_sph;
}

/*
 * bounding_box()
 * get bounding box size for different objs
 * calls bound box function based on obj_type
 * result stored in bound_box
 */
void	create_bbox(t_obj *obj, t_interval bound_box[3])
{
	void	(*func[3])(t_obj *, t_interval[3]);

	if (obj->type < 0 || obj->type > 2)
	{
		/*debug*/printf("invalid bbox_type! %d\n", obj->type);
		return ;
	}
	init_bbox_func(func);
	func[obj->type](obj, bound_box);
}
