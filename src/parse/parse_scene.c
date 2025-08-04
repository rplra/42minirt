/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:33:02 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/03 22:52:54 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// validate and store

int	parse_scene(t_parse *file, t_rt *rt)
{
	if (!file->tokens)
		return (print_error(file, ERROR_PARAMEMPTY, 0, NULL));
	if (ft_strcmp(file->tokens[0], "A") == 0)
		return (parse_ambient(file->tokens, file, &rt->ambient));
	else if (ft_strcmp(file->tokens[0], "C") == 0)
		return (parse_camera(file->tokens, file, &rt->camera));
	else if (ft_strcmp(file->tokens[0], "L") == 0)
		return (parse_light(file->tokens, file, &rt->light));
	else if (is_object(file->tokens[0]))
		return(parse_object(file, rt));
	return (print_error(file, ERROR_INVALIDID, 0, NULL));
}

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

int	parse_object(t_parse *file, t_rt *rt)
{
	t_obj obj;

	ft_memset(&obj, 0, sizeof(t_obj));
	if (ft_strcmp(file->tokens[0], "pl") == 0)
	{
		obj.type = PLANE;
		if (parse_plane(file, &obj))
			return (1);
	}
	else if (ft_strcmp(file->tokens[0], "sp") == 0)
	{
		obj.type = SPHERE;
		if (parse_sphere(file, &obj))
			return (1);
	}
	else if (ft_strcmp(file->tokens[0], "cy") == 0)
	{
		obj.type = CYLINDER;
		if (parse_cylinder(file, &obj))
			return (1);
	}
	assign_material(&obj.material);
	assign_rotation(&obj);
	assign_bbox(&obj);
	obj.id = rt->obj_count;
	return (add_object(rt, &obj));
}
