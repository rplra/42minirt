/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:43:30 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/04 15:48:23 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//normalize normal
int	parse_plane(t_parse *file, t_object *obj)
{
	char	**position;
	char	**normal;
	char	**colour;

	if (count_params(file->tokens) != 4)
		return (print_error(file, ERROR_PLCOUNT, 0, file->tokens));
	position = ft_split(file->tokens[1], ',');
	if (!is_vector(file, position, &obj->obj.plane.position, NO))
		return (free_array(position), print_error(file, ERROR_PLPOS, 1, file->tokens));
	free_array(position);
	normal = ft_split(file->tokens[2], ',');
	if (!is_vector(file, normal, &obj->obj.plane.normal, YES))
		return (free_array(normal), print_error(file, ERROR_NORMAL, 2, file->tokens));
	free_array(normal);
	colour = ft_split(file->tokens[3], ',');
	if (!is_colour(file, colour, &obj->colour))
		return (free_array(colour), 1);
	free_array(colour);
	return (0);
}

int	parse_sphere(t_parse *file, t_object *obj)
{
	char	**position;
	char	**colour;
	bool	valid;

	if (count_params(file->tokens) != 4)
		return (print_error(file, ERROR_SPCOUNT, 0, file->tokens));
	position = ft_split(file->tokens[1], ',');
	if (!is_vector(file, position, &obj->obj.sphere.position, NO))
		return (print_error(file, ERROR_SPPOS, 1, file->tokens));
	free_array(position);
	obj->obj.sphere.diameter = ft_atod(file->tokens[2], &valid);
	if (!valid)
		return (print_error(file, ERROR_SPDIA, 2, file->tokens));
	colour = ft_split(file->tokens[3], ',');
	if (!is_colour(file, colour, &obj->colour))
		return (free_array(colour), 1);
	free_array(colour);
	return (0);
}

//normalize
int	parse_cylinder(t_parse *file, t_object *obj)
{
	char	**position;
	char	**axis;
	char	**colour;
	bool	valid;

	if (count_params(file->tokens) != 6)
		return (print_error(file, ERROR_CYCOUNT, 0, file->tokens));
	position = ft_split(file->tokens[1], ',');
	if (!is_vector(file, position, &obj->obj.cylinder.position, NO))
		return (print_error(file, ERROR_CYPOS, 1, file->tokens));
	axis = ft_split(file->tokens[2], ',');
	if (!is_vector(file, axis, &obj->obj.cylinder.axis, YES))
		return (print_error(file, ERROR_NORMAL, 2, file->tokens));
	obj->obj.cylinder.diameter = ft_atod(file->tokens[3], &valid);
	if (!valid || obj->obj.cylinder.diameter <= 0)
		return (print_error(file, ERROR_CYDIA, 3, file->tokens));
	obj->obj.cylinder.height = ft_atod(file->tokens[4], &valid);
	if (!valid || obj->obj.cylinder.height <= 0)
		return (print_error(file, ERROR_CYHT, 4, file->tokens));
	colour = ft_split(file->tokens[5], ',');
	if (!is_colour(file, colour, &obj->colour))
		return (free_array(colour), 1);
	free_array(colour);
	return (0);
}
