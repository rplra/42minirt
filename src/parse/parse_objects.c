/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:43:30 by rraja-az          #+#    #+#             */
/*   Updated: 2025/05/29 18:12:14 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void parse_plane(t_parse *scene, t_plane *plane)
{
	char	**position;
	char	**normal;
	char	**colour;
	bool	valid;

	if (count_params(scene->tokens) != 4)
		exit_with_error("Error: Invalid parameter count for Plane");
	position = ft_split(scene->tokens[1], ',');
	if (!is_vector(position, NO))
	{
		free_array(position);
		exit_with_error("Error: Invalid camera position coordinates");
	}
	normal = ft_split(scene->tokens[2], ',');
	if (!is_vector(normal, YES))
	{
		free_array(normal);
		exit_with_error("Error: Invalid orientation coordinates");
	}
	colour = ft_split(scene->tokens[3], ',');
	if (!is_colour(colour))
		exit_with_error("Error: Invalid colour, range must be within 0 to 255");
}

void parse_sphere(t_parse *scene, t_sphere *sphere)
{
	char	**sp_center;
	double	diameter;
	char	**colour;
	bool	valid;

	if (count_params(scene->tokens) != 4)
		exit_with_error("Error: Invalid parameter count for Sphere");
	sp_center = ft_split(scene->tokens[1], ',');
	if (!is_vector(sp_center, NO))
	{
		free_array(sp_center);
		exit_with_error("Error: Invalid camera position coordinates");
	}
	diameter = ft_atod(scene->tokens[2], valid);
	if (!valid)
		exit_with_error("Error: Diameter must be a positive interger");
	colour = ft_split(scene->tokens[3], ',');
	if (!is_colour(colour))
		exit_with_error("Error: Invalid colour, range must be within 0 to 255");
}

void parse_cylinder(t_parse *scene, t_cylinder *cylinder)
{
	char	**cy_center;
	char	**axis;
	double	diameter;
	double	height;
	char	**colour;
	bool	valid;

	if (count_params(scene->tokens) != 6)
		exit_with_error("Error: Invalid parameter count for Cylinder");
	cy_center = ft_split(scene->tokens[1], ',');
	if (!is_vector(cy_center, NO))
	{
		free_array(cy_center);
		exit_with_error("Error: Invalid camera position coordinates");
	}
	axis = ft_split(scene->tokens[2], ',');
	if (!is_vector(axis, YES))
	{
		free_array(axis);
		exit_with_error("Error: Invalid orientation coordinates");
	}
	diameter = ft_atod(scene->tokens[3], valid);
	if (!valid)
		exit_with_error("Error: Diameter must be a positive interger");
	height = ft_atod(scene->tokens[4], valid);
	if (!valid)
		exit_with_error("Error: Height must be a positive interger");
	colour = ft_split(scene->tokens[3], ',');
	if (!is_colour(colour))
		exit_with_error("Error: Invalid colour, range must be within 0 to 255");
}
