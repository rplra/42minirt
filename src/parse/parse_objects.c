/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:43:30 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/03 16:31:44 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int parse_plane(char **params, t_parse *scene, t_plane *plane)
{
	char	**position;
	char	**normal;
	char	**colour;
	bool	valid;

	if (count_params(params) != 4)
		return (print_error(scene, ERROR_PLCOUNT, 0, params));
	position = ft_split(params[1], ',');
	if (!is_vector(scene, position, &plane->position, NO))
		return(print_error(scene, ERROR_PLPOS, 1, params));
	normal = ft_split(params[2], ',');
	if (!is_vector(scene, normal, &plane->normal, YES))
		return (print_error(scene, ERROR_NORMAL, 2, params));
	colour = ft_split(params[3], ',');
	is_colour(colour);
	return (free_arrays(params, position, normal, colour));
}

int parse_sphere(char **params, t_parse *scene, t_sphere *sphere)
{
	char	**position;
	char	**colour;
	double	diameter;
	bool	valid;

	if (count_params(params) != 4)
		return (print_error(scene, ERROR_SPCOUNT, 0, params));
	position = ft_split(params[1], ',');
	if (!is_vector(scene, position, &sphere->position, NO))
		return (print_error(scene, ERROR_SPPOS, 1, params));
	diameter = ft_atod(params[2], &valid);
	if (!valid)
		return (print_error(scene, ERROR_SPDIA, 2, params));
	colour = ft_split(params[3], ',');
	is_colour(colour);
	return (free_arrays(params, position, colour, NULL));
}

int parse_cylinder(char **params, t_parse *scene, t_cylinder *cylinder)
{
	char	**position;
	char	**normal;
	char	**colour;
	double	diameter;
	double	height;
	bool	valid;

	if (count_params(params) != 6)
		return (print_error(scene, ERROR_CYCOUNT, 0, params));
	position = ft_split(params[1], ',');
	if (!is_vector(scene, position, &cylinder->position, NO))
		return (print_error(scene, ERROR_CYPOS, 1, params));
	normal = ft_split(params[2], ',');
	if (!is_vector(scene, normal, &cylinder->normal, YES))
		return (print_error(scene, ERROR_NORMAL, 2, params));
	diameter = ft_atod(params[3], &valid);
	if (!valid)
		return (print_error(scene, ERROR_CYDIA, 3, params));
	height = ft_atod(params[4], &valid);
	if (!valid)
		return (print_error(scene, ERROR_CYHT, 4, params));
	colour = ft_split(params[5], ',');
	is_colour(colour);
	return (free_arrays(params, position, normal, colour));
}
