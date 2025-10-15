/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 08:26:36 by rraja-az          #+#    #+#             */
/*   Updated: 2025/10/14 21:30:12 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_ambient(char **tokens, t_parse *file, t_ambient *ambient)
{
	t_ambient	tmp;
	char		**values;
	bool		valid;

	if (count_tokens(tokens) != TOKENS_AMBIENT)
		return (print_error(file, ERROR_ACOUNT, -1, tokens));
	ft_memset(&tmp, 0, sizeof(t_ambient));
	tmp.intensity = ft_atof(tokens[1], &valid);
	if (!valid || tmp.intensity < 0.0 || tmp.intensity > 1.0)
		return (print_error(file, ERROR_RATIO, 1, tokens));
	values = ft_split(tokens[2], ',');
	if (is_colour(file, values, &tmp.colour))
		return (1);
	free_array(values);
	*ambient = tmp;
	return (0);
}

int	parse_camera(char **tokens, t_parse *file, t_camera *camera)
{
	t_camera	tmp;
	char		**values;
	bool		valid;

	if (count_tokens(tokens) != TOKENS_CAMERA)
		return (print_error(file, ERROR_CCOUNT, -1, tokens));
	ft_memset(&tmp, 0, sizeof(t_camera));
	values = ft_split(tokens[1], ',');
	if (is_vector(file, values, &tmp.pos, NO))
		return (print_error(file, ERROR_CPOS, 1, values));
	free_array(values);
	values = ft_split(tokens[2], ',');
	if (is_vector(file, values, &tmp.lookat, YES))
		return (print_error(file, ERROR_CORT, 2, values));
	free_array(values);
	tmp.lookat = unit_vec3(tmp.lookat);
	if (tmp.lookat.x == 0 && tmp.lookat.y == 0 && tmp.lookat.z == 0)
		tmp.lookat = unit_vec3(subtract_vec(tmp.lookat, tmp.pos));
	tmp.lookat_ori = tmp.lookat;
	tmp.hfov = ft_atof(tokens[3], &valid);
	if (!valid || tmp.hfov < FOV_MIN || tmp.hfov > FOV_MAX)
		return (print_error(file, ERROR_CFOV, 3, tokens));
	tmp.hfov = radian(tmp.hfov);
	*camera = tmp;
	return (0);
}

int	parse_light(char **tokens, t_parse *file, t_light *light)
{
	t_light	tmp;
	char	**values;
	bool	valid;

	if (count_tokens(tokens) != TOKENS_LIGHT)
		return (print_error(file, ERROR_LCOUNT, -1, tokens));
	ft_memset(&tmp, 0, sizeof(t_light));
	values = ft_split(tokens[1], ',');
	if (is_vector(file, values, &tmp.pos, NO))
		return (print_error(file, ERROR_LPOS, 1, values));
	free_array(values);
	tmp.brightness = ft_atof(tokens[2], &valid);
	if (!valid || tmp.brightness < 0.0 || tmp.brightness > 1.0)
		return (print_error(file, ERROR_RATIO, 2, tokens));
	values = ft_split(tokens[3], ',');
	if (is_colour(file, values, &tmp.colour))
		return (1);
	free_array(values);
	*light = tmp;
	return (0);
}
