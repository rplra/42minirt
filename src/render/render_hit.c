/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 13:45:13 by hsim              #+#    #+#             */
/*   Updated: 2025/06/30 21:38:08 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * check all sph objects to see which is the closest hit
 * 
 * derived from quadratic equation discriminant formula
 * b sq - 4ac >= 0 (hit sphere)
 * b sq - 4ac < 0 (doesnt hit sphere)
 * full formula:
 * [-b +- sqrt(b sq - 4ac)]  /  2a
 * shortened:
 * [b +- sqrt(b sq - ac)]  /  a
 * 
 * res = discriminant
 * expanded frm sphere equation x sq + y sq + z sq - r sq = 0
 * vector from point P on ray -> sphere center C
 * 
 * returns the closest point if there are 2 roots
 * unsigned int max: 4294967295 as limit num
 * 
 * formula expansion reference:
 * https://raytracing.github.io/books/RayTracingInOneWeekend.html
 * https://youtu.be/ebzlMOw79Yw?si=8SXTPsEcSUtwft71
 */
float	has_hit_sphere(t_obj obj, t_interval ray_range, t_ray ray)
{
	float		n[3];
	float		discriminant;
	float		tmp;
	t_vec3		ray_to_center;

	ray_to_center = subtract_vec(obj.sph.orig, ray.orig);
	n[A] = scalar_product(ray.vector, ray.vector) + EPS;
	n[B] = scalar_product(ray.vector, ray_to_center) + EPS;
	n[C] = scalar_product(ray_to_center, ray_to_center) - \
(obj.sph.rad * obj.sph.rad) + EPS;

	discriminant = (n[B] * n[B]) - (n[A] * n[C]);
	if (discriminant < 0)
		return (-1);
	tmp = (n[B] - sqrt(discriminant)) / n[A];
	if (tmp <= ray_range.min || tmp >= ray_range.max) //0 to 4294967295
	{
		tmp = (n[B] + sqrt(discriminant)) / n[A];
		if (tmp <= ray_range.min || tmp >= ray_range.max)
			return (-1);
	}
	/*debug*/printf("has_hit_sphere:%f %f\n", tmp, discriminant);
	return (tmp);
}

/*
 * child function in hit
 * calls respective has_hit function depending on object type
 */
void	init_hit_func(float (*has_hit[])())
{
	has_hit[SPHERE] = has_hit_sphere;
}

/*
 * child function in hit
 * calls respective get_surf_norm function depending on object type
 */
void	init_surf_norm(t_vec3 (*get_surf_norm[])(t_ray, t_obj, float))
{
	get_surf_norm[SPHERE] = get_surf_norm_sph;
}

/*
 * child function in ray_color
 * checks if ray hits any surface
 * returns the closest point ray hits
 * at = origin + (t * direction)
 */
// t_obj	*hit(t_rt *vars, t_interval ray_range, t_ray ray, t_vec3 *at)
t_obj	*hit(t_rt *vars, t_interval ray_range, t_ray ray)
{
	float		t;
	t_obj		*tmp;
	t_obj		*res;
	float		min;
	float		(*has_hit[3])(t_obj, t_interval, t_ray);
	t_vec3      (*get_surf_norm[3])(t_ray, t_obj, float);

	init_hit_func(has_hit);
	init_surf_norm(get_surf_norm);
	min = ray_range.max;
	res = NULL;
	tmp = vars->obj;
	while (tmp != NULL)
	{
		// /*debug*/printf("id:%d\n", x);
		t = has_hit[tmp->type](*tmp, ray_range, ray); //this returns t value only, more like get_root
		// /*debug*/printf("has_hit_sphere:t:%f\n", t);
		if (t > ray_range.min && t <= min) // if its new min, keep in record
		{
			res = tmp;
			min = t;
			vars->rec.t = t; //hit hittable
			// can split this out to end (has_hit_sphere)
			vars->rec.at = add_vec(ray.orig, mult_vec_scalar(ray.vector, min)); //min=t
			vars->rec.surf_norm = get_surf_norm[res->type](ray, *res, min); //min=t
		}
		tmp = tmp->next;
	}
	return (res);
}

// t_obj	*hit(t_rt *vars, t_ray ray, t_vec3 *surf_norm, t_vec3 *at)
// {
// 	float		t;
// 	t_obj		*tmp;
// 	t_obj		*res;
// 	float		min;
// 	float		(*has_hit[3])(t_obj, t_ray);
// 	t_vec3      (*get_surf_norm[3])(t_ray, t_obj, float);

// 	init_hit_func(has_hit);
// 	init_surf_norm(get_surf_norm);
// 	min = 2147483647.0;
// 	res = NULL;
// 	tmp = vars->obj;
// 	while (tmp != NULL)
// 	{
// 		// /*debug*/printf("id:%d\n", x);
// 		t = has_hit[tmp->type](*tmp, ray);
// 		// /*debug*/printf("has_hit_sphere:t:%f\n", t);
// 		if (t > 0.001 && t <= min) // if its new min, keep in record
// 		{
// 			res = tmp;
// 			min = t;
// 			// can split this out to end
// 			*at = add_vec(ray.orig, mult_vec_scalar(ray.vector, min));
// 			*surf_norm = get_surf_norm[res->type](ray, *res, min);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (res);
// }

/* child function in hit_aabb */
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

/* hit function for bounding_box aabb */
int	hit_aabb(t_ray r, t_interval ray_t, t_interval bbox[3])
{
	int		axis;
	float	axis_inv; //inverse axis, adinv
	float	ray_vec[3];
	float	ray_orig[3];
	float	t[2];

	axis = -1;
	vec3_to_arr(r.vector, ray_vec);
	vec3_to_arr(r.orig, ray_orig);
	while (++axis < 3)
	{
		axis_inv = 1 / ray_vec[axis];
		t[0] = (bbox[axis].min - ray_orig[axis]) * axis_inv;
		t[1] = (bbox[axis].max - ray_orig[axis]) * axis_inv;
		assign_ray_t(t[0], t[1], &ray_t);
		if (ray_t.max <= ray_t.min)
			return (-1);
	}
	return (0);
}

int	hit_bvh(t_ray ray, t_interval ray_range, t_rt vars, t_interval bbox[3])
{
	t_obj *hit_left;
	t_obj *hit_right;

	if (!hit_aabb(ray, ray_range, bbox))
		return (0);

	// bool hit_left = left->hit(r, ray_t, rec); //call respective git function of obj
	// bool hit_right = right->hit(r, interval(ray_t.min, hit_left ? rec.t : ray_t.max), rec);

	hit_left = hit(&vars, ray_range, vars.ray);
	if (hit_left)
		hit_right = hit(&vars, new_interval(ray_range.min, vars.rec.t), ray);
	else
		hit_right = hit(&vars, new_interval(ray_range.min, ray_range.max), ray);
	if (hit_left || hit_right)
		return (1);
	return (0);
}
