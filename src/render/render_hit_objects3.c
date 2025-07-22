/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit_objects3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:16:30 by hsim              #+#    #+#             */
/*   Updated: 2025/07/22 11:58:27 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * child function in check_hit_body
 * returns cyl_height considering its axis
 * using dot(pos, axis)*axis to mask the correct axis value
 * eg if axis=(0,1,0), cyl_axis_pos returns y value in cyl position
 * 
 * eg. if axis=(0,1,0) (y-axis), will be
 * cyl_height.max = cyl.pos.y + (cyl.axis.y * cyl.height / 2)
 * cyl_height.min = cyl.pos.y - (cyl.axis.y * cyl.height / 2)
 */
t_interval	get_cyl_axis_height(t_cylinder cyl)
{
	t_vec3		cyl_axis_pos;
	t_vec3		cyl_axis_height;
	t_interval	cyl_height;

	cyl_axis_pos = mult_vec_scalar(cyl.axis, scalar_product(cyl.pos, cyl.axis));
	cyl_axis_height = mult_vec_scalar(cyl.axis, cyl.height / 2);
	cyl_height.min = scalar_product(cyl.axis, subtract_vec(cyl_axis_pos, cyl_axis_height));
	cyl_height.max = scalar_product(cyl.axis, add_vec(cyl_axis_pos, cyl_axis_height));

	return (cyl_height);
}

/*
 * child function in check_hit_body
 * returns point on surface correspondiing to the cyl_axis
 * eg. if cyl_axis=(0,1,0) , point_on_surf=(3,2,1) returns 2 (value of y)
 */
void	get_point_on_surf(t_cylinder cyl, t_ray ray, float t[2], float res[2])
{
	t_vec3		pt_ray[2];

	pt_ray[0] = add_vec(ray.orig, mult_vec_scalar(ray.vector, t[0]));
	pt_ray[1] = add_vec(ray.orig, mult_vec_scalar(ray.vector, t[1]));
	res[0] = scalar_product(cyl.axis, pt_ray[0]);
	res[1] = scalar_product(cyl.axis, pt_ray[1]);
}