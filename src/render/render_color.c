/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:11:59 by hsim              #+#    #+#             */
/*   Updated: 2025/06/25 11:43:33 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
 * input values ranges frm 0 to 255
 * returns a rgb value
 */
int	create_rgb(int r_value, int g_value, int b_value)
{
	return (r_value << 16 | g_value << 8 | b_value);
}

/* variation of rgb */
t_vec3	lerp_rgb(t_vec3 c1, t_vec3 c2, float t)
{
	t_vec3	color;

	color = add_vec(mult_vec_scalar(c1, (1 - t)), \
mult_vec_scalar(c2, t));
	return (color);
}

/* splits color into single r, g, b channel */
t_vec3	split_rgb(int color)
{
	t_vec3	res;

	res.x = (color >> 16) & 0xFF;
	res.y = (color >> 8) & 0xFF;
	res.z = color & 0xFF;
	return (res);
}

static float	linear_to_gamma(float n)
{
	float	res;

	res = 0;
	if (n > 0)
		res = sqrt(n);
	if (res > 0.999)
		res = 0.999;
	else if (res < 0)
		res = 0;
	return (res);
}

/* does color correction converting color values frm linear to gamma space */
t_vec3	color_correction(t_vec3 color)
{
	t_vec3	res;

	res.x = (int)(linear_to_gamma(color.x) * 256.0);
	res.y = (int)(linear_to_gamma(color.y) * 256.0);
	res.z = (int)(linear_to_gamma(color.z) * 256.0);

	// res.x = (int)((color.x) * 255.0);
	// res.y = (int)((color.y) * 255.0);
	// res.z = (int)((color.z) * 255.0);
	return (res);
}