/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:43:30 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/05 10:21:46 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//normalize normal
int	parse_plane(t_parse *file, t_object *obj)
{
	t_plane	tmp;
	char	**values;

	if (count_params(file->tokens) != 4)
		return (print_error(file, ERROR_PLCOUNT, 0, file->tokens));
	ft_memset(&tmp, 0, sizeof(t_plane));
	values = ft_split(file->tokens[1], ',');
	if (!is_vector(file, values, &tmp.position, NO) && free_array(values))
		return (print_error(file, ERROR_PLPOS, 1, file->tokens));
	free_array(values);
	values = ft_split(file->tokens[2], ',');
	if (!is_vector(file, values, &tmp.normal, YES) && free_array(values))
		return (print_error(file, ERROR_NORMAL, 2, file->tokens));
	free_array(values);
	values = ft_split(file->tokens[3], ',');
	if (!is_colour(file, values, &obj->colour))
		return (free_array(values), 1);
	free_array(values);
	obj->type = obj_plane;
	obj->obj.plane = tmp;
	return (0);
}

int	parse_sphere(t_parse *file, t_object *obj)
{
	t_sphere	tmp;
	char		**values;
	bool		valid;

	if (count_params(file->tokens) != 4)
		return (print_error(file, ERROR_SPCOUNT, 0, file->tokens));
	ft_memset(&tmp, 0, sizeof(t_sphere));
	values = ft_split(file->tokens[1], ',');
	if (!is_vector(file, values, &tmp.position, NO) && free_array(values))
		return (print_error(file, ERROR_SPPOS, 1, file->tokens));
	free_array(values);
	tmp.diameter = ft_atod(file->tokens[2], &valid);
	if (!valid)
		return (print_error(file, ERROR_SPDIA, 2, file->tokens));
	values = ft_split(file->tokens[3], ',');
	if (!is_colour(file, values, &obj->colour))
		return (free_array(values), 1);
	free_array(values);
	obj->type = obj_sphere;
	obj->obj.sphere = tmp;
	return (0);
}

//normalize
int	parse_cylinder(t_parse *file, t_object *obj)
{
	t_cylinder	tmp;
	char		**values;
	bool		valid;

	if (count_params(file->tokens) != 6)
		return (print_error(file, ERROR_CYCOUNT, 0, file->tokens));
	ft_memset(&tmp, 0, sizeof(t_cylinder));
	values = ft_split(file->tokens[1], ',');
	if (!is_vector(file, values, &tmp.position, NO) && free_array(values))
		return (print_error(file, ERROR_CYPOS, 1, file->tokens));
	values = ft_split(file->tokens[2], ',');
	if (!is_vector(file, values, &tmp.axis, YES) && free_array(values))
		return (print_error(file, ERROR_NORMAL, 2, file->tokens));
	tmp.diameter = ft_atod(file->tokens[3], &valid);
	if (!valid || tmp.diameter <= 0)
		return (print_error(file, ERROR_CYDIA, 3, file->tokens));
	tmp.height = ft_atod(file->tokens[4], &valid);
	if (!valid || tmp.height <= 0)
		return (print_error(file, ERROR_CYHT, 4, file->tokens));
	values = ft_split(file->tokens[5], ',');
	if (!is_colour(file, values, &obj->colour))
		return (free_array(values), 1);
	free_array(values);
	obj->type = obj_cylinder;
	obj->obj.cylinder = tmp;
	return (0);
}
