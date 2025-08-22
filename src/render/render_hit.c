/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 13:45:13 by hsim              #+#    #+#             */
/*   Updated: 2025/08/22 13:10:41 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * brief: gets the coordinate of the intersection hit
 * returns a 3d point along a vector ray
 * vec = origin + (t * direction)
 */
t_vec3	point_at(float t, t_ray ray)
{
	return (add_vec(ray.orig, mult_vec_scalar(ray.vector, t)));
}

/*
 * child function in hit
 * calls respective has_hit function depending on object type
 */
void	init_hit_func(bool (*has_hit[])())
{
	has_hit[PLANE] = has_hit_plane;
	has_hit[SPHERE] = has_hit_sphere;
	has_hit[CYLINDER] = has_hit_cy;
}

/*
 * ray_range: defines the minimum and maximum valid t values
 * 			(distance along the ray).
 * ray: the ray being tested against all scene objects
 * 1. use bvh tree to efficiently find intersections (returns boolean)
 * 2. check for hit > get ptr to obj > return ptr to obj hit
*/
t_obj	*hit(t_rt *rt, t_interval ray_range, t_ray ray)
{
	float	t;
	t_obj	*res;

	res = NULL;
	t = hit_bvh(rt->bvh, ray_range, ray, rt);
	if (t > 0)
	{
		res = &rt->obj[rt->hit.index];
		if (res->b_rotate == 1)
			transform_hit_pt(rt, *res);
	}
	return (res);
}

/* child function in has_hit_sphere, records details of the hitted obj */
int	update_hit_rec(t_rt *rt, int index, t_ray ray, float t)
{
	t_vec3 (*get_surf_norm[3])(t_ray r, t_obj o, float t, t_uchar s);
	init_surf_norm(get_surf_norm);
	rt->hit.surf_norm = get_surf_norm[rt->obj[index].type](ray, rt->obj[index],
			t, rt->hit.setting);
	rt->hit.at = add_vec(ray.orig, mult_vec_scalar(ray.vector, t));
	rt->hit.obj = &rt->obj[index];
	rt->hit.index = index;
	rt->hit.t = t;
	return (1);
}
