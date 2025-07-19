/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:11:57 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/19 12:30:36 by rraja-az         ###   ########.fr       */
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
 * brief: set surface normal at hit point to face against the incoming ray 
 * why? so that we always have the norm to point toward light source
 * checks if dot product is > 0,
 * if true, reverse the ray by multiply -1
 */
t_vec3	set_face_norm(t_ray ray, t_vec3 surf_norm)
{
	if (scalar_product(ray.vector, surf_norm) > 0)
		surf_norm = mult_vec_scalar(surf_norm, -1);
	return (surf_norm);
}

/*
 * child function in hit
 * calls respective get_surf_norm function depending on object type
 */
void	init_surf_norm(t_vec3 (*get_surf_norm[])(t_ray, t_obj, float))
{
	get_surf_norm[PLANE] = get_surf_norm_plane;
	get_surf_norm[SPHERE] = get_surf_norm_sph;
	get_surf_norm[CYLINDER] = get_surf_norm_cyl;
}

t_vec3	get_surf_norm_plane(t_ray ray, t_obj obj, float t)
{
	(void) t;
	return (set_face_norm(ray, obj.plane.normal));
}

/*
 * calculates vector pt_ray -> sphere_center
 * if scalar_product of ray . surf_norm > 0, (means ray hits inner side)
 * reverse direction of surf_norm if so
 * returns a surf_norm in unit vector
 * 
 * 1. get intersection point
 * 2. get the vect from centre of sphere to hit point > normalize
 * 3. set the norm to face light source ray
 */
t_vec3	get_surf_norm_sph(t_ray ray, t_obj obj, float t)
{
	t_vec3	pt_ray;
	t_vec3	surf_norm;


	pt_ray = add_vec(ray.orig, mult_vec_scalar(ray.vector, t)); // .at
	surf_norm = subtract_vec(pt_ray, obj.sph.pos);
	surf_norm = unit_vec3(surf_norm);
	surf_norm = set_face_norm(ray, surf_norm);
	return (surf_norm);
}

/*
 * 1. get intersection point
 * 2. get the vect from base centre to hit point > get distance
 * 3. check distance against which surface it hits 
 * 	  (<= 0 is bottom, >= ht is top, else sides)
 * 4. set the norm to face light source ray
 */
t_vec3	get_surf_norm_cyl(t_ray ray, t_obj obj, float t)
{
	t_vec3	pt_ray;
	t_vec3	base_from_intersection;
	float	distance_to_axis;
	t_vec3	axis_point;
	t_vec3	surf_norm;

	pt_ray = add_vec(ray.orig, mult_vec_scalar(ray.vector, t));
	base_from_intersection = subtract_vec(pt_ray, obj.cyl.pos); 
	distance_to_axis = scalar_product(base_from_intersection, obj.cyl.axis);
	if (distance_to_axis <= 0)
		return (mult_vec_scalar(obj.cyl.axis, -1));
	else if (distance_to_axis >= obj.cyl.height)
		return (obj.cyl.axis);
	else
	{
		axis_point = add_vec(obj.cyl.pos, mult_vec_scalar(obj.cyl.axis, distance_to_axis));
		surf_norm = subtract_vec(pt_ray, axis_point);
		return (unit_vec3(surf_norm));
	}
	surf_norm = set_face_norm(ray, surf_norm);
	return (surf_norm);
}
