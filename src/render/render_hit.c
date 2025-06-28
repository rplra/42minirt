/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 13:45:13 by hsim              #+#    #+#             */
/*   Updated: 2025/06/28 19:11:41 by hsim             ###   ########.fr       */
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
float	has_hit_sphere(t_obj obj, t_ray ray)
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
	if (tmp <= 0 || tmp >= 4294967295.0)
		tmp = (n[B] + sqrt(discriminant)) / n[A];
	/*debug*/printf("has_hit_sphere:%f %f %f\n", tmp, discriminant, INFINITY);

	if (tmp <= 0 || tmp >= 4294967295.0)
		return (-1);
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
t_obj	*hit(t_rt *vars, t_ray ray, t_vec3 *surf_norm, t_vec3 *at)
{
	float		t;
	t_obj		*tmp;
	t_obj		*res;
	float		min;
	float		(*has_hit[3])(t_obj, t_ray);
	t_vec3      (*get_surf_norm[3])(t_ray, t_obj, float);

	init_hit_func(has_hit);
	init_surf_norm(get_surf_norm);
	min = 2147483647.0;
	res = NULL;
	tmp = vars->obj;
	while (tmp != NULL)
	{
		// /*debug*/printf("id:%d\n", x);
		t = has_hit[tmp->type](*tmp, ray);
		// /*debug*/printf("has_hit_sphere:t:%f\n", t);
		if (t > 0.001 && t <= min) // if its new min, keep in record
		{
			res = tmp;
			min = t;
			// can split this out to end
			*at = add_vec(ray.orig, mult_vec_scalar(ray.vector, min));
			*surf_norm = get_surf_norm[res->type](ray, *res, min);
		}
		tmp = tmp->next;
	}
	return (res);
}
