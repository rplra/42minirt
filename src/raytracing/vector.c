/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 08:44:18 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/21 12:52:23 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	vector_len(t_vector vec)
{
	return ((sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2))));
}

t_vector	vector_subtract(t_vector v1, t_vector v2)
{
	t_vector res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

t_vector	vector_add(t_vector v1, t_vector v2)
{
	t_vector res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_vector	vector_scale(t_vector v, float scale)
{
	t_vector res;

	res.x = v.x * scale;
	res.y = v.y * scale;
	res.z = v.z * scale;
	return (res);
}

t_vector	*vector_normalize(t_vector *vec)
{
	float	norm;

	norm = vector_len(*vec);
	if (norm == 0.0)
		exit_with_error("Error: Vector length is zero, unable to normalize\n");
	norm = 1.0 / norm;
	vec->x *= norm;
	vec->y *= norm;
	vec->z *= norm;
	return (vec);
}