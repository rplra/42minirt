/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quaternion2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:55:02 by hsim              #+#    #+#             */
/*   Updated: 2025/07/28 08:47:03 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_enum.h"
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

/*
 * Quaternion Rotation
 * in Unit Quaternion, q inverse = conjugate quaternion
 * normalize quaternion, then multiply them
 * new pt = q . p . q inverse
 * q1= the rotation quaternion
 */
t_vec3	quaternion_rotate(t_quat q1, t_vec3 initpoint)
{
	t_quat	q2;
	t_quat	qpoint;
	t_quat	result;

	qpoint.scalar = 0.0;
	qpoint.vector = initpoint;
	norm_quaternion(&q1);
	q2 = conjugate_quaternion(q1);
	result = quaternion_multiply(q1, qpoint);
	result = quaternion_multiply(result, q2);
	return (result.vector);
}

/*
 * Quaternion Rotation
 * rotate object local axis in the world axis
 * (object is rotated, but object is still aligned to its local axis)
 * 
 * new pt = q . p . q conjugate
 * q1= the rotation quaternion
 */
t_vec3	local_to_global(t_quat q1, t_vec3 initpoint)
{
	t_quat	q2;
	t_quat	qpoint;
	t_quat	result;

	qpoint.scalar = 0.0;
	qpoint.vector = initpoint;
	norm_quaternion(&q1);
	q2 = conjugate_quaternion(q1);
	result = quaternion_multiply(q1, qpoint);
	result = quaternion_multiply(result, q2);
	return (result.vector);
}

/*
 * Quaternion Rotation
 * rotate world global axis to the obj local axis
 * ( object is rotated within its own axis,
 *   object is now not aligned to its local axis )
 * 
 * new pt = q conjugate . p . q
 * q1= the rotation quaternion
 */
t_vec3	global_to_local(t_quat q1, t_vec3 initpoint)
{
	t_quat	q2;
	t_quat	qpoint;
	t_quat	result;

	qpoint.scalar = 0.0;
	qpoint.vector = initpoint;
	norm_quaternion(&q1);
	q2 = conjugate_quaternion(q1);
	result = quaternion_multiply(q2, qpoint);
	result = quaternion_multiply(result, q1);
	return (result.vector);	//not sure if need normalize
}

void	init_rotation_quat(t_quat q[3], t_vec3 rotation)
{
	q[X] = new_quaternion(new_vec3(1, 0, 0), rotation.x);
	q[Y] = new_quaternion(new_vec3(0, 1, 0), rotation.y);
	q[Z] = new_quaternion(new_vec3(0, 0, 1), rotation.z);
}

void	init_conjugate_quat(t_quat conjugate[3], t_quat q[3])
{
	conjugate[X] = conjugate_quaternion(q[X]);
	conjugate[Y] = conjugate_quaternion(q[Y]);
	conjugate[Z] = conjugate_quaternion(q[Z]);
}

/*
 * x = x-axis rotation in quaternion, same follows y & z
 * normally will normalize quaternion before rotation
 * new point = x . y . z . point . x inverse . y inverse . z inverse
 * quaternion multiplication on:
 * left (q2 . q1) = rotation on global axis,
 * right (q1 . q2) = rotation on local axis 
 */
t_vec3	quaternion_rotate_adv(t_vec3 initpoint, t_vec3 rotation)
{
	t_quat	qpoint;
	t_quat	result;
	t_quat	conjugate[3];
	t_quat	q[3];

	qpoint.scalar = 0.0;
	qpoint.vector = initpoint;
	init_rotation_quat(q, rotation);
	init_conjugate_quat(conjugate, q);
	// conjugate[X] = conjugate_quaternion(q[X]);
	// conjugate[Y] = conjugate_quaternion(q[Y]);
	// conjugate[Z] = conjugate_quaternion(q[Z]);
	result = quaternion_multiply(q[Z], q[Y]);
	result = quaternion_multiply(result, q[X]);
	result = quaternion_multiply(result, qpoint);
	result = quaternion_multiply(result, conjugate[Z]);
	result = quaternion_multiply(result, conjugate[Y]);
	result = quaternion_multiply(result, conjugate[X]);
	// norm_quaternion(&result);
	// return (unit_vec3(result.vector));
	return (result.vector);
}

/*
 * x = x-axis rotation in quaternion, same follows y & z
 * normally will normalize quaternion before rotation
 * new point = x . y . z . point . x inverse . y inverse . z inverse
 * quaternion multiplication on:
 * left (q2 . q1) = rotation on global axis,
 * right (q1 . q2) = rotation on local axis 
 */
// t_vec3	quaternion_rotate_adv(t_quat x, t_quat y, t_quat z, \
// t_vec3 initpoint)
// {
// 	t_quat	qpoint;
// 	t_quat	result;
// 	t_quat	conjugate_x;
// 	t_quat	conjugate_y;
// 	t_quat	conjugate_z;

// 	qpoint.scalar = 0.0;
// 	qpoint.vector = initpoint;
// 	conjugate_x = conjugate_quaternion(x);
// 	conjugate_y = conjugate_quaternion(y);
// 	conjugate_z = conjugate_quaternion(z);
// 	result = quaternion_multiply(x, y);
// 	result = quaternion_multiply(result, z);
// 	result = quaternion_multiply(result, qpoint);
// 	result = quaternion_multiply(result, conjugate_x);
// 	result = quaternion_multiply(result, conjugate_y);
// 	result = quaternion_multiply(result, conjugate_z);
// 	return (unit_vec3(result.vector));
// 	// return (result.vector);
// }
