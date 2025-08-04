/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_mat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:18:16 by hsim              #+#    #+#             */
/*   Updated: 2025/08/03 19:06:37 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * brief: adds randomness to a reflected ray dir to simulate rough / fuzzy metal surface
 * child function in mat_metal
 * adjusts fuzziness on metal surface
 * fuzz range from 0 to 1
 * 
 * 1. check if fuzz value is too high, clamp it to max 1
 * 0 = mirror (perfect reflection), 1 = total rough (max randomness)
 * 2. calc fuzzy reflection >
 * bounce ray = perfect reflection direction
 * 3. generate rand vec in any direction
 * 4. scale rand by fuzz (how rough the surface is)
 * 5. add scaled rand to reflection direction
 */
t_vec3	simulate_fuzz(t_vec3 bounce_ray, float fuzz, t_uint *seed)
{
	t_vec3	res;

	if (fuzz > 1)
		fuzz = 1;
	res = add_vec(bounce_ray, mult_vec_scalar(rand_unit_vec(seed), fuzz));
	return (res);
}

/*
 * child function in ray_color
 *
 * brief: calcs reflection direction (like a mirror)
 * returns ray direction when surface material is metal/reflective
 * formula: in_ray - (2 * dot(in_ray, surf_norm) * surf_norm)
 * dot(...) is the magnitude, (scaling in_ray to surf_norm)
 * * surf_norm
 * = magnitude * dir
 * 
 * magnitude = bounce strength (how much light reflecs off the surface)
 * 
 * 1. calc dot product between incoming ray and surface normal
 * 2. times 2 to have it bounce directly back (perfect reflection)
 * 3. scales surf_norm by calculated magnitude; creates a vec of incoming ray projection onto normal
 * 4. subtract scaled normal from incoming ray; giving us reflection direction
 * 5. checks if surface has any roughness > if yes > simulate fuzz
 */
t_vec3	mat_metal(t_vec3 incoming_ray, t_vec3 surf_norm, \
float fuzz, t_uint *seed)
{
	t_vec3	bounce_ray;
	float	magnitude;

	magnitude = 2 * (scalar_product(incoming_ray, surf_norm));
	bounce_ray = mult_vec_scalar(surf_norm, magnitude);
	bounce_ray = unit_vec3(subtract_vec(incoming_ray, bounce_ray));
	if (fuzz > 0.0)
		bounce_ray = simulate_fuzz(bounce_ray, fuzz, seed);
	return (bounce_ray);
}

/* 
 * child function in ray_color
 * returns ray direction when surface material is diffuse
 * 
 * diffuse light when scattered, rays are biased towards the surface normal
 * 1. takes surface normal, add random vector to it; creates scattered direction
 * 2. result simulates how light bounces off randomly off a rough surface
 * 3. check if result is close to zero (no direction)
 * 4. if res = 0, use surface normal as the direction
 */
t_vec3	mat_lambertian(t_vec3 surf_norm, t_uint *seed)
{
	t_vec3	res;

	res = add_vec(surf_norm, rand_vec(seed));
	if (is_near_zero(res))
		res = surf_norm;
	return (res);
}

/*
 * child function in sample_pixels
 * returns background gradient color
 * 
 * t = interpolation factor; between 0 and 1; how much bg colour to mix to create gradient
 * normalize > get interpolation factor > return gradient of col based on t
 * return gradient of mixed bg colour based on ray points (up / down / horizontally)
 * 1. normalize ray > ensure direction has length 1
 * 	  eg ray vector (0.7, 0.7, 0); up ad right direction; before norm = len_vec = 0.99
 *    after norm = 0.7 / 0.99 = 0.707 (between -1 and +1)
 * 2. calc interpolation factor
 *	  eg (0.707 + 1) / 2 = 1.707 / 2 = 0.854 (thus, 85.4% of the sky colour, 14.6% of ground color)
 * 3. return gradient of mixed bg colour based on ray points (up / down / horizontally)
 */
t_vec3	bg_color(t_rt vars, t_ray ray)
{
	float	t;

	ray.vector.y /= len_vec3(ray.vector);
	t = (ray.vector.y + 1) / 2;
	return (lerp_rgb(vars.color_bg[1], vars.color_bg[0], t));
	// return (split_rgb(lerp_hsv(vars.color_bg[1], vars.color_bg[0], t)));
}
