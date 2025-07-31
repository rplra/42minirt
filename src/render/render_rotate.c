/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:08:23 by hsim              #+#    #+#             */
/*   Updated: 2025/07/31 09:19:18 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// static
t_ray	rotate_ray_to_local(t_vec3 rotation, t_ray ray)
{
	t_ray	ray_rotate;

	ray_rotate.orig = quaternion_rotate_adv(ray.orig, rotation, 0);
	ray_rotate.vector = quaternion_rotate_adv(ray.vector, rotation, 0);
	return (ray_rotate);
}

t_ray	transform_ray(t_obj obj, t_ray ray)
{
	ray.orig = subtract_vec(ray.orig, obj.bbox_center);
	ray = rotate_ray_to_local(obj.rotate, ray);
	ray.orig = subtract_vec(ray.orig, mult_vec_scalar(obj.bbox_center, -1));
	return (ray);
}

void	transform_hit_pt(t_rt *rt, t_obj res)
{
	rt->hit.at = add_vec(rt->hit.at, res.bbox_center);
	
	rt->hit.at = quaternion_rotate_adv(rt->hit.at, res.rotate, 1);
	rt->hit.surf_norm = quaternion_rotate_adv(rt->hit.surf_norm, res.rotate, 1);
	
	rt->hit.at = add_vec(rt->hit.at, mult_vec_scalar(res.bbox_center, -1));
}

void	transform_bbox(t_rt *rt, t_uint index)
{
	copy_bbox(rt->obj[index].bbox, rt->obj[index].bbox_ori);

	aabb_translate(rt->obj[index], rt->obj[index].bbox, mult_vec_scalar(rt->obj[index].bbox_center, -1));
	aabb_rotate(rt->obj[index], rt->obj[index].bbox);
	aabb_translate(rt->obj[index], rt->obj[index].bbox, rt->obj[index].bbox_center);
}
