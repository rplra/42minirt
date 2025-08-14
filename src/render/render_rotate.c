/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:08:23 by hsim              #+#    #+#             */
/*   Updated: 2025/08/13 13:58:01 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * child function in transform_ray
 * rotates ray to local space to apply rotation
 */
static t_ray	rotate_ray_to_local(t_vec3 rotation, t_ray ray)
{
	t_ray	ray_rotate;

	ray_rotate.orig = quaternion_rotate_adv(ray.orig, rotation, 0);
	ray_rotate.vector = quaternion_rotate_adv(ray.vector, rotation, 0);
	return (ray_rotate);
}

/*
 * translates ray to world center (to make object rotate frm its center axis)
 * apply rotation
 * translates rotated ray back to obj position
 */
t_ray	transform_ray(t_obj obj, t_ray ray)
{
	ray.orig = subtract_vec(ray.orig, obj.bbox_center);
	ray = rotate_ray_to_local(obj.rotate, ray);
	ray.orig = subtract_vec(ray.orig, mult_vec_scalar(obj.bbox_center, -1));
	return (ray);
}

/*
 * 1. translate hit point to world center so that obj appears
 *    to rotate at its own axis
 * 2. apply rotation
 * 3. translate hit point back to obj position
 */
void	transform_hit_pt(t_rt *rt, t_obj res)
{
	// translate ray to world center
	rt->hit.at = subtract_vec(rt->hit.at, res.bbox_center);
	
	// rotate
	rt->hit.at = quaternion_rotate_adv(rt->hit.at, res.rotate, 1);
	rt->hit.surf_norm = quaternion_rotate_adv(rt->hit.surf_norm, res.rotate, 1);
	
	// translate back to obj ori position
	rt->hit.at = subtract_vec(rt->hit.at, mult_vec_scalar(res.bbox_center, -1));

}

void	transform_bbox(t_rt *rt, t_uint index)
{
	copy_bbox(rt->obj[index].bbox, rt->obj[index].bbox_ori);

	aabb_translate(rt->obj[index], rt->obj[index].bbox, mult_vec_scalar(rt->obj[index].bbox_center, -1));
	aabb_rotate(rt->obj[index], rt->obj[index].bbox);
	aabb_translate(rt->obj[index], rt->obj[index].bbox, rt->obj[index].bbox_center);
}

void	update_cam_pos(t_rt *rt, int keycode)
{
	if (rt->sel.type != SEL_CAMERA && keycode != KEY_R)
		return ;
	reset_cam(rt, keycode);
	rt->camera.pos = add_vec(rt->camera.ori, rt->camera.transform.translate);
	rt->camera.vup = quaternion_rotate_adv(rt->camera.vup_ori, rt->camera.transform.rotate, 0);
	rt->camera.lookat = quaternion_rotate_adv(rt->camera.lookat_ori, rt->camera.transform.rotate, 0);
	// /*debug*/debug_print_vec("rot_vup", rt->camera.vup);
	// /*debug*/debug_print_vec("orient_rot", rt->camera.lookat);
	rt->ray.orig = rt->camera.pos;
}
