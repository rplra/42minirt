/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   product.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:42:18 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/24 21:52:20 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Diffused Lighting uses dot product between surface normal and light direction
// dot product determines how bright light is based on how aligned 2 vectors are
float	dot_product(t_vec3 u, t_vec3 v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}

// Rotation Transformation uses cross product to construct rotation axes for objects and cameras
// Cross product determines the rotation axis; byproduct of perpendicular vector (follow the right hand rule)
t_vec3 cross_product(t_vec3 u, t_vec3 v)
{
	t_vec3	length;
	
	length.x = u.x * v.x;
	length.y = u.y * v.y;
	length.z = u.z * v.y;
	return (length);
}