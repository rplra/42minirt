/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 08:26:36 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/04 16:13:23 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


// check for multiple A, C and L
int	validate_setup(t_parse *file)
{
	if (file->ambient_count > 1 || file->camera_count > 1
		|| file->light_count > 1)
		return (print_error(file, ERROR_UNIQUEID, 0, file->tokens));
	if (file->ambient_count == 0 || file->camera_count == 0
		|| file->light_count == 0)
		return (print_error(file, ERROR_MISSINGID, 0, file->tokens));
	return (0);
}

// to define all error message
// to match boundaries with define
// to parse value into struct
// to normalize vector

int parse_ambient(char **params, t_parse *file, t_ambient *ambient)
{
	char	**colour;
	bool	valid;

	if (count_params(params) != 3)
		return (print_error(file, ERROR_ACOUNT, 0, params));
	ambient->ratio = ft_atod(params[1], &valid);
	if (!valid || ambient->ratio < 0.0 || ambient->ratio > 1.0)
		return (print_error(file, ERROR_RATIO, 1, params));
	colour = ft_split(params[2], ',');
	is_colour(file, colour, &ambient->colour);
	if (!is_colour(file, colour, &ambient->colour))
		return (free_array(colour), 1);
	free_array(colour);
	return (0);
}

//normalize
int parse_camera(char **params, t_parse *file, t_camera *camera)
{
	char	**position;
	char	**orientation;
	bool	valid;

	if (count_params(params) != 4)
		return (print_error(file, ERROR_CCOUNT, 0, params));
	position = ft_split(params[1], ',');
	if (!is_vector(file, position, &camera->position, NO))
		return (free_array(position), print_error(file, ERROR_CPOS, 1, NULL));
	free_array(position);
	orientation = ft_split(params[2], ',');
	if (!is_vector(file, orientation, &camera->orientation, YES))
		return (free_array(orientation), print_error(file, ERROR_CORT, 2, NULL));
	free_array(orientation);
	camera->fov = ft_atoui(params[3], &valid);
	if (!valid || camera->fov < FOV_MIN || camera->fov > FOV_MAX)
		return (print_error(file, ERROR_CFOV, 3, params));
	return (0);
}

int parse_light(char **params, t_parse *file, t_light *light)
{
	char	**position;
	char	**colour;
	bool	valid;
	
	if (count_params(params) != 4)
		return (print_error(file, ERROR_LCOUNT, 0, params));
	position = ft_split(params[1], ',');
	if (!is_vector(file, position, &light->position, NO))
		return (free_array(position), print_error(file, ERROR_LPOS, 1, params));
	free_array(position);
	light->brightness = ft_atod(params[2], &valid);
	if (!valid || light->brightness < 0.0 || light->brightness > 1.0)
		return (print_error(file, ERROR_RATIO, 0, params));
	colour = ft_split(params[3], ',');
	is_colour(file, colour, &light->colour);
	if (!is_colour(file, colour, &light->colour))
		return (free_array(colour), 1);
	free_array(colour);
	return (0);
}
