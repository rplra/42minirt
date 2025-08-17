/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit_cy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:47:34 by hsim              #+#    #+#             */
/*   Updated: 2025/08/17 15:42:58 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

	if (rt->obj[index].b_rotate == 1)
		ray = transform_ray(rt->obj[index], ray);

	hit_body = has_hit_body(rt->obj[index].cyl, ray_range, ray, t);
	if (hit_body != -1)
		hit_body = check_hit_body(rt, index, ray, t);
	hit_cap = has_hit_cap(rt, index, ray_range, ray);

	if (hit_body == -1 && hit_cap == -1)
		return (0);
	/* *************************** if both ok *************************** */
	if (hit_body != -1 && hit_cap != -1)
	{
		/* ********************* prioritize cyl_body ******************** */
		if (hit_cap < hit_body)
		{
			// /*debug*/printf("has_hit_cyl:s\n");
			update_hit_rec(rt, index, ray, hit_cap);
			rt->hit.setting = 0;
			return (1);
		}
	// 	update_hit_rec(rt, index, ray, t[0]);
	// 	rt->hit.setting = 1;
		return (0);
	}

	/* *************************** cap ok *************************** */
	if (hit_cap != -1)
	{
		// /*debug*/printf("has_hit_cyl: %f < %f\n", hit_cap, hit_body);
		update_hit_rec(rt, index, ray, hit_cap);
		rt->hit.setting = 0;
		return (1);
	}

	// /* *************************** body ok *************************** */
	if (hit_body != -1)
	{
		update_hit_rec(rt, index, ray, hit_body);
		rt->hit.setting = 1;
		return (1);
	}
	return (0);
}
