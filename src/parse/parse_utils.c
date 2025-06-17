/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 08:34:27 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/13 18:59:55 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_object(const char *token)
{
	return (ft_strcmp(token, "pl") == 0)
			|| (ft_strcmp(token, "sp") == 0)
			|| (ft_strcmp(token, "cy") == 0);
}

int	add_object(t_scene *scene, t_object obj)
{
	t_object	*new_objs;
	size_t		old_size;
	size_t		new_size;
	
	old_size = scene->obj_count * sizeof(t_object);
	new_size = (scene->obj_count + 1) * sizeof(t_object);
	new_objs = ft_realloc(scene->objects, old_size, new_size);
	if (!new_objs)
		return (1);
	scene->objects = new_objs;
	scene->objects[scene->obj_count] = obj;
	scene->obj_count++;
	return (0);
}

int	count_params(char **params)
{
	int	i;

	i = 0;
	while (params[i])
		i++;
	return (i);
}

int	is_colour(t_parse *scene, char **col, t_colour *colour)
{
	bool	valid;
	
	if (count_params(col) != 3)
		return (print_error(scene, ERROR_COLCOUNT, 0, col));
	colour->r = ft_atoui(col[0], &valid);
	if (!valid)
		return (print_error(scene, ERROR_INVALID_R, -1, col));
	colour->g = ft_atoui(col[1], &valid);
	if (!valid)
		return (print_error(scene, ERROR_INVALID_G, -1, col));
	colour->b = ft_atoui(col[2], &valid);
	if (!valid)
		return (print_error(scene, ERROR_INVALID_B, -1, col));
	if ((colour->r < 0 || colour->r > 255)
		|| (colour->g < 0 || colour->g > 255)
		|| (colour->b < 0 || colour->b > 255))
		return (print_error(scene, ERROR_INVALID_COL_VAL, -1, col));;
	return (0);
}

int	is_vector(t_parse *scene, char **values, t_vector *vector, bool check_range)
{
	bool	valid;

	if (count_params(values) != 3)
		return (print_error(scene, ERROR_INVALID_COORD, -1, NULL));
	vector->x = ft_atof(values[0], &valid);
	if (!valid)
		return (print_error(scene, ERROR_INVALID_X, -1, NULL));
	vector->y = ft_atof(values[1], &valid);
	if (!valid)
		return (print_error(scene, ERROR_INVALID_Y, -1, NULL));
	vector->z = ft_atof(values[2], &valid);
	if (!valid)
		return (print_error(scene, ERROR_INVALID_Z, -1, NULL));
	if (check_range)
	{
		if ((vector->x < -1 || vector->x > 1)
		|| (vector->y < -1 || vector->y > 1) 
		|| (vector->z < -1 || vector->z > 1))
		return (print_error(scene, ERROR_VECTOR, -1, NULL));
	}
	return (0);
}
