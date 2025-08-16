/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:43:30 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/16 22:33:21 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_plane(t_parse *file, t_obj *obj)
{
	t_plane	tmp;
	char	**values;

	if (count_params(file->tokens) != 4)
		return (print_error(file, ERROR_PLCOUNT, -1, file->tokens));
	ft_memset(&tmp, 0, sizeof(t_plane));
	values = ft_split(file->tokens[1], ',');
	if (is_vector(file, values, &tmp.pos, NO))
		return (print_error(file, ERROR_PLPOS, 1, values));
	free_array(values);
	values = ft_split(file->tokens[2], ',');
	if (is_vector(file, values, &tmp.normal, YES))
		return (print_error(file, ERROR_NORMAL, 2, values));
	free_array(values);
	tmp.normal = unit_vec3(tmp.normal);
	values = ft_split(file->tokens[3], ',');
	if (is_colour(file, values, &obj->material.albedo))
		return (1);
	free_array(values);
	obj->type = PLANE;
	obj->plane = tmp;
	setup_plane_geometry(obj);
	return (0);
}

int	parse_sphere(t_parse *file, t_obj *obj)
{
	t_sphere	tmp;
	char		**values;
	bool		valid;

	if (count_params(file->tokens) != 4)
		return (print_error(file, ERROR_SPCOUNT, -1, file->tokens));
	ft_memset(&tmp, 0, sizeof(t_sphere));
	values = ft_split(file->tokens[1], ',');
	if (is_vector(file, values, &tmp.pos, NO))
		return (print_error(file, ERROR_SPPOS, 1, values));
	free_array(values);
	tmp.rad = ft_atof(file->tokens[2], &valid) / 2;
	if (!valid || tmp.rad <= 0)
		return (print_error(file, ERROR_SPDIA, 2, file->tokens));
	values = ft_split(file->tokens[3], ',');
	if (is_colour(file, values, &obj->material.albedo))
		return (1);
	free_array(values);
	obj->type = SPHERE;
	obj->sph = tmp;
	return (0);
}

static int	parse_cylinder_dimensions_and_color(t_parse *file,
	t_cylinder *tmp, t_obj *obj)
{
	char	**values;
	bool	valid;

	tmp->rad = ft_atof(file->tokens[3], &valid) / 2;
	if (!valid || tmp->rad <= 0)
		return (print_error(file, ERROR_CYDIA, 3, file->tokens));
	tmp->height = ft_atof(file->tokens[4], &valid);
	if (!valid || tmp->height <= 0)
		return (print_error(file, ERROR_CYHT, 4, file->tokens));
	values = ft_split(file->tokens[5], ',');
	if (is_colour(file, values, &obj->material.albedo))
		return (1);
	return (0);
}

int	parse_cylinder(t_parse *file, t_obj *obj)
{
	t_cylinder	tmp;
	char		**values;

	if (count_params(file->tokens) != 6)
		return (print_error(file, ERROR_CYCOUNT, -1, file->tokens));
	ft_memset(&tmp, 0, sizeof(t_cylinder));
	values = ft_split(file->tokens[1], ',');
	if (is_vector(file, values, &tmp.pos, NO))
		return (print_error(file, ERROR_CYPOS, 1, values));
	free_array(values);
	values = ft_split(file->tokens[2], ',');
	if (is_vector(file, values, &tmp.axis, YES))
		return (print_error(file, ERROR_NORMAL, 2, values));
	tmp.axis = unit_vec3(tmp.axis);
	free_array(values);
	if (parse_cylinder_dimensions_and_color(file, &tmp, obj))
		return (1);
	obj->type = CYLINDER;
	obj->cyl = tmp;
	setup_cylinder_geometry(obj);
	return (0);
}
