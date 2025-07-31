/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:11:57 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/29 09:09:30 by hsim             ###   ########.fr       */
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
	(void) ray;
	if (scalar_product(ray.vector, surf_norm) > 0)	//if pointing in same direction
		surf_norm = mult_vec_scalar(surf_norm, -1);	//reverse direction
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
	(void) t;
	(void) setting;
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
 */
t_vec3	get_surf_norm_sph(t_ray ray, t_obj obj, float t, t_uchar setting)
{
	t_vec3	pt_ray;
	t_vec3	surf_norm;
	(void) setting;

	// also known as set_face_normal
	pt_ray = add_vec(ray.orig, mult_vec_scalar(ray.vector, t)); // .at
	surf_norm = subtract_vec(pt_ray, obj.sph.pos);
	surf_norm = unit_vec3(surf_norm);
	// so, reverse surf_norm if so
	surf_norm = set_face_norm(ray, surf_norm);
	return (surf_norm);
}

// cyl cap test
// t_vec3	get_surf_norm_cyl(t_ray ray, t_obj obj, float t, t_uchar setting)
// {
// 	(void) t;
// 	(void) ray;
// 	(void) setting;
// 	// t_vec3	axis = mult_vec_scalar(obj.cyl.axis, -1);
// 	// return (set_face_norm(ray, axis));
// 	return (set_face_norm(ray, obj.cyl.axis));
// }

/*
 * renders 3d or flat based on identifier id
 * projects cyl_center to be parallel to hit_point
 * then, subtract P-C (same as sphere), & normalize
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

	t_interval cyl_height = get_cyl_axis_height(obj.cyl);

	t2 = scalar_product(pt_ray, obj.cyl.axis);
	if (t2 >= cyl_height.max - EPSILON)
		return (obj.cyl.axis);
	return (mult_vec_scalar(obj.cyl.axis, -1));

	// return (set_face_norm(ray, obj.cyl.axis));
}

// t_vec3	get_surf_norm_cyl(t_ray ray, t_obj obj, float t, t_uchar setting)
// {
// 	float	t2;
// 	t_vec3	pt_ray;
// 	t_vec3	p_to_c;
// 	t_vec3	surf_norm;

// 	if (setting == 1)
// 	{
// 		pt_ray = add_vec(ray.orig, mult_vec_scalar(ray.vector, t));
// 		p_to_c = subtract_vec(pt_ray, obj.cyl.pos);
		
// 		t2 = scalar_product(p_to_c, obj.cyl.axis);
// 		surf_norm = add_vec(obj.cyl.pos, mult_vec_scalar(obj.cyl.axis, t2));
// 		surf_norm = subtract_vec(pt_ray, surf_norm);
// 		surf_norm = unit_vec3(surf_norm);
// 		return (surf_norm);
// 	}
// 	return (set_face_norm(ray, obj.cyl.axis));
// }

// t_vec3	get_surf_norm_cyl(t_ray ray, t_obj obj, float t)
// {
// 	t_vec3		pt_ray;
// 	t_vec3		surf_norm;
// 	t_interval	cyl_axis;
// 	float		alpha;
// 	float		beta;


// 	// pt_ray = add_vec(ray.orig, mult_vec_scalar(ray.vector, t)); // .at
// 	// pt_ray = new_vec3(pt_ray.x, 0, pt_ray.z);	//cylinder infinite on y
	
// 	pt_ray = add_vec(ray.orig, mult_vec_scalar(ray.vector, t)); // .at
// 	// alpha = scalar_product(pt_ray, unit_vec3(obj.cyl.coord[X]));
// 	// beta = scalar_product(pt_ray, unit_vec3(obj.cyl.coord[Y]));

// 	cyl_axis = get_cyl_axis_height(obj.cyl);
// 	// cyl_axis.min = obj.cyl.pos.y - (obj.cyl.axis.y * (obj.cyl.height / 2));
// 	// cyl_axis.max = obj.cyl.pos.y + (obj.cyl.axis.y * (obj.cyl.height / 2));

// 	float dist = ft_square(alpha) + ft_square(beta);	//x sq + 0 + z sq = r sq

// 	if ((dist <= ft_square(0.5) && pt_ray.y >= cyl_axis.max - EPSILON) || \
// (dist <= ft_square(0.5) && pt_ray.y <= cyl_axis.min + EPSILON))
// 	{
// 		/*debug*/printf("surf_norm cap!\n");
// 		return (set_face_norm(ray, obj.cyl.axis));
// 	}

// 	/* ************************************************************** */
// 	//n= <normal>, obj_center - pt_ray
// 	surf_norm = subtract_vec(pt_ray, obj.cyl.pos);
// 	surf_norm = unit_vec3(surf_norm);
// 	// /*debug*/debug_print_vec("surf_norm_cyl", surf_norm);
// 	// so, reverse surf_norm if so
// 	surf_norm = set_face_norm(ray, surf_norm);
// 	/*debug*/printf("surf_norm_body\n");
// 	return (surf_norm);
// }

//lyara
// t_vec3	get_surf_norm_cyl(t_ray ray, t_obj obj, float t)
// {
// 	t_vec3	pt_ray;
// 	t_vec3	base_from_intersection;
// 	float	distance_to_axis;
// 	t_vec3	axis_point;
// 	t_vec3	surf_norm;

// 	// intersection point at ray
// 	pt_ray = add_vec(ray.orig, mult_vec_scalar(ray.vector, t));
// 	// vector from base intersection to point
// 	base_from_intersection = subtract_vec(pt_ray, obj.cyl.pos);
// 	// projection onto axis to see how far along axis the point is
// 	distance_to_axis = scalar_product(base_from_intersection, obj.cyl.axis);
// 	// bottom cap
// 	if (distance_to_axis <= 0)
// 		return (mult_vec_scalar(obj.cyl.axis, -1));
// 	// top cap
// 	else if (distance_to_axis >= obj.cyl.height)
// 		return (obj.cyl.axis);
// 	// sides
// 	else
// 	{
// 		axis_point = add_vec(obj.cyl.pos, mult_vec_scalar(obj.cyl.axis, distance_to_axis));
// 		surf_norm = subtract_vec(pt_ray, axis_point);
// 		return (unit_vec3(surf_norm));
// 	}
// 	// flip normal if facing the same direction as the ray
// 	surf_norm = set_face_norm(ray, surf_norm);
// 	// if (scalar_product(ray.vector, surf_norm) > 0)
// 	// 	surf_norm = mult_vec_scalar(surf_norm, -1);
// 	return (surf_norm);
// }

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