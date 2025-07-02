/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:30:15 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/02 19:16:38 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// need to fix
int	is_shadow(t_rt	*vars, t_vec3 point, t_vec3 normal, t_scene *scene)
{
	t_vec3		light_dir;
	t_ray		shadow_ray;
	t_interval	shadow_ray_range;
	t_obj		*shadow_obj;
	float		distance_to_light;

	// get direction from point to light
	light_dir = (subtract_vec(scene->light.position, point));
	distance_to_light = len_vec3(light_dir);
	light_dir = unit_vec3(light_dir);

	// offset origin to avoid shadow acne
	shadow_ray.orig = add_vec(point, mult_vec_scalar(normal, EPSILON));
	shadow_ray.vector = light_dir;

	// init hit
	// shadow_hit.t = FLT_MAX;
	// shadow_hit.obj = NULL;
	
	// set valid range for shadow ray (btw point and light)
	shadow_ray_range = new_interval(EPSILON, distance_to_light);

	// check intersection
	shadow_obj = hit(vars, shadow_ray_range, shadow_ray);
	if (shadow_obj && vars->rec.t < distance_to_light)
		return (1);
	return (0);
}
