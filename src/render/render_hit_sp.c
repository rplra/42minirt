/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit_sp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:54:15 by hsim              #+#    #+#             */
/*   Updated: 2025/08/22 13:05:41 by rraja-az         ###   ########.fr       */
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
bool	has_hit_sphere(t_rt *rt, int index, t_interval ray_range, t_ray ray)
{
	float		n[3];
	float		t;
	float		discriminant;
	t_vec3		ray_to_center;

	ray_to_center = subtract_vec(rt->obj[index].sph.pos, ray.orig);
	n[A] = scalar_product(ray.vector, ray.vector);
	n[B] = scalar_product(ray.vector, ray_to_center);
	n[C] = scalar_product(ray_to_center, ray_to_center) - \
(rt->obj[index].sph.rad * rt->obj[index].sph.rad);
	discriminant = ft_square(n[B]) - (n[A] * n[C]);
	if (discriminant < 0)
		return (0);
	t = (n[B] - sqrt(discriminant)) / n[A];
	if (t <= ray_range.min || t >= ray_range.max)
	{
		t = (n[B] + sqrt(discriminant)) / n[A];
		if (t <= ray_range.min || t >= ray_range.max)
			return (0);
	}
	update_hit_rec(rt, index, ray, t);
	return (1);
}
