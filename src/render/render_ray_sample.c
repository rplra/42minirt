/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_sample.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:46:09 by hsim              #+#    #+#             */
/*   Updated: 2025/07/03 14:43:43 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "render.h"
#include "minirt.h"

/*
 * child function in sample_pixels 
 * return a random vector for pixel sampling
 */
t_vec3	sample_sq_rand(unsigned int *seed)
{
	t_vec3	pt;

	pt = new_vec3(rand_lcg(seed) - 0.5, rand_lcg(seed) - 0.5, 0);
	// /*debug*/printf("sample_sq_rand:%f %f %f\n", pt.x, pt.y, pt.z);
	return (pt);
}

/*
 * child function in sample_pixels 
 * return a random defoc_disk vector for disk sampling
 */
t_vec3	sample_defoc_disk(t_rt vars, unsigned int *seed)
{
	t_vec3	pt;
	t_vec3	res;

	pt = rand_unit_disk(seed);
	// res = vars.cam_orig;
	res = add_vec(vars.camera.position, add_vec(mult_vec_scalar(\
vars.camera.defoc_disk[X], pt.x), mult_vec_scalar(vars.camera.defoc_disk[Y], pt.y)));
	/*debug*/debug_print_vec("sample_defoc:cam:", vars.camera.position);
	/*debug*/debug_print_vec("sample_defoc:x:", vars.camera.defoc_disk[X]);
	/*debug*/debug_print_vec("sample_defoc:y:", vars.camera.defoc_disk[Y]);
	/*debug*/debug_print_vec("sample_defoc:pt:", pt);
	/*debug*/debug_print_vec("sample_defoc:res:", res);

	return (res);
}

/*
 * generate random sampling point on pixels
 * and return the color sampled
 */
int	sample_pixels(t_rt vars, t_vec3 target, t_vec3 viewport_d[2], int x)
{
	int				k;
	unsigned int	seed;
	t_vec3			offset;
	t_vec3			color;
	t_vec3			res;
	(void)	x;

	seed = 12349 + x;
	k = -1;
	color = new_vec3(0, 0, 0);
	res.z = target.z;
	while (++k < vars.camera.sample_per_pixel)
	{
		offset = sample_sq_rand(&seed);
		// res.x = target.x + (offset.x * viewport_d.x);
		// res.y = target.y + (offset.y * viewport_d.y);
		res.x = target.x + (offset.x * viewport_d[X].x) + \
(offset.y * viewport_d[Y].x);
		res.y = target.y + (offset.y * viewport_d[Y].y) + \
(offset.x * viewport_d[X].y);

		// res = add_vec(target, add_vec(\
// mult_vec_scalar(viewport_d[X], offset.x), mult_vec_scalar(viewport_d[Y], offset.y)));

		// auto pixel_sample = pixel00_loc
		//						+ ((i + offset.x()) * pixel_delta_u)
		//						+ ((j + offset.y()) * pixel_delta_v);
		if (vars.camera.defoc_ang > 0)
			vars.ray.orig = sample_defoc_disk(vars, &seed);
		vars.ray.vector = subtract_vec(res, vars.ray.orig);

		/*debug*/printf("ft_draw:tar:%f %f %f\n", target.x, target.y, target.z);
		/*debug*/printf("ft_draw:res:%f %f %f\n", res.x, res.y, res.z);

		// color = add_vec(color, ray_color_loop(vars, vars.ray, &seed));
		color = add_vec(color, ray_color(&vars, vars.ray, vars.camera.ray_bounce, &seed));
		// /*debug*/printf("color:%f %f %f\n", color.x, color.y, color.z);
	}
	color = div_vec_scalar(color, vars.camera.sample_per_pixel);
	color = color_correction(color);
	// /*debug*/printf("color_fin: %f %f %f\n", color.x, color.y, color.z);
	// color = color_correction(div_vector_scalar(color, vars.sample_per_pixel));
	return (create_rgb(color.x, color.y, color.z));
}
