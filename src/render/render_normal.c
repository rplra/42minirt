/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:11:57 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/22 13:07:45 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * brief: set surface normal at hit point to face against the incoming ray
 * why? so that we always have the norm to point toward light source
 * checks if dot product is > 0, (if pointing in same direction)
 * if true, reverse the ray by multiply -1 (reverse dir)
 */
t_vec3	set_face_norm(t_ray ray, t_vec3 surf_norm)
{
	(void)ray;
	if (scalar_product(ray.vector, surf_norm) > 0)
		surf_norm = mult_vec_scalar(surf_norm, -1);
	return (surf_norm);
}

/*
 * child function in hit
 * calls respective get_surf_norm function depending on object type
 */
void	init_surf_norm(t_vec3 (*get_surf_norm[])(t_ray, t_obj, float, t_uchar))
{
	get_surf_norm[PLANE] = get_surf_norm_plane;
	get_surf_norm[SPHERE] = get_surf_norm_sph;
	get_surf_norm[CYLINDER] = get_surf_norm_cyl;
}

t_vec3	get_surf_norm_plane(t_ray ray, t_obj obj, float t, t_uchar setting)
{
	(void)t;
	(void)setting;
	return (set_face_norm(ray, obj.plane.normal));
}

/*
 * calculates vector pt_ray -> sphere_center
 * if scalar_product of ray . surf_norm > 0, (means ray hits inner side)
 * reverse direction of surf_norm if so
 * returns a surf_norm in unit vector
 *
 * Formula: P-C
 * if dot(ray_dir, P-C) > 0,
 * invert the direction
 *
 * 1. get intersection point
 * 2. get the vect from centre of sphere to hit point > normalize
 * 3. set the norm to face light source ray
 */
t_vec3	get_surf_norm_sph(t_ray ray, t_obj obj, float t, t_uchar setting)
{
	t_vec3	pt_ray;
	t_vec3	surf_norm;

	(void)setting;
	pt_ray = add_vec(ray.orig, mult_vec_scalar(ray.vector, t));
	surf_norm = subtract_vec(pt_ray, obj.sph.pos);
	surf_norm = unit_vec3(surf_norm);
	surf_norm = set_face_norm(ray, surf_norm);
	return (surf_norm);
}

/*
 * renders 3d or flat based on identifier id
 * projects cyl_center to be parallel to hit_point
 * subtract P-C (same as sphere, but discard axis value), & normalize
 * if hit_pt=P, center=C
 * 1. subtract P-C
 * 2. get height: dot(axis, P-C)
 * 3. remove height: C = cyl_center + (cyl_axis * height)
 * 4. subtract P-new_C
 *
 * id = 1: renders 3D
 * else  : renders flat 2D
 */
t_vec3	get_surf_norm_cyl(t_ray ray, t_obj obj, float t, t_uchar setting)
{
	float	t2;
	t_vec3	pt_ray;
	t_vec3	p_to_c;
	t_vec3	surf_norm;

	pt_ray = add_vec(ray.orig, mult_vec_scalar(ray.vector, t));
	if (setting == 1)
	{
		p_to_c = subtract_vec(pt_ray, obj.cyl.pos);
		t2 = scalar_product(p_to_c, obj.cyl.axis);
		surf_norm = add_vec(obj.cyl.pos, mult_vec_scalar(obj.cyl.axis, t2));
		surf_norm = subtract_vec(pt_ray, surf_norm);
		surf_norm = unit_vec3(surf_norm);
		return (surf_norm);
	}
	return (set_face_norm(ray, obj.cyl.axis));
}
