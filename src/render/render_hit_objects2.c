/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit_objects2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:47:34 by hsim              #+#    #+#             */
/*   Updated: 2025/07/25 14:50:26 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	check_hit_body(t_rt *rt, int i, t_ray ray, float t[2])
{
	float		pt_hit[2];
	t_interval	cyl_height;

	cyl_height = get_cyl_axis_height(rt->obj[i].cyl);
	get_point_on_surf(rt->obj[i].cyl, ray, t, pt_hit);
// 	if (((pt_hit[0] > cyl_height.min && pt_hit[0] < cyl_height.max) || \
// (pt_hit[1] > cyl_height.min && pt_hit[1] < cyl_height.max)))
	if (pt_hit[0] > cyl_height.min + EPSILON && pt_hit[0] < cyl_height.max + EPSILON)
	{
		if (t[1] < t[0])
			/*debug*/printf("body_small! %f > %f\n", t[0], t[1]);
		return (t[0]);
	}
	return (-1);
}

float	has_hit_body(t_cylinder cyl, t_interval ray_range, t_ray ray, float t[2])
{
	float	n[3];
	float	discriminant;
	t_vec3	ray_to_center;
	t_vec3	ray_dir;
	t_vec3	highlighted_axis;

	/* ************* get discriminant ************* */
	ray_to_center = subtract_vec(cyl.pos, ray.orig); // C-O
	highlighted_axis = mult_vec_scalar(cyl.axis, scalar_product(ray_to_center, cyl.axis));
	ray_to_center = subtract_vec(ray_to_center, highlighted_axis); // C-O - ((C-0).V)*V
    ray_dir =  subtract_vec(ray.vector, mult_vec_scalar(cyl.axis, scalar_product(ray.vector, cyl.axis))); // d - (d.V)*V
	
	n[A] = scalar_product(ray_dir, ray_dir);
	if (n[A] < EPSILON)
		return (-1);
	n[B] = scalar_product(ray_dir, ray_to_center);
	n[C] = scalar_product(ray_to_center, ray_to_center) - \
ft_square(cyl.rad);
	discriminant = ft_square(n[B]) - (n[A] * n[C]);
	if (discriminant < EPSILON)
		return (-1);

	/* ****************** get t ****************** */
	t[0] = (n[B] - sqrt(discriminant)) / n[A];
	t[1] = (n[B] + sqrt(discriminant)) / n[A];

	/* *************** if t intersects obj ************** */
	if (t[0] <= ray_range.min || t[0] >= ray_range.max)
	{
		t[0] = (n[B] + sqrt(discriminant)) / n[A];
		if (t[0] <= ray_range.min || t[0] >= ray_range.max)
			return (-1);
	}
	return (t[0]);
}

/*
 * checks if ray to point falls within the cylinder space
 * formula modifies from <Raytracing in One Weekend>, sphere intersection formula
 * just modified y to be assigned to 0
 * 
 * Reference:
 * https://raytracing.github.io/books/RayTracingInOneWeekend.html
 * #addingasphere/ray-sphereintersection
 */
bool	has_hit_cylinder(t_rt *rt, int index, t_interval ray_range, t_ray ray)
{
	float	t[2];
	float	hit_body = 0;
	float	hit_cap = 0;

	hit_body = has_hit_body(rt->obj[index].cyl, ray_range, ray, t);
	if (hit_body != -1)
		hit_body = check_hit_body(rt, index, ray, t);
	hit_cap = has_hit_cap(rt, index, ray_range, ray);

	if (hit_body == -1 && hit_cap == -1)
		return (0);
	/* *************************** if both ok *************************** */
	if (hit_body != -1 && hit_cap != -1)
	{
		/*debug*/printf("has_hit_cyl:%d: %f < %f\n", index, hit_cap, hit_body);
		/*debug*/debug_print_vec("has_hit_cyl: ray.orig", ray.orig);
		/*debug*/debug_print_vec("has_hit_cyl: ray.dir", ray.vector);
		if (hit_cap < hit_body)
		{
			/*debug*/printf("has_hit_cyl:s\n");
			// /*debug*/printf("has_hit_cyl:%d: %f < %f\n", index, hit_cap, hit_body);
			update_hit_rec(rt, index, ray, hit_cap);
			rt->hit.setting = 0;
			return (1);
		}
	// 	update_hit_rec(rt, index, ray, t[0]);
	// 	rt->hit.setting = 1;
		return (0);
	}

	/* *************************** cap ok *************************** */
	// if (hit_cap != -1 && hit_body == -1)
	if (hit_cap != -1)
	{
		// /*debug*/printf("has_hit_cyl: %f < %f\n", hit_cap, hit_body);
		update_hit_rec(rt, index, ray, hit_cap);
		rt->hit.setting = 0;
		return (1);
	}

	/* *************************** body ok *************************** */
	// if (hit_body != -1 && hit_cap == -1)
	if (hit_body != -1)
	{
		// if (hit_cap)
			// /*debug*/printf("has_hit_cyl:body: %f < %f\n", hit_cap, hit_body);
		update_hit_rec(rt, index, ray, hit_body);
		rt->hit.setting = 1;
		return (1);
	}

	return (0);
}
