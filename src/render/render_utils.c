/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:18:14 by hsim              #+#    #+#             */
/*   Updated: 2025/08/06 13:02:33 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * checks if all vector values is near to zero 
 * useful for normalizing a vector to avoid dividing it by zero
 * prevents error in math, normalize, intersection and shading
*/
bool	is_near_zero(t_vec3 vec)
{
	float	res[3];
	float	s;

	s = 0.001f;
	res[X] = fabs(vec.x);
	res[Y] = fabs(vec.y);
	res[Z] = fabs(vec.z);
	return ((res[X] < s) && (res[Y] < s) && (res[Z] < s));
}

/* 
 * assigns value in t_vec3 to float[3]
 * used in hit aabb
 */
void	vec3_to_arr(t_vec3 pt, float res[3])
{
	res[X] = pt.x;
	res[Y] = pt.y;
	res[Z] = pt.z;
}

// void	swap_float(float t[2])
// {
// 	float	tmp;

// 	if (t[0] > t[1])
// 	{
// 		// /*debug*/printf("swap!\n");
// 		tmp = t[0];
// 		t[0] = t[1];
// 		t[1] = tmp;
// 	}
// }

void	assign_int(int value[2], int width, int height)
{
	value[W] = width;
	value[H] = height;
}
