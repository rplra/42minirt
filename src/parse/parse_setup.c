/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 08:26:36 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/21 12:08:09 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int parse_ambient(char **params, t_parse *file, t_ambient *ambient)
{
	t_ambient	tmp;
	char		**values;
	bool		valid;

	if (count_params(params) != 3)
		return (print_error(file, ERROR_ACOUNT, -1, params));
	//printf("Ambient param count : %i\n", count_params(params)); // debug
	ft_memset(&tmp, 0, sizeof(t_ambient));
	tmp.intensity = ft_atof(params[1], &valid);
	//printf("Ambient ratio: %f\n",tmp.ratio); // debug
	if (!valid || tmp.intensity < 0.0 || tmp.intensity > 1.0)
		return (print_error(file, ERROR_RATIO, 1, params));
	values = ft_split(params[2], ',');
	if (is_colour(file, values, &tmp.colour))
		return (1);
	//printf("Converted colour: (r=%u, g=%u, b=%u)\n", tmp.colour.r, tmp.colour.g, tmp.colour.b); // debug
	free_array(values);
	*ambient = tmp;
	//printf("Printing struct\n");
	//print_ambient(ambient); // debug
	return (0);
}

//normalize
int parse_camera(char **params, t_parse *file, t_camera *camera)
{
	t_camera	tmp;
	char		**values;
	bool		valid;

	if (count_params(params) != 4)
		return (print_error(file, ERROR_CCOUNT, -1, params));
	//printf("Camera param count : %i\n", count_params(params)); // debug
	ft_memset(&tmp, 0, sizeof(t_camera));
	values = ft_split(params[1], ',');
	if (is_vector(file, values, &tmp.position, NO))
		return (print_error(file, ERROR_CPOS, 1, values));
	//printf("Camera pos: (x=%f, y=%f, z=%f)\n", tmp.position.x, tmp.position.y, tmp.position.z);
	free_array(values);
	values = ft_split(params[2], ',');
	if (is_vector(file, values, &tmp.orientation, YES))
		return (print_error(file, ERROR_CORT, 2, values));
	//printf("Camera ort: (x=%f, y=%f, z=%f)\n", tmp.orientation.x, tmp.orientation.y, tmp.orientation.z); // debug
	free_array(values);
	//printf("Camera ort normalized: (x=%f, y=%f, z=%f)\n", tmp.orientation.x, tmp.orientation.y, tmp.orientation.z); // debug
	vector_normalize(&tmp.orientation);
	tmp.fov = ft_atoui(params[3], &valid);
	if (!valid || tmp.fov < FOV_MIN || tmp.fov > FOV_MAX)
		return (print_error(file, ERROR_CFOV, 3, params));
	//printf("Camera fov: %u\n", tmp.fov);
	*camera = tmp;
	//printf("Printing struct\n");
	//print_camera(camera);
	return (0);
}

int parse_light(char **params, t_parse *file, t_light *light)
{
	t_light	tmp;
	char	**values;
	bool	valid;
	
	if (count_params(params) != 4)
		return (print_error(file, ERROR_LCOUNT, -1, params));
	//printf("Light param count : %i\n", count_params(params)); // debug
	ft_memset(&tmp, 0, sizeof(t_light));
	values = ft_split(params[1], ',');
	if (is_vector(file, values, &tmp.position, NO))
		return (print_error(file, ERROR_LPOS, 1, values));
	//printf("Light pos: (x=%f, y=%f, z=%f)\n", tmp.position.x, tmp.position.y, tmp.position.z);
	free_array(values);
	tmp.brightness = ft_atof(params[2], &valid);
	if (!valid || tmp.brightness < 0.0 || tmp.brightness > 1.0)
		return (print_error(file, ERROR_RATIO, 2, params));
	//printf("Light brightness: %f\n", tmp.brightness);
	values = ft_split(params[3], ',');
	if (is_colour(file, values, &tmp.colour))
		return (1);
	//printf("Converted colour: (r=%u, g=%u, b=%u)\n", tmp.colour.r, tmp.colour.g, tmp.colour.b); // debug
	free_array(values);
	*light = tmp;
	//printf("Printing struct\n");
	//print_light(light); // debug
	return (0);
}
