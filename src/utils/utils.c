/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:20:36 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/11 16:50:27 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	flush_gnl(int fd)
{
	char *line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}	
}

// clamp is needed so that if the value is 1.2 (beyond 255),
// value is strictly kept to 1.0 (255), vice versa
float	clamp(float value, float min, float max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

t_vec3	colour_clamp(t_vec3 c)
{
	c.r = clamp(c.r, 0.0f, 1.0f);
	c.g = clamp(c.g, 0.0f, 1.0f);
	c.b = clamp(c.b, 0.0f, 1.0f);
	return (c);
}