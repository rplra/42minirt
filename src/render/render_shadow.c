/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shadow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:18:50 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/19 17:32:33 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * brief: set up shadow ray & check if obj is shadowed
 * 1. start shadow ray just beneath surface to avoid acne (self intersection
 * 2. point ray to light, check if it hits obj before reaching light > hits > true
 */
int	is_shadowed(t_rt *rt, t_hit *point, t_vec3 light_dir, float t)
{
	t_ray	shadow_ray;
	t_obj	*shadow_obj;

	shadow_ray.orig = add_vec(point->at,
			mult_vec_scalar(point->surf_norm, EPSILON));
	shadow_ray.vector = light_dir;
	shadow_obj = hit(rt, new_interval(EPSILON, t), shadow_ray);
	if (shadow_obj)
		return (1);
	return (0);
}

