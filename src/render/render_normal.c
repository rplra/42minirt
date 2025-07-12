/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:11:57 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/11 09:43:21 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * 3d point along a vector ray
 * vec = origin + (t * direction)
 */
t_vec3	point_at(float t, t_ray ray)
{
	return (add_vec(ray.orig, mult_vec_scalar(ray.vector, t)));
}

/*
 * checks if dot product is > 0,
 * if true, reverse the ray by multiply -1
 */
t_vec3	set_face_norm(t_ray ray, t_vec3 surf_norm)
{
	if (scalar_product(ray.vector, surf_norm) > 0)	//if pointing in same direction
		surf_norm = mult_vec_scalar(surf_norm, -1);	//reverse direction
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
	return (set_face_norm(ray, obj.quad.normal));
}

/*
 * calculates vector pt_ray -> sphere_center
 * if scalar_product of ray . surf_norm > 0, (means ray hits inner side)
 * reverse direction of surf_norm if so
 * returns a surf_norm in unit vector
 */
t_vec3	get_surf_norm_sph(t_ray ray, t_obj obj, float t)
{
	t_vec3	pt_ray;
	t_vec3	surf_norm;

	// also known as set_face_normal
	pt_ray = add_vec(ray.orig, mult_vec_scalar(ray.vector, t)); // .at
	surf_norm = subtract_vec(pt_ray, obj.sph.pos);
	surf_norm = unit_vec3(surf_norm);
	// so, reverse surf_norm if so
	surf_norm = set_face_norm(ray, surf_norm);
	return (surf_norm);
}

t_vec3	get_surf_norm_cyl(t_ray ray, t_obj obj, float t)
{
	t_vec3	pt_ray;
	t_vec3	base_from_intersection;
	float	distance_to_axis;
	t_vec3	axis_point;
	t_vec3	surf_norm;

	// intersection point at ray
	pt_ray = add_vec(ray.orig, mult_vec_scalar(ray.vector, t));
	// vector from base intersection to point
	base_from_intersection = subtract_vec(pt_ray, obj.cyl.pos);
	// projection onto axis to see how far along axis the point is
	distance_to_axis = scalar_product(base_from_intersection, obj.cyl.axis);
	// bottom cap
	if (distance_to_axis <= 0)
		return (mult_vec_scalar(obj.cyl.axis, -1));
	// top cap
	else if (distance_to_axis >= obj.cyl.height)
		return (obj.cyl.axis);
	// sides
	else
	{
		axis_point = add_vec(obj.cyl.pos, mult_vec_scalar(obj.cyl.axis, distance_to_axis));
		surf_norm = subtract_vec(pt_ray, axis_point);
		return (unit_vec3(surf_norm));
	}
	// flip normal if facing the same direction as the ray
	if (scalar_product(ray.vector, surf_norm) > 0)
		surf_norm = mult_vec_scalar(surf_norm, -1);
	return (surf_norm);
}

// normalize cylinder
/* t_vec3	get_cylinder_normal(t_vec3 point, t_cylinder *cy)
{
	t_vec3	base_from_intersection;
	float	distance_to_axis;
	t_vec3	axis_point;
	t_vec3	normal;

	base_from_intersection = subtract_vec(point, cy->axis);
	distance_to_axis = scalar_product(base_from_intersection, cy->axis);
	// check if the intersection happens at the bottom cap
	if (distance_to_axis <= 0)
		return (mult_vec_scalar(cy->axis, -1));
	// check if the intersection happens at the top cap
	else if (distance_to_axis >= cy->height)
		return (cy->axis);
	// else, intersection happens at the sides of the cylinder
	else
	{
		axis_point = add_vec(cy->pos, mult_vec_scalar(cy->axis, distance_to_axis));
		normal = subtract_vec(point, axis_point);
		return (unit_vec3(normal));
	}
} */