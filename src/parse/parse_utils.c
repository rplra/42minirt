/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 08:34:27 by rraja-az          #+#    #+#             */
/*   Updated: 2025/05/29 14:16:59 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		count_params(char **params)
{
	int	i;

	i = 0;
	while (params[i])
		i++;
	return (i);
}

bool	is_colour(char **col, t_colour *colour)
{
	if (count_params(col) != 3)
		exit_with_error("Error: Colour must consist of 3 values - R, G, B");
	colour->r = ft_atoi(col[0]);
	colour->g = ft_atoi(col[1]);
	colour->b = ft_atoi(col[2]);
	if ((colour->r < 0 || colour->r > 255)
		|| (colour->g < 0 || colour->g > 255)
		|| (colour->b < 0 || colour->b > 255))
		return (false);
	return (true);
}

bool	is_vector(char **values, t_vector *vector, bool check_range)
{
	bool	valid;

	if (count_params(values) != 3)
		exit_with_error("Error: Coordinate must consist of 3 values; x, y, z");
	vector->x = ft_atod(values[0], &valid);
	if (!valid)
		return (false);
	vector->y = ft_atod(values[1], &valid);
	if (!valid)
		return (false);
	vector->z = ft_atod(values[2], &valid);
	if (!valid)
		return (false);
	if (check_range)
	{
		if ((vector->x < -1 || vector->x > 1)
		|| (vector->y < -1 || vector->y > 1) 
		|| (vector->z < -1 || vector->z > 1))
		return (false);
	}
	return (true);
}
