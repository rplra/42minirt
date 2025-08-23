/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit_cy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:47:34 by hsim              #+#    #+#             */
/*   Updated: 2025/08/23 16:29:35 by hsim             ###   ########.fr       */
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

static int	handle_cylinder_hits(t_rt *rt, int index, t_ray ray)
{
	if (rt->hit.body == -1 && rt->hit.cap == -1)
		return (0);
	if (rt->hit.body != -1 && rt->hit.cap != -1)
	{
		if (rt->hit.cap < rt->hit.body)
		{
			rt->hit.setting = 0;
			update_hit_rec(rt, index, ray, rt->hit.cap);
			return (1);
		}
		return (0);
	}
	if (rt->hit.cap != -1)
	{
		rt->hit.setting = 0;
		update_hit_rec(rt, index, ray, rt->hit.cap);
		return (1);
	}
	if (rt->hit.body != -1)
	{
		rt->hit.setting = 1;
		update_hit_rec(rt, index, ray, rt->hit.body);
		return (1);
	}
	return (0);
}

bool	has_hit_cy(t_rt *rt, int index, t_interval ray_range, t_ray ray)
{
	float	t[2];

	if (rt->obj[index].b_rotate == 1)
		ray = transform_ray(rt->obj[index], ray);
	rt->hit.body = has_hit_body(rt->obj[index].cyl, ray_range, ray, t);
	if (rt->hit.body != -1)
		rt->hit.body = check_hit_body(rt, index, ray, t);
	rt->hit.cap = has_hit_cap(rt, index, ray_range, ray);
	return (handle_cylinder_hits(rt, index, ray));
}
