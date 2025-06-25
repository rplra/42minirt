/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 08:44:18 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/24 21:52:20 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	vector_len(t_vec3 vec)
{
	return ((sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2))));
}

t_vec3	vector_subtract(t_vec3 v1, t_vec3 v2)
{
	t_vec3 res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

t_vec3	vector_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3 res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_vec3	vector_scale(t_vec3 v, float scale)
{
	t_vec3 res;

	res.x = v.x * scale;
	res.y = v.y * scale;
	res.z = v.z * scale;
	return (res);
}

t_vec3 vector_negate(t_vec3 v)
{
	t_vec3	neg;
	
	neg.x = -v.x;
	neg.y = -v.y;
	neg.z = -v.z;
	return (neg);
}

t_vec3	vector_normalize(t_vec3 vec)
{
	float	norm;

	norm = vector_len(vec);
	if (norm == 0.0)
		exit_with_error("Error: Vector length is zero, unable to normalize\n");
	norm = 1.0 / norm;
	vec.x *= norm;
	vec.y *= norm;
	vec.z *= norm;
	return (vec);
}