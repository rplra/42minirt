/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:33:02 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/03 15:50:21 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// validate and store

int	parse_scene(t_parse *file, t_scene *scene)
{
	if (!file->tokens)
		return (print_error(scene, ERROR_PARAMEMPTY, 0, NULL));
	else if (ft_strcmp(file->tokens[0], "A") == 0)
		return (parse_ambient(file->tokens, scene, &scene->ambient));
	else if (ft_strcmp(file->tokens[0], "C") == 0)
		return (parse_camera(file->tokens, scene, &scene->camera));
	else if (ft_strcmp(file->tokens[0], "L") == 0)
		return (parse_light(file->tokens, scene, &scene->lights));
	else if (ft_strcmp(file->tokens[0], "sp") == 0)
		return (parse_sphere(scene));
	else if (ft_strcmp(file->tokens[0], "pl") == 0)
		return (parse_plane(scene));
	else if (ft_strcmp(file->tokens[0], "cy") == 0)
		return (parse_cylinder(scene));
	else
	{
		print_error(scene, ERROR_INVALIDID, 0, NULL);
		return (1);
	}
}

int	parse_object(t_parse *file, t_scene *scene)
{
	
}
