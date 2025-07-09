/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:43:30 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/09 20:47:49 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_plane(t_parse *file, t_object *obj)
{
	t_plane	tmp;
	char	**values;

	if (count_params(file->tokens) != 4)
		return (print_error(file, ERROR_PLCOUNT, -1, file->tokens));
	//printf("Plane param count : %i\n", count_params(file->tokens)); // debug
	ft_memset(&tmp, 0, sizeof(t_plane));
	values = ft_split(file->tokens[1], ',');
	if (is_vector(file, values, &tmp.position, NO))
		return (print_error(file, ERROR_PLPOS, 1, values));
	//printf("Plane pos: (x=%f, y=%f, z=%f)\n", tmp.position.x, tmp.position.y, tmp.position.z); // debug
	free_array(values);
	values = ft_split(file->tokens[2], ',');
	if (is_vector(file, values, &tmp.normal, YES))
		return (print_error(file, ERROR_NORMAL, 2, values));
	//printf("Plane normal: (x=%f, y=%f, z=%f)\n", tmp.normal.x, tmp.normal.y, tmp.normal.z); // debug
	free_array(values);
	tmp.normal = vector_normalize(tmp.normal);
	//printf("Plane normalized: (x=%f, y=%f, z=%f)\n", tmp.normal.x, tmp.normal.y, tmp.normal.z); // debug
	values = ft_split(file->tokens[3], ',');
	if (is_colour(file, values, &obj->colour))
		return (1);
	//printf("Converted colour: (r=%u, g=%u, b=%u)\n", obj->colour.r, obj->colour.g, obj->colour.b); // debug
	free_array(values);
	obj->type = PLANE;
	obj->obj.plane = tmp;
	//printf("Printing struct\n");
	//print_plane(obj);
	return (0);
}

int	parse_sphere(t_parse *file, t_object *obj)
{
	t_sphere	tmp;
	char		**values;
	bool		valid;

	if (count_params(file->tokens) != 4)
		return (print_error(file, ERROR_SPCOUNT, -1, file->tokens));
	//printf("Sphere param count : %i\n", count_params(file->tokens)); //debug
	ft_memset(&tmp, 0, sizeof(t_sphere));
	values = ft_split(file->tokens[1], ',');
	if (is_vector(file, values, &tmp.pos, NO))
		return (print_error(file, ERROR_SPPOS, 1, values));
	//printf("Camera pos: (x=%f, y=%f, z=%f)\n", tmp.position.x, tmp.position.y, tmp.position.z); // debug
	free_array(values);
	tmp.rad = ft_atof(file->tokens[2], &valid);
	if (!valid || tmp.rad <= 0)
		return (print_error(file, ERROR_SPDIA, 2, file->tokens));
	//printf("Sphere diameter: %f\n", tmp.diameter);
	values = ft_split(file->tokens[3], ',');
	if (is_colour(file, values, &obj->colour))
		return (1);
	//printf("Converted colour: (r=%u, g=%u, b=%u)\n", obj->colour.r, obj->colour.g, obj->colour.b);
	free_array(values);
	obj->type = SPHERE;
	obj->obj.sphere = tmp;
	//printf("Printing struct\n");
	//print_sphere(obj);
	return (0);
}

int	parse_cylinder(t_parse *file, t_object *obj)
{
	t_cylinder	tmp;
	char		**values;
	bool		valid;

	if (count_params(file->tokens) != 6)
		return (print_error(file, ERROR_CYCOUNT, -1, file->tokens));
	//printf("Cylinder param count : %i\n", count_params(file->tokens)); //debug
	ft_memset(&tmp, 0, sizeof(t_cylinder));
	values = ft_split(file->tokens[1], ',');
	if (is_vector(file, values, &tmp.position, NO))
		return (print_error(file, ERROR_CYPOS, 1, values));
	//printf("Cylinder pos: (x=%f, y=%f, z=%f)\n", tmp.position.x, tmp.position.y, tmp.position.z); // debug
	free_array(values);
	values = ft_split(file->tokens[2], ',');
	if (is_vector(file, values, &tmp.axis, YES))
		return (print_error(file, ERROR_NORMAL, 2, values));
	//printf("Cylinder axis: (x=%f, y=%f, z=%f)\n", tmp.axis.x, tmp.axis.y, tmp.axis.z); // debug
	tmp.axis = vector_normalize(tmp.axis);
	free_array(values);
	tmp.diameter = ft_atof(file->tokens[3], &valid);
	if (!valid || tmp.diameter <= 0)
		return (print_error(file, ERROR_CYDIA, 3, file->tokens));
	//printf("Cylinder diameter: %f\n", tmp.diameter);
	tmp.height = ft_atof(file->tokens[4], &valid);
	if (!valid || tmp.height <= 0)
		return (print_error(file, ERROR_CYHT, 4, file->tokens));
	//printf("Cylinder height: %f\n", tmp.height);
	values = ft_split(file->tokens[5], ',');
	if (is_colour(file, values, &obj->colour))
		return (1);
	//printf("Converted colour: (r=%u, g=%u, b=%u)\n", obj->colour.r, obj->colour.g, obj->colour.b);
	free_array(values);
	obj->type = CYLINDER;
	obj->obj.cylinder = tmp;
	//printf("Printing struct\n");
	//print_cylinder(obj);
	return (0);
}