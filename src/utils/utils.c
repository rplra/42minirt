/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:20:36 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/21 16:26:51 by rraja-az         ###   ########.fr       */
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

t_colour	colour_clamp(t_colour c)
{
	c.r = clamp(c.r, 0.0f, 1.0f);
	c.g = clamp(c.g, 0.0f, 1.0f);
	c.b = clamp(c.b, 0.0f, 1.0f);
	return (c);
}