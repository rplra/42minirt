/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_assign.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:09:12 by hsim              #+#    #+#             */
/*   Updated: 2025/08/14 23:43:17 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	assign_material(t_mat *material)
{
	material->type = MAT_TYPE;
	material->specular = MAT_SPECULAR;
	material->reflect = MAT_REFLECT;
	material->fuzz = MAT_FUZZ;
}

void	assign_rotation(t_obj *obj)
{
	obj->b_rotate = 0;
	obj->rotate = new_vec3(0, 0, 0);
}

void	assign_bbox(t_obj *obj)
{
	create_bbox(obj, obj->bbox);
	copy_bbox(obj->bbox_ori, obj->bbox);
	obj->bbox_center = get_bbox_center(obj->bbox);
}

void	assign_bbox_translate(t_obj *obj, t_vec3 delta)
{
	aabb_translate(*obj, obj->bbox, delta);
	copy_bbox(obj->bbox_ori, obj->bbox);
	obj->bbox_center = get_bbox_center(obj->bbox);
}

void	assign_obj(t_obj *obj)
{
	assign_material(&obj->material);
	assign_rotation(obj);
	assign_bbox(obj);
}
