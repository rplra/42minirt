/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:54:15 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/07 17:45:10 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * child function in hit
 * calls respective has_hit function depending on object type
 */
void	init_hit_func(float (*has_hit[])())
{
	has_hit[PLANE] = has_hit_plane;
	has_hit[SPHERE] = has_hit_sphere;
	has_hit[CYLINDER] = has_hit_cylinder;
}

// hsim to replace with hers (this is temp func)
float	has_hit_plane(t_obj obj, t_interval ray_range, t_ray ray)
{
	// to complete
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
float	has_hit_sphere(t_obj obj, t_interval ray_range, t_ray ray)
{
	float		n[3];
	float		discriminant;
	float		tmp;
	t_vec3		ray_to_center;

	ray_to_center = subtract_vec(obj.sph.pos, ray.orig);
	n[A] = scalar_product(ray.vector, ray.vector) + EPSILON;
	n[B] = scalar_product(ray.vector, ray_to_center) + EPSILON;
	n[C] = scalar_product(ray_to_center, ray_to_center) - \
(obj.sph.rad * obj.sph.rad) + EPSILON;

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

float	has_hit_cylinder(t_obj obj, t_interval ray_range, t_ray ray)
{
	// to complete
}

