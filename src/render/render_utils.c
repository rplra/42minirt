/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:18:14 by hsim              #+#    #+#             */
/*   Updated: 2025/07/19 12:22:09 by rraja-az         ###   ########.fr       */
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
