/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:33:02 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/07 10:31:43 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// validate and store

int	parse_scene(t_parse *file, t_rt *rt)
{
	if (!file->tokens)
		return (print_error(file, ERROR_PARAMEMPTY, 0, NULL));
	if (ft_strcmp(file->tokens[0], "A") == 0)
	{
		//printf("Parsing Ambient\n"); // debug
		return (parse_ambient(file->tokens, file, &rt->ambient));
	}
	else if (ft_strcmp(file->tokens[0], "C") == 0)
	{
		//printf("Parsing Camera\n"); // debug
		return (parse_camera(file->tokens, file, &rt->camera));
	}
	else if (ft_strcmp(file->tokens[0], "L") == 0)
	{
		//printf("Parsing Light\n"); // debug
		return (parse_light(file->tokens, file, &rt->light));
	}
	else if (is_object(file->tokens[0]))
		return(parse_object(file, rt));
	return (print_error(file, ERROR_INVALIDID, 0, NULL));
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
	// add material defaults, to revise
	obj.material.specular = 0.5;
	obj.material.reflect = 0.5;
	return (add_object(rt, &obj));
}
