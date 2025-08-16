/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:11:59 by hsim              #+#    #+#             */
/*   Updated: 2025/08/15 08:40:34 by rraja-az         ###   ########.fr       */
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
	t_col	color;

	color = add_vec(mult_vec_scalar(c1, (1 - t)), mult_vec_scalar(c2, t));
	return (color);
}

/*
 * brief: extract RGB into its respective value R, G, B in a vector
 * splits color into single r, g, b channel
 */
t_col	split_rgb(int color)
{
	t_col	res;

	res.R = (color >> 16) & 0xFF;
	res.G = (color >> 8) & 0xFF;
	res.B = color & 0xFF;
	return (res);
}

/*
 * brief: adjust brightness value to look more natural to human eyes
 * human eyes will adjust accordingly to the ambient brightness
 * eg: in a dark env, eyes can adapt to see in the dark, vice versa
 * linear (actual), gamma (adjusted)
 * res = sqrt(n); // gamma 2.0, not 2.2
 */
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

/* 
 * brief: does color correction converting color values frm linear to gamma space
 * colour filter > how our eyes perceive (gamma) instead of reality(linear)
 *  if (color.R != color.R)// for NaNs check, NaN will not equal to itself
 */
t_col	color_correction(t_col color)
{
	t_col	res;

	if (color.R != color.R)
		color.R = 0;
	if (color.G != color.G)
		color.G = 0;
	if (color.B != color.B)
		color.B = 0;
	res.R = (int)(linear_to_gamma(color.R) * 256.0f);
	res.G = (int)(linear_to_gamma(color.G) * 256.0f);
	res.B = (int)(linear_to_gamma(color.B) * 256.0f);
	return (res);
}
