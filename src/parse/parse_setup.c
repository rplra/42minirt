/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 08:26:36 by rraja-az          #+#    #+#             */
/*   Updated: 2025/05/29 17:45:31 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// to define all error message
// to match boundaries with define
// to parse value into struct
// to normalize vector

void parse_ambient(t_parse *scene, t_ambient *ambient)
{
	float	ratio;
	char	**colour;
	bool	valid;

	if (count_params(scene->tokens) != 3)
		exit_with_error("Error: Invalid parameter count for Ambient");
	ratio = ft_atoui(scene->tokens[1], valid);
	if (!valid || ratio < 0.0 || ratio > 1.0)
		exit_with_error("Error: Invalid ratio, range must be within 0.0 to 1.0");
	colour = ft_split(scene->tokens[2], ',');
	if (!is_colour(colour))
		exit_with_error("Error: Invalid colour, range must be within 0 to 255");
}

void parse_camera(t_parse *scene, t_camera *camera)
{
	char	**position;
	char	**orientation;
	uint	fov;
	bool	valid;

	if (count_params(scene->tokens) != 4)
		exit_with_error("Error: Invalid parameter count for Camera");
	position = ft_split(scene->tokens[1], ',');
	if (!is_vector(position, NO))
	{
		free_array(position);
		exit_with_error("Error: Invalid camera position coordinates");
	}
	orientation = ft_split(scene->tokens[2], ',');
	if (!is_vector(orientation, YES))
	{
		free_array(orientation);
		exit_with_error("Error: Invalid orientation coordinates");
	}
	fov = ft_atoui(scene->tokens[3], valid);
	if (!valid || fov < FOV_MIN || fov > FOV_MAX)
		exit_with_error("Error: FOV must be between 0 to 180");
	// parse info into struct
	// free whatever that was previously parsed
}

void parse_light(t_parse *scene, t_light *light)
{
	char	**position;
	double	ratio;
	char	**colour;
	bool	valid;
	
	if (count_params(scene->tokens) != 4)
		exit_with_error("Error: Invalid parameter count for Camera");
	position = ft_split(scene->tokens[1], ',');
	if (!is_vector(position, NO))
		exit_with_error("Error: Invalid light point coordinates");
	ratio = ft_atoui(scene->tokens[1], valid);
	if (!valid || ratio < 0.0 || ratio > 1.0)
		exit_with_error("Error: Invalid ratio, range must be within 0.0 to 1.0");
	colour = ft_split(scene->tokens[3], ',');
	if (!is_colour(colour))
		exit_with_error("Error: Invalid colour, range must be within 0 to 255");
}