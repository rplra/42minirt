/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quaternion2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:55:02 by hsim              #+#    #+#             */
/*   Updated: 2025/08/22 15:48:58 by hsim             ###   ########.fr       */
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
 * 
 * if flag=1 (default)
 * new pt = q . p . q inverse (local_to_global)
 * if flag=0
 * new pt = q inverse . p . q (global_to_local)
 * 
 * q1= the rotation quaternion
 */
t_vec3	quaternion_rotate(t_quat q1, t_vec3 initpoint, int flag)
{
	t_quat	conjugate;
	t_quat	qpoint;
	t_quat	result;

	qpoint.scalar = 0.0;
	qpoint.vector = initpoint;
	norm_quaternion(&q1);
	conjugate = conjugate_quaternion(q1);
	if (flag)
	{
		result = quaternion_multiply(q1, qpoint);
		result = quaternion_multiply(result, conjugate);
	}
	else
	{
		result = quaternion_multiply(conjugate, qpoint);
		result = quaternion_multiply(result, q1);
	}
	return (result.vector);
}

void	init_rotation_quat(t_quat q[3], t_vec3 rotation)
{
	q[X] = new_quaternion(new_vec3(1, 0, 0), rotation.x);
	q[Y] = new_quaternion(new_vec3(0, 1, 0), rotation.y);
	q[Z] = new_quaternion(new_vec3(0, 0, 1), rotation.z);
}

t_quat	quaternion_zyx(t_quat q[3])
{
	t_quat	result;

	result = quaternion_multiply(q[Z], q[Y]);
	result = quaternion_multiply(result, q[X]);
	return (result);
}

t_quat	quaternion_xyz(t_quat q[3])
{
	t_quat	result;

	result = quaternion_multiply(q[X], q[Y]);
	result = quaternion_multiply(result, q[Z]);
	return (result);
}

/*
 * x = x-axis rotation in quaternion, same follows y & z
 * normally will normalize quaternion before rotation
 * new point = x . y . z . point . x inverse . y inverse . z inverse
 * quaternion multiplication on:
 * left  (q2 . q1) = rotation on global axis,
 * right (q1 . q2) = rotation on local axis 
 * 
 * flag=0 : x.y.z . pt | (global_to_local)
 * flag=1 : z.y.x . pt | (local_to_global, default)
 */
t_vec3	quaternion_rotate_adv(t_vec3 initpoint, t_vec3 rotation, int flag)
{
	t_quat	q[3];
	t_quat	quat;
	t_vec3	result;

	init_rotation_quat(q, rotation);
	// if (flag)
		// quat = quaternion_zyx(q);
	// else
		quat = quaternion_xyz(q);
	norm_quaternion(&quat);	//maybe
	result = quaternion_rotate(quat, initpoint, flag);
	return (result);
}

/*
 * x = x-axis rotation in quaternion, same follows y & z
 * normally will normalize quaternion before rotation
 * new point = x . y . z . point . x inverse . y inverse . z inverse
 * quaternion multiplication on:
 * left (q2 . q1) = rotation on global axis,
 * right (q1 . q2) = rotation on local axis 
 */
// t_vec3	quaternion_rotate_adv(t_quat x, t_quat y, t_quat z,
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
