/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:18:16 by hsim              #+#    #+#             */
/*   Updated: 2025/08/17 14:49:38 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_col	emitted(t_rt *rt, t_uchar ray_bounce, t_ray ray, t_obj *obj)
{
	if (obj->material.type == LIGHT)
	{
		if (rt->b_show_light == 0 && ray_bounce == rt->camera.ray_bounce)
			return (bg_color(*rt, ray));
		return (obj->material.albedo);
	}
	return (new_vec3(0.01, 0.01, 0.01));
}

bool	scatter(t_rt *rt, t_ray ray, t_ray *bounce, t_uint *seed)
{
	t_obj	*obj_hit;

	obj_hit = &rt->obj[rt->hit.index];
	if (obj_hit->material.type == LIGHT)
		return (0);
	else if (obj_hit->material.type == METAL)
	{
		bounce->vector = mat_metal(ray.vector, rt->hit.surf_norm,
				obj_hit->material.fuzz, seed);
		if (scalar_product(bounce->vector, rt->hit.surf_norm) <= 0)
			return (0);
	}
	else if (obj_hit->material.type == DIFFUSE)
		bounce->vector = mat_lambertian(rt->hit.surf_norm, seed);
	return (1);
}

/* ray_color v3, objs as light */
t_vec3	ray_color(t_rt *rt, t_ray ray, t_uchar ray_bounce, t_uint *seed)
{
	t_obj	*obj_hit;
	t_ray	bounce;
	t_vec3	emitted_col;
	t_vec3	bounced_col;

	if (ray_bounce <= 0)
		return (new_vec3(0, 0, 0));
	obj_hit = hit(rt, new_interval(0.00001f, 2147483647.0), ray);
	if (obj_hit == NULL)
		return (bg_color(*rt, ray));
	bounce.orig = rt->hit.at;
	emitted_col = emitted(rt, ray_bounce, ray, obj_hit);
	if (!scatter(rt, ray, &bounce, seed))
		return (emitted_col);
	bounced_col = (mult_vec(ray_color(rt, bounce, ray_bounce - 1, seed),
				obj_hit->material.albedo));
	return (add_vec(emitted_col, bounced_col));
}
