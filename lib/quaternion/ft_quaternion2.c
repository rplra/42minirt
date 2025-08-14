/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quaternion2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:55:02 by hsim              #+#    #+#             */
/*   Updated: 2025/08/14 16:13:00 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_enum.h"

/* 
 * Calculates the length/magnitude/norm of quaternion
 * = sqrt(scalar sq + i sq + j sq + k sq)
 */
float	len_quaternion(t_quat q1)
{
	return (sqrt(ft_square(q1.scalar) + ft_square(q1.vector.x) + \
ft_square(q1.vector.y) + ft_square(q1.vector.z)));
}

/*
 * Unit Quaternion
 * Normalize the quaternion to length of 1
 * = q / len_quaternion
 */
void	norm_quaternion(t_quat *q1)
{
	float	qlength;

	qlength = len_quaternion(*q1);
	q1->scalar /= qlength;
	q1->vector = mult_vec_scalar(q1->vector, 1.0 / qlength);
}

/* 
 * Quaternion Multiplication
 * Multiply q1 * q2
 * Not commutative !!
 * a1a2 - x1x2 - y1y2 - z1z2
 * + (a1x2 + x1a2 + y1z2 - z1y2)i
 * + (a1y2 - x1z2 + y1a2 + z1x2)j
 * + (a1z2 + x1y2 - y1x2 + z1a2)k
 */
t_quat	quaternion_multiply(t_quat q1, t_quat q2)
{
	t_quat	result;

	result.scalar = (q1.scalar * q2.scalar) - \
scalar_product(q1.vector, q2.vector);
	result.vector = cross_product_quaternion(q1, q2);
	return (result);
}
