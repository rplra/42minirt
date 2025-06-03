/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 08:26:36 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/03 16:03:16 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


// check for multiple A, C and L
int	validate_setup(t_parse *scene)
{
	if (scene->ambient_count > 1 || scene->camera_count > 1
		|| scene->light_count > 1)
		return (print_error(scene, ERROR_UNIQUEID, 0, scene->tokens));
	if (scene->ambient_count == 0 || scene->camera_count == 0
		|| scene->light_count == 0)
		return (print_error(scene, ERROR_MISSINGID, 0, scene->tokens));
	return (0);
}

// to define all error message
// to match boundaries with define
// to parse value into struct
// to normalize vector

int parse_ambient(char **params, t_parse *scene, t_ambient *ambient)
{
	float	ratio;
	char	**colour;
	bool	valid;

	if (count_params(params) != 3)
		return (print_error(scene, ERROR_ACOUNT, 0, params));
	ratio = ft_atoui(params[1], &valid);
	if (!valid || ratio < 0.0 || ratio > 1.0)
		return (print_error(scene, ERROR_RATIO, 1, params));
	colour = ft_split(params[2], ',');
	is_colour(colour);
	return (free_arrays(params, colour, NULL, NULL));
}

int parse_camera(char **params, t_parse *scene, t_camera *camera)
{
	char	**position;
	char	**orientation;
	uint	fov;
	bool	valid;

	if (count_params(params) != 4)
		return (print_error(scene, ERROR_CCOUNT, 0, params));
	position = ft_split(params[1], ',');
	if (!is_vector(scene, position, &camera->position, NO))
		print_error(scene, ERROR_CPOS, 1, NULL);
	orientation = ft_split(params[2], ',');
	if (!is_vector(scene, orientation, &camera->orientation, YES))
		print_error(scene, ERROR_CORT, 2, NULL);
	fov = ft_atoui(params[3], &valid);
	if (!valid || fov < FOV_MIN || fov > FOV_MAX)
		return (print_error(scene, ERROR_CFOV, 3, params));
	// parse info into struct
	return (free_arrays(params, position, orientation, NULL));
}

int parse_light(char **params, t_parse *scene, t_light *light)
{
	char	**position;
	char	**colour;
	double	ratio;
	bool	valid;
	
	if (count_params(params) != 4)
		return (print_error(scene, ERROR_LCOUNT, 0, params));
	position = ft_split(params[1], ',');
	if (!is_vector(scene, position, &light->position, NO))
		return (print_error(scene, ERROR_LPOS, 1, params));
	ratio = ft_atod(params[2], &valid);
	if (!valid || ratio < 0.0 || ratio > 1.0)
		return (print_error(scene, ERROR_RATIO, 0, params));
	colour = ft_split(params[3], ',');
	is_colour(colour);
	return (free_arrays(params, position, colour, NULL));
}
