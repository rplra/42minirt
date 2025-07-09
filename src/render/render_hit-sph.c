/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit-sph.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 22:30:46 by hsim              #+#    #+#             */
/*   Updated: 2025/07/09 15:44:31 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	update_sph_rec(t_rt *vars, int index, t_ray ray, float t)
{
	t_vec3 (*get_surf_norm[3])(t_ray, t_obj, float);

	init_surf_norm(get_surf_norm);
	vars->rec.surf_norm = get_surf_norm[vars->obj[index].type](ray, vars->obj[index], t);			//if t>0
	vars->rec.at = add_vec(ray.orig, mult_vec_scalar(ray.vector, t));	//if t>0
	vars->rec.hit = &vars->obj[index];
	vars->rec.index = index;
	vars->rec.t = t;
}

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
bool	has_hit_sphere(t_rt *vars, int index, t_interval ray_range, t_ray ray)
{
	float		n[3];
	float		t;
	float		discriminant;
	t_vec3		ray_to_center;

	/*debug*/printf("has_hit index:%d\n", index);
	/* ************* get discriminant ************* */
	ray_to_center = subtract_vec(vars->obj[index].sph.orig, ray.orig);
	n[A] = scalar_product(ray.vector, ray.vector) + EPS;
	n[B] = scalar_product(ray.vector, ray_to_center) + EPS;
	n[C] = scalar_product(ray_to_center, ray_to_center) - \
(vars->obj[index].sph.rad * vars->obj[index].sph.rad) + EPS;
	discriminant = (n[B] * n[B]) - (n[A] * n[C]);
	if (discriminant < 0.001f)
		return (0);

	/* ****************** get t ****************** */
	t = (n[B] - sqrt(discriminant)) / n[A];
	if (t <= ray_range.min || t >= ray_range.max)
	{
		t = (n[B] + sqrt(discriminant)) / n[A];
		if (t <= ray_range.min || t >= ray_range.max)
			return (0);
	}
	/*debug*/printf("has_hit_sphere:%f %f\n", t, discriminant);

	update_sph_rec(vars, index, ray, t);
	return (1);
}
