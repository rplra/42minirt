/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:11:59 by hsim              #+#    #+#             */
/*   Updated: 2025/07/19 09:02:21 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
 * brief: combines RGB into one colour; mlx can use to display colour
 * eg: create_rgb(135, 206, 235) > 0x87CEEB > 8900331
 * input values ranges frm 0 to 255
 * returns a rgb value
 */
int	create_rgb(int r_value, int g_value, int b_value)
{
	return (r_value << 16 | g_value << 8 | b_value);
}

/* 
 * brief: smoothly blends btw 2 colors based on a factor
 * variation of rgb 
 * lerp = linear interpolation rgb
 * mixes two col; t(0) = c1, t(0.5) = c1 + c2, t(1) = c2
 */
t_col	lerp_rgb(t_col c1, t_col c2, float t)
{
	t_vec3	color;

	color = add_vec(mult_vec_scalar(c1, (1 - t)), \
mult_vec_scalar(c2, t));
	return (color);
}

/*
 * brief: extract RGB into its respective value R, G, B in a vector
 * splits color into single r, g, b channel
 */
t_col	split_rgb(int color)
{
	t_col	res;

	res.r = (color >> 16) & 0xFF;
	res.g = (color >> 8) & 0xFF;
	res.b = color & 0xFF;
	return (res);
}

/*
 * brief: adjust brightness value to look more natural to human eyes
 * human eyes will adjust accordingly to the ambient brightness 
 * eg: in a dark env, eyes can adapt to see in the dark, vice versa
 * linear (actual), gamma (adjusted)
 */
static float	linear_to_gamma(float n)
{
	float	res;

	res = 0;
	if (n > 0)
		res = sqrt(n); // gamma 2.0, not 2.2
	if (res > 0.999)
		res = 0.999;
	else if (res < 0)
		res = 0;
	return (res);
}

/* brief: does color correction converting color values frm linear to gamma space
 * colour filter > based on how our eyes perceive (gamma) instead of reality(linear)
 */ 
t_vec3	color_correction(t_vec3 color)
{
	t_vec3	res;

	res.x = (int)(linear_to_gamma(color.x) * 256.0f);
	res.y = (int)(linear_to_gamma(color.y) * 256.0f);
	res.z = (int)(linear_to_gamma(color.z) * 256.0f);

	// res.x = (int)((color.x) * 255.0);
	// res.y = (int)((color.y) * 255.0);
	// res.z = (int)((color.z) * 255.0);
	return (res);
}

// clamp is needed so that if the value is 1.2 (beyond 255),
// value is strictly kept to 1.0 (255), vice versa
// float	clamp(float value, float min, float max)
// {
// 	if (value < min)
// 		return (min);
// 	if (value > max)
// 		return (max);
// 	return (value);
// }

// t_col	colour_clamp(t_col c)
// {
// 	c.r = clamp(c.r, 0.0f, 1.0f);
// 	c.g = clamp(c.g, 0.0f, 1.0f);
// 	c.b = clamp(c.b, 0.0f, 1.0f);
// 	return (c);
// }
