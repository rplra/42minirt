/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:11:59 by hsim              #+#    #+#             */
/*   Updated: 2025/07/12 14:47:42 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
 * input values ranges frm 0 to 255
 * returns a rgb value
 */
// combines RGB into one colour; mlx can use to display colour
// eg; create_rgb(135, 206, 235) → 0x87CEEB → 8900331
int	create_rgb(int r_value, int g_value, int b_value)
{
	return (r_value << 16 | g_value << 8 | b_value);
}

/* variation of rgb */
// lerp = linear interpolation rgb; smoothly blends btw 2 colors based on a factor
// mixes two col; t(0) = c1, t(0.5) = c1 + c2, t(1) = c2
t_vec3	lerp_rgb(t_vec3 c1, t_vec3 c2, float t)
{
	t_vec3	color;

	color = add_vec(mult_vec_scalar(c1, (1 - t)), \
mult_vec_scalar(c2, t));
	return (color);
}

/* splits color into single r, g, b channel */
// extract RGB into its respective value R, G, B in a vector
t_vec3	split_rgb(int color)
{
	t_vec3	res;

	res.x = (color >> 16) & 0xFF;
	res.y = (color >> 8) & 0xFF;
	res.z = color & 0xFF;
	return (res);
}

// adjust brightness value to look more natural to human eyes
// human eyes will adjust accordingly to the ambient brightness 
// eg, in a dark env, eyes can adapt to see in the dark, vice versa
// linear is the actual colour
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

/* does color correction converting color values frm linear to gamma space */
// brief: colour filter > based on how our eyes perceive (gamma) instead of reality(linear)
// linear vs gamma
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