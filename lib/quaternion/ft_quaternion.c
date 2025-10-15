/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quaternion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:33:14 by hsim              #+#    #+#             */
/*   Updated: 2025/08/14 16:12:51 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

float	ft_square(float num)
{
	return (num * num);
}

/* converts degree to radian */
float	radian(float deg)
{
	return ((deg * M_PI) / 180);
}

/* 
 * Creates a new quaternion,
 * a rotation instruction with degree & axis of rotation
 * q = cos(deg/2) + sin(deg/2)( x + y + z )
 *   = cos(deg/2) + (x * sin(deg/2)) + (y * sin(deg/2)) + (z * sin(deg/2))
 * 
 * converts deg to radians automatically
 */
t_quat	new_quaternion(t_vec3 axis, float deg)
{
	t_quat	q;
	float	rad;

	rad = radian(deg);
	q.scalar = cos(rad / 2);
	q.vector = mult_vec_scalar(axis, sin(rad / 2));
	return (q);
}

/*
 * Conjugate Quaternion
 * reverses sign of quaternion vectors to negative
 */
t_quat	conjugate_quaternion(t_quat q1)
{
	t_quat	result;

	result.scalar = q1.scalar;
	result.vector = mult_vec_scalar(q1.vector, -1.0);
	return (result);
}
