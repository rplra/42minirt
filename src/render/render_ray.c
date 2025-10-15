/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:18:16 by hsim              #+#    #+#             */
/*   Updated: 2025/10/14 11:58:45 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* 
 * brief: checks light col that's emitted from a light object
 *
 * 1. check if obj is light
 * 2. if light is off and its the first camera ray bounce
 * 		> return the background col
 * 3. else return the light's col
 * 4. if obj is not light > just emit tiny light (almost black)
*/
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

/*  
 * brief: get the next bounced ray(metal / diffuse) based on given hit
 *
 * 1. get the obj being hit
 * 2. if light > dont scatter
 * 3. if metal (reflect) > reflects ray on surf norm
 * 4. if reflected ray is inwards > discard == absorb
 * 5. if diffuse > rand ray ard normal (simulate rough matte scattering)
 */
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

/* for debug purposes, returns surf_norm as color */
t_vec3	surf_norm_color(t_vec3 surf_norm)
{
	return (mult_vec_scalar(add_vec(surf_norm, new_vec3(1, 1, 1)), 0.5 * 255));
}

/* 
 * brief: recursively bounce rays to get global illumantion 
 *
 * 1. if no bounce left > return black col
 * 2. get the first obj being hit > if non > return background col
 * 3. set bounce pt at hit pt
 * 4. get emitted col (if there's light obj) 
 * 		> scatter > if not > return light col only
 * 5. recursively call ray_color with new bounce ray 
 * 		> decrement bounce count > multiple res with mat's albedo
 * 6. return light emitted + light gathered from other bounces
 */
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
