/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit_cy2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:16:30 by hsim              #+#    #+#             */
/*   Updated: 2025/08/17 17:05:23 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * child function in check_hit_body
 * returns cyl_height considering its axis
 * using dot(pos, axis)*axis to mask the correct axis value
 * eg if axis=(0,1,0), cyl_axis_pos returns y value in cyl position
 * 
 * eg. if axis=(0,1,0) (y-axis), will be
 * cyl_height.max = cyl.pos.y + (cyl.axis.y * cyl.height / 2)
 * cyl_height.min = cyl.pos.y - (cyl.axis.y * cyl.height / 2)
 */
t_interval	get_cyl_axis_height(t_cy cyl)
{
	t_vec3		cyl_axis_pos;
	t_interval	cyl_height;

	cyl_axis_pos = mult_vec_scalar(cyl.axis, scalar_product(cyl.pos, cyl.axis));
	// /*debug*/debug_print_vec("ori_axis_h", cyl.axis_height);
	// /*debug*/debug_print_vec("new_axis_h", cyl_axis_height);
	cyl_height.min = scalar_product(cyl.axis,
			subtract_vec(cyl_axis_pos, cyl.axis_height));
	cyl_height.max = scalar_product(cyl.axis,
			add_vec(cyl_axis_pos, cyl.axis_height));
	return (cyl_height);
}

/*
 * child function in check_hit_body
 * returns point on surface correspondiing to the cyl_axis
 * eg. if cyl_axis=(0,1,0) , point_on_surf=(3,2,1) returns 2 (value of y)
 */
void	get_point_on_surf(t_cy cyl, t_ray ray, float t[2], float res[2])
{
	t_vec3		pt_ray[2];

	pt_ray[0] = add_vec(ray.orig, mult_vec_scalar(ray.vector, t[0]));
	pt_ray[1] = add_vec(ray.orig, mult_vec_scalar(ray.vector, t[1]));
	res[0] = scalar_product(cyl.axis, pt_ray[0]);
	res[1] = scalar_product(cyl.axis, pt_ray[1]);
}

float	check_hit_body(t_rt *rt, int i, t_ray ray, float t[2])
{
	float		pt_hit[2];
	t_interval	cyl_ht;

	cyl_ht = get_cyl_axis_height(rt->obj[i].cyl);
	get_point_on_surf(rt->obj[i].cyl, ray, t, pt_hit);
// 	if (((pt_hit[0] > cyl_height.min && pt_hit[0] < cyl_height.max) ||
// (pt_hit[1] > cyl_height.min && pt_hit[1] < cyl_height.max)))
	if (pt_hit[0] > cyl_ht.min + EPSILON && pt_hit[0] < cyl_ht.max + EPSILON)
	{
		// if (t[1] < t[0])
			// /*debug*/printf("body_small! %f > %f\n", t[0], t[1]);
		return (t[0]);
	}
	return (-1);
}

static bool	t_intersect_body(float *t, t_interval ray_range, \
float n[3], float discriminant)
{
	if (*t <= ray_range.min || *t >= ray_range.max)
	{
		*t = (n[B] + sqrt(discriminant)) / n[A];
		if (*t <= ray_range.min || *t >= ray_range.max)
			return (0);
	}
	return (1);
}

/*
 * ray_to_center = subtract_vec(cyl.pos, ray.orig); // C-O
 * ray_to_center = subtract_vec(ray_to_center, hi_axis); // C-O - ((C-0).V)*V
 * ray_dir =  subtract_vec(ray.vector, mult_vec_scalar(cyl.axis,
		scalar_product(ray.vector, cyl.axis))); // d - (d.V)*V
*/

float	has_hit_body(t_cy cyl, t_interval ray_range, t_ray ray, float t[2])
{
	float	n[3];
	float	discriminant;
	t_vec3	ray_to_center;
	t_vec3	ray_dir;
	t_vec3	highlighted_axis;

	ray_to_center = subtract_vec(cyl.pos, ray.orig);
	highlighted_axis = mult_vec_scalar(cyl.axis,
			scalar_product(ray_to_center, cyl.axis));
	ray_to_center = subtract_vec(ray_to_center, highlighted_axis);
	ray_dir = subtract_vec(ray.vector, mult_vec_scalar(cyl.axis,
				scalar_product(ray.vector, cyl.axis)));
	n[A] = scalar_product(ray_dir, ray_dir);
	if (n[A] < EPSILON)
		return (-1);
	n[B] = scalar_product(ray_dir, ray_to_center);
	n[C] = scalar_product(ray_to_center, ray_to_center) - ft_square(cyl.rad);
	discriminant = ft_square(n[B]) - (n[A] * n[C]);
	if (discriminant < EPSILON)
		return (-1);
	t[0] = (n[B] - sqrt(discriminant)) / n[A];
	t[1] = (n[B] + sqrt(discriminant)) / n[A];
	if (!t_intersect_body(&t[0], ray_range, n, discriminant))
		return (-1);
	return (t[0]);
}

// float	has_hit_body(t_cy cyl, t_interval ray_range, t_ray ray, float t[2])
// {
// 	float	n[3];
// 	float	discriminant;
// 	t_vec3	ray_to_center;
// 	t_vec3	ray_dir;
// 	t_vec3	highlighted_axis;

// 	/* ************* get discriminant ************* */
// 	ray_to_center = subtract_vec(cyl.pos, ray.orig); // C-O
// 	highlighted_axis = mult_vec_scalar(cyl.axis, scalar_product(ray_to_center, cyl.axis));
// 	ray_to_center = subtract_vec(ray_to_center, highlighted_axis); // C-O - ((C-0).V)*V
//     ray_dir =  subtract_vec(ray.vector, mult_vec_scalar(cyl.axis, scalar_product(ray.vector, cyl.axis))); // d - (d.V)*V

// 	n[A] = scalar_product(ray_dir, ray_dir);
// 	if (n[A] < EPSILON)
// 		return (-1);
// 	n[B] = scalar_product(ray_dir, ray_to_center);
// 	n[C] = scalar_product(ray_to_center, ray_to_center) - \
// ft_square(cyl.rad);
// 	discriminant = ft_square(n[B]) - (n[A] * n[C]);
// 	if (discriminant < EPSILON)
// 		return (-1);

// 	/* ****************** get t ****************** */
// 	t[0] = (n[B] - sqrt(discriminant)) / n[A];
// 	t[1] = (n[B] + sqrt(discriminant)) / n[A];

// 	/* *************** if t intersects obj ************** */
// 	if (!t_intersect_body(&t[0], ray_range, n, discriminant))
// 		return (-1);
// 	// if (t[0] <= ray_range.min || t[0] >= ray_range.max)
// 	// {
// 	// 	t[0] = (n[B] + sqrt(discriminant)) / n[A];
// 	// 	if (t[0] <= ray_range.min || t[0] >= ray_range.max)
// 	// 		return (-1);
// 	// }
// 	return (t[0]);
// }
