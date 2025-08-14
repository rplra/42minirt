/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 08:34:27 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/14 23:52:45 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	count_params(char **params)
{
	int	i;

	i = 0;
	while (params[i])
		i++;
	return (i);
}

bool	is_object(const char *token)
{
	return ((ft_strcmp(token, "pl") == 0)
		|| (ft_strcmp(token, "sp") == 0)
		|| (ft_strcmp(token, "cy") == 0));
}

int	add_object(t_rt *rt, t_obj *obj)
{
	t_obj	*new_objs;
	size_t	old_size;
	size_t	new_size;

	old_size = rt->obj_count * sizeof(t_obj);
	new_size = (rt->obj_count + 1) * sizeof(t_obj);
	new_objs = ft_realloc(rt->obj, old_size, new_size);
	if (!new_objs)
		return (1);
	rt->obj = new_objs;
	rt->obj[rt->obj_count] = *obj;
	rt->obj_count++;
	return (0);
}

int	is_colour(t_parse *scene, char **col, t_col *colour)
{
	bool	valid;

	if (count_params(col) != 3)
		return (print_error(scene, ERROR_COLCOUNT, -1, col));
	colour->R = ft_atoui(col[0], &valid);
	if (!valid)
		return (print_error(scene, ERROR_INVALID_R, -1, col));
	colour->G = ft_atoui(col[1], &valid);
	if (!valid)
		return (print_error(scene, ERROR_INVALID_G, -1, col));
	colour->B = ft_atoui(col[2], &valid);
	if (!valid)
		return (print_error(scene, ERROR_INVALID_B, -1, col));
	if ((colour->R < 0 || colour->R > 255) || (colour->G < 0 || colour->G > 255)
		|| (colour->B < 0 || colour->B > 255))
		return (print_error(scene, ERROR_INVALID_COL_VAL, -1, col));
	colour->R = (float)colour->R / 255.0;
	colour->G = (float)colour->G / 255.0;
	colour->B = (float)colour->B / 255.0;
	return (0);
}

int	is_vector(t_parse *scene, char **values, t_vec3 *vector, bool check_range)
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
		if ((vector->x < -1 || vector->x > 1) || (vector->y < -1
				|| vector->y > 1) || (vector->z < -1 || vector->z > 1))
			return (print_error(scene, ERROR_VECTOR, -1, NULL));
	}
	return (0);
}
