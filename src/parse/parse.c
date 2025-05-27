/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:33:02 by rraja-az          #+#    #+#             */
/*   Updated: 2025/05/27 14:59:11 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// validate and sotre

void	parse_params(t_parse *scene)
{
	if (!scene->params)
		exit_with_error("Error: Parameter is empty");
	if (ft_strncmp(scene->params[0], 'A', 1) == 0)
		return (parse_ambient(scene));
	if (ft_strncmp(scene->params[0], 'C', 1) == 0)
		return (parse_camera(scene));
	if (ft_strncmp(scene->params[0], 'L', 1) == 0)
		return (parse_light(scene));
	if (ft_strncmp(scene->params[0], "sp", 2) == 0)
		return (parse_sphere(scene));
	if (ft_strncmp(scene->params[0], "pl", 2) == 0)
		return (parse_plane(scene));
	if (ft_strncmp(scene->params[0], "cy", 2) == 0)
		return (parse_cylinder(scene));
}

// convert values to float for others
// convert values to int for colour

