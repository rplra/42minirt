/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:36:20 by hsim              #+#    #+#             */
/*   Updated: 2025/07/14 07:54:02 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

/* Creates new vector from given values */
t_vec3	new_vec3(float x, float y, float z)
{
	t_vec3	newvector;

	newvector.x = x;
	newvector.y = y;
	newvector.z = z;
	return (newvector);
}

/* Calculates length of a vector, returns sqrt(x^2 + y^2 + z^2) */
float	len_vec3(t_vec3 vector)
{
	return (sqrt((vector.x * vector.x) + \
(vector.y * vector.y) + \
(vector.z * vector.z)));
}

/*
 * Normalize vector into unit vector
 * returns x / sqrt(x*x + y*y + z*z),
 *         y / sqrt(x*x + y*y + z*z),
 *         z / sqrt(x*x + y*y + z*z)
 */
t_vec3	unit_vec3(t_vec3 vector)
{
	float	len;

	len = len_vec3(vector);
	if (len >= 0.00001f)
		return (new_vec3(vector.x / len, \
vector.y / len, \
vector.z / len));
	return (new_vec3(0, 0, 0));
}

/* Add vector + vector */
t_vec3	add_vec(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

/* return vector a minus vector b */
t_vec3	subtract_vec(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}
