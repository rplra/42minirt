/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_aabb3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:35:35 by hsim              #+#    #+#             */
/*   Updated: 2025/07/09 15:37:00 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   functions creating bbox for different objs
 *   aabb = axis-aligned bounding box
 * ************************************************************************** */


#include "minirt.h"

/*
 * res = bound_box 
 * updates bound_box for static sphere
 * value returned in res
 */
void	aabb_sph(t_obj *obj, t_interval res[3])
{
	t_sph	sph;
	t_vec3	rvec;

	sph = obj->sph;
	if (sph.rad < 0)
		sph.rad = 0;
	rvec = new_vec3(sph.rad, sph.rad, sph.rad);
	aabb(subtract_vec(sph.orig, rvec), add_vec(sph.orig, rvec), res);
}

/*
 * child function in get_bounding_box
 * calls different function based on obj type
 */
static void	init_bbox_func(void (*aabb_obj[])(t_obj *, t_interval[3]))
{
	aabb_obj[SPHERE] = aabb_sph;
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
