/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:16:21 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/24 21:49:51 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_colour	colour_add(t_colour c1, t_colour c2)
{
		t_colour	c;

	c.r = clamp((c1.r + c2.r), 0, 255);
	c.g = clamp((c1.g + c2.g), 0, 255);
	c.b = clamp((c1.b + c2.b), 0, 255);
	return (c);
}

t_colour	colour_multiply(t_colour c1, t_colour c2)
{
	t_colour	c;

	c.r = c1.r * c2.r;
	c.g = c1.g * c2.g;
	c.b = c1.b * c2.b;
	return (c);
}

t_colour	colour_scale(t_colour col, float scale)
{
	t_colour	c;

	c.r = col.r * scale;
	c.g = col.g * scale;
	c.b = col.b * scale;
	return (c);
}

/* t_colour rgb_int_to_float(int rgb)
{
	t_colour	c;

	c.r = (float)((rgb >> 16) & 0xff) / 255;
	c.g = (float)((rgb >> 8) & 0xff) / 255;
	c.b = (float)(rgb & 0xff) / 255;
	return (c);
} */

int	rgb_float_to_int(t_colour col)
{
	int	c;

	c = (int)(col.r * 255) << 16;
	c += (int)(col.g * 255) << 8;
	c += (int)(col.b * 255);
	return (c);
}
