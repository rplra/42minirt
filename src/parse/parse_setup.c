/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 08:26:36 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/05 09:41:16 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// check for multiple / missing A, C and L 
int	validate_setup(t_parse *file)
{
	if (file->ambient_count > 1 || file->camera_count > 1
		|| file->light_count > 1)
		return (print_error(file, ERROR_UNIQUEID, 0, file->tokens));
	if (file->ambient_count == 0 || file->camera_count == 0
		|| file->light_count == 0)
		return (print_error(file, ERROR_MISSINGID, 0, file->tokens));
	return (0);
}

int parse_ambient(char **params, t_parse *file, t_ambient *ambient)
{
	t_ambient	tmp;
	char		**values;
	bool		valid;

	if (count_params(params) != 3)
		return (print_error(file, ERROR_ACOUNT, 0, params));
	ft_memset(&tmp, 0, sizeof(t_ambient));
	tmp.ratio = ft_atod(params[1], &valid);
	if (!valid || tmp.ratio < 0.0 || tmp.ratio > 1.0)
		return (print_error(file, ERROR_RATIO, 1, params));
	values = ft_split(params[2], ',');
	if (!is_colour(file, values, &tmp.colour))
		return (free_array(values), 1);
	free_array(values);
	*ambient = tmp;
	return (0);
}

//normalize
int parse_camera(char **params, t_parse *file, t_camera *camera)
{
	t_camera	tmp;
	char		**values;
	bool		valid;

	if (count_params(params) != 4)
		return (print_error(file, ERROR_CCOUNT, 0, params));
	ft_memset(&tmp, 0, sizeof(t_camera));
	values = ft_split(params[1], ',');
	if (!is_vector(file, values, &tmp.position, NO))
		return (free_array(values), print_error(file, ERROR_CPOS, 1, NULL));
	free_array(values);
	values = ft_split(params[2], ',');
	if (!is_vector(file, values, &tmp.orientation, YES))
		return (free_array(values), print_error(file, ERROR_CORT, 2, NULL));
	free_array(values);
	tmp.fov = ft_atoui(params[3], &valid);
	if (!valid || tmp.fov < FOV_MIN || tmp.fov > FOV_MAX)
		return (print_error(file, ERROR_CFOV, 3, params));
	*camera = tmp;
	return (0);
}

int parse_light(char **params, t_parse *file, t_light *light)
{
	t_light	tmp;
	char	**values;
	bool	valid;
	
	if (count_params(params) != 4)
		return (print_error(file, ERROR_LCOUNT, 0, params));
	ft_memset(&tmp, 0, sizeof(t_light));
	values = ft_split(params[1], ',');
	if (!is_vector(file, values, &tmp.position, NO))
		return (free_array(values), print_error(file, ERROR_LPOS, 1, params));
	free_array(values);
	tmp.brightness = ft_atod(params[2], &valid);
	if (!valid || tmp.brightness < 0.0 || tmp.brightness > 1.0)
		return (print_error(file, ERROR_RATIO, 2, params));
	values = ft_split(params[3], ',');
	if (!is_colour(file, values, &tmp.colour))
		return (free_array(values), 1);
	free_array(values);
	*light = tmp;
	return (0);
}
