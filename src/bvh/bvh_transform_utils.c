/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_transform_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:11:35 by hsim              #+#    #+#             */
/*   Updated: 2025/08/14 17:11:59 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	get_vec_min(t_vec3 j, t_vec3 k)
{
	t_vec3	pt;

	pt.x = fmin(j.x, k.x);
	pt.y = fmin(j.y, k.y);
	pt.z = fmin(j.z, k.z);
	return (pt);
}

t_vec3	get_vec_max(t_vec3 j, t_vec3 k)
{
	t_vec3	pt;

	pt.x = fmax(j.x, k.x);
	pt.y = fmax(j.y, k.y);
	pt.z = fmax(j.z, k.z);
	return (pt);
}
