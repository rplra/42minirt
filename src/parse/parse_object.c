/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:43:30 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/14 09:10:31 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	set_tmp_vec(t_vec3 normal)
{
	t_vec3	tmp;

	if (normal.x == 1)
		tmp = new_vec3(0, 0, -1);
	else if (normal.x != 0)
		tmp = new_vec3(0, 0, 1);
	else
		tmp = new_vec3(1, 0, 0);
	return (tmp);
}

void	assign_plane_components(t_obj *obj)
{
	t_vec3	n;
	t_vec3	tmp_vec;

	obj->type = PLANE;
	tmp_vec = set_tmp_vec(obj->plane.normal);
	obj->plane.coord[Y] = unit_vec3(cross_product(obj->plane.normal, tmp_vec));
	obj->plane.coord[X] = cross_product(obj->plane.normal, obj->plane.coord[Y]);
	//scale to certain size
	obj->plane.coord[X] = mult_vec_scalar(obj->plane.coord[X], -4);
	obj->plane.coord[Y] = mult_vec_scalar(obj->plane.coord[Y], 4);
	n = cross_product(obj->plane.coord[X], obj->plane.coord[Y]);
	obj->plane.d = scalar_product(obj->plane.normal, obj->plane.pos);
	obj->plane.w = div_vec_scalar(n, scalar_product(n, n));
}

int	parse_plane(t_parse *file, t_obj *obj)
{
	t_plane	tmp;
	char	**values;

	if (count_params(file->tokens) != 4)
		return (print_error(file, ERROR_PLCOUNT, -1, file->tokens));
	//printf("Plane param count : %i\n", count_params(file->tokens)); // debug
	ft_memset(&tmp, 0, sizeof(t_plane));
	values = ft_split(file->tokens[1], ',');
	if (is_vector(file, values, &tmp.pos, NO))
		return (print_error(file, ERROR_PLPOS, 1, values));
	//printf("Plane pos: (x=%f, y=%f, z=%f)\n", tmp.position.x, tmp.position.y, tmp.position.z); // debug
	free_array(values);
	values = ft_split(file->tokens[2], ',');
	if (is_vector(file, values, &tmp.normal, YES))
		return (print_error(file, ERROR_NORMAL, 2, values));
	//printf("Plane normal: (x=%f, y=%f, z=%f)\n", tmp.normal.x, tmp.normal.y, tmp.normal.z); // debug
	free_array(values);
	tmp.normal = unit_vec3(tmp.normal);
	//printf("Plane normalized: (x=%f, y=%f, z=%f)\n", tmp.normal.x, tmp.normal.y, tmp.normal.z); // debug
	values = ft_split(file->tokens[3], ',');
	if (is_colour(file, values, &obj->material.albedo))
		return (1);
	//printf("Converted colour: (r=%u, g=%u, b=%u)\n", obj->colour.r, obj->colour.g, obj->colour.b); // debug
	free_array(values);
	obj->plane = tmp;
	assign_plane_components(obj);
	// obj->type = PLANE;
	//printf("Printing struct\n");
	//print_plane(obj);
	return (0);
}

int	parse_sphere(t_parse *file, t_obj *obj)
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
	//printf("Sphere pos: (x=%f, y=%f, z=%f)\n", tmp.position.x, tmp.position.y, tmp.position.z); // debug
	free_array(values);
	tmp.rad = ft_atof(file->tokens[2], &valid) / 2;
	if (!valid || tmp.rad <= 0)
		return (print_error(file, ERROR_SPDIA, 2, file->tokens));
	//printf("Sphere radius: %f\n", tmp.rad);
	values = ft_split(file->tokens[3], ',');
	if (is_colour(file, values, &obj->material.albedo))
		return (1);
	//printf("Converted colour: (r=%u, g=%u, b=%u)\n", obj->colour.r, obj->colour.g, obj->colour.b);
	free_array(values);
	obj->type = SPHERE;
	obj->sph = tmp;
	//printf("Printing struct\n");
	//print_sphere(obj);
	return (0);
}

int	parse_cylinder(t_parse *file, t_obj *obj)
{
	t_cylinder	tmp;
	char		**values;
	bool		valid;

	if (count_params(file->tokens) != 6)
		return (print_error(file, ERROR_CYCOUNT, -1, file->tokens));
	//printf("Cylinder param count : %i\n", count_params(file->tokens)); //debug
	ft_memset(&tmp, 0, sizeof(t_cylinder));
	values = ft_split(file->tokens[1], ',');
	if (is_vector(file, values, &tmp.pos, NO))
		return (print_error(file, ERROR_CYPOS, 1, values));
	//printf("Cylinder pos: (x=%f, y=%f, z=%f)\n", tmp.position.x, tmp.position.y, tmp.position.z); // debug
	free_array(values);
	values = ft_split(file->tokens[2], ',');
	if (is_vector(file, values, &tmp.axis, YES))
		return (print_error(file, ERROR_NORMAL, 2, values));
	//printf("Cylinder axis: (x=%f, y=%f, z=%f)\n", tmp.axis.x, tmp.axis.y, tmp.axis.z); // debug
	tmp.axis = unit_vec3(tmp.axis);
	free_array(values);
	tmp.rad = ft_atof(file->tokens[3], &valid) / 2;
	if (!valid || tmp.rad <= 0)
		return (print_error(file, ERROR_CYDIA, 3, file->tokens));
	//printf("Cylinder radius: %f\n", tmp.rad);
	tmp.height = ft_atof(file->tokens[4], &valid);
	if (!valid || tmp.height <= 0)
		return (print_error(file, ERROR_CYHT, 4, file->tokens));
	//printf("Cylinder height: %f\n", tmp.height);
	values = ft_split(file->tokens[5], ',');
	if (is_colour(file, values, &obj->material.albedo))
		return (1);
	//printf("Converted colour: (r=%u, g=%u, b=%u)\n", obj->colour.r, obj->colour.g, obj->colour.b);
	free_array(values);
	obj->type = CYLINDER;
	obj->cyl = tmp;
	//printf("Printing struct\n");
	//print_cylinder(obj);
	return (0);
}