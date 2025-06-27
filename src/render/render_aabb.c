/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_aabb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:56:09 by hsim              #+#    #+#             */
/*   Updated: 2025/06/27 16:51:32 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* aabb = axis-aligned bounding box
 * ************************************************************************** */

#include "render.h"

/* compares which smaller and returns in as 1st param in t_interval */
static t_interval	assign_min_max(float a, float b)
{
	t_interval	range;

	if (a <= b)
	{
		range.min = a;
		range.max = b;
	}
	else
	{
		range.min = b;
		range.max = a;
	}
	return (range);
}

void	aabb(t_vec3 a, t_vec3 b, t_interval range[3])
{
	range[X] = assign_min_max(a.x, b.x);
	range[Y] = assign_min_max(a.y, b.y);
	range[Z] = assign_min_max(a.z, b.z);
}

/*
 * comparing box0[X].min & box1[X].min
 * sets res[X].min to smallest value between them
 * sets res[X].max to biggest value between them
 * same applies to Y.min/max & Z.min/max
 */
void	update_aabb_box(t_interval box_0[3], t_interval box_1[3], \
t_interval res[3])
{
	res[X] = interval(box_0[X], box_1[X]);
	res[Y] = interval(box_0[Y], box_1[Y]);
	res[Z] = interval(box_0[Z], box_1[Z]);
}

void	assign_ray_t(float t0, float t1, t_interval *ray_t)
{
	if (t0 < t1)
	{
		if (t0 > ray_t->min)
			ray_t->min = t0;
		else if (t1 < ray_t->max)
			ray_t->max = t1;
	}
	else
	{
		if (t1 > ray_t->min)
			ray_t->min = t1;
		else if (t0 < ray_t->max)
			ray_t->max = t0;
	}
}

// int	hit(t_ray r, t_interval ax[3], t_interval ray_t)
// {
// 	int		axis;
// 	float	axis_inv; //inverse axis, adinv
// 	float	ray_vec[3];
// 	float	ray_orig[3];
// 	float	t[2];
// 
// 	axis = -1;
// 	vec3_to_arr(r.vector, ray_vec);
// 	vec3_to_arr(r.orig, ray_orig);
// 	while (++axis < 3)
// 	{
// 		axis_inv = 1 / ray_vec[axis];
// 		t[0] = (ax[axis].min - ray_orig[axis]) * axis_inv;
// 		t[1] = (ax[axis].max - ray_orig[axis]) * axis_inv;
// 		assign_ray_t(t[0], t[1], &ray_t);
// 		if (ray_t.max <= ray_t.min)
// 			return (-1);
// 	}
// 	return (0);
// }

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
 */
void	get_bbox(t_obj_type type, t_obj *obj, t_interval bound_box[3])
{
	void	(*func[3])(t_obj *, t_interval[3]);

	if (type < 0 || type > 2)
		return ;
	init_bbox_func(func);
	func[type](obj, bound_box);
}
