/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_sample.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:46:09 by hsim              #+#    #+#             */
/*   Updated: 2025/07/27 20:33:58 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * child function in sample_pixels 
 * return a random vector for pixel sampling
 * 
 * brief: generates random 2d point within a square (the pixel) centered at 0,0
 * imagine a sticky note with center, then randomly touch a point within 0.5 away from the center
 * this helps smoothen out jagged lines
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
 * 
 * generates random point on a disk, centered at cam's position
 * if the point is out of disk, objects appear blurry otherwise if within, it stays sharp
 * 1. pick a random spot on the disk
 * 2. move cam's center to random point
 */
t_vec3	sample_defoc_disk(t_rt vars, unsigned int *seed)
{
	t_vec3	pt;
	t_vec3	res;

	pt = rand_unit_disk(seed);
	// res = vars.cam_orig;
	res = add_vec(vars.camera.pos, add_vec(mult_vec_scalar(\
vars.camera.defoc_disk[X], pt.x), mult_vec_scalar(vars.camera.defoc_disk[Y], pt.y)));
	// /*debug*/debug_print_vec("sample_defoc:cam:", vars.camera.pos);
	// /*debug*/debug_print_vec("sample_defoc:x:", vars.camera.defoc_disk[X]);
	// /*debug*/debug_print_vec("sample_defoc:y:", vars.camera.defoc_disk[Y]);
	// /*debug*/debug_print_vec("sample_defoc:pt:", pt);
	// /*debug*/debug_print_vec("sample_defoc:res:", res);
	return (res);
}

/*
 * generate random sampling point on pixels
 * and return the color sampled
 * 
 * combines sample from both square and lens to sample each pixes multiple times, trace rays, and compute final colour
 * target : 3d position on the image plane (the pixel i want to sample)
 * viewport : vecs that defines the pixel's width and height in 3d space
 * x : pixel's coordinate's (used for seeding ramdomness)
 * 
 * 1. takes the random point on both pixel and lens,
 * 2. get the direction from lens to pixel,
 * 3. trace rays and combines all colours and,
 * 4. get the final resulting colour based on the sample
 * 5. then after sampling it will average out the colour and correct it via gamma
 * 6. lastly converts the final colour to displayable RGB value
 */
int	sample_pixels(t_rt vars, t_vec3 target, t_vec3 viewport_d[2], int x)
{
	int				k;
	unsigned int	seed;
	t_vec3			offset;
	t_vec3			color;
	t_vec3			res;
	(void)	x;

	seed = vars.seed + x;
	k = -1;
	color = new_vec3(0, 0, 0);
	res.z = target.z;
	///*debug*/printf("sample_pixels: sample_per_pixel=%d, ray_bounce=%d\n",
	//	vars.camera.sample_per_pixel, vars.camera.ray_bounce);

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
		// /*debug*/printf("ft_draw:tar:%f %f %f\n", target.x, target.y, target.z);
		// /*debug*/printf("ft_draw:res:%f %f %f\n", res.x, res.y, res.z);
		color = add_vec(color, ray_color(&vars, vars.ray, vars.camera.ray_bounce, &seed));
		// /*debug*/printf("color:%f %f %f\n", color.x, color.y, color.z);
	}
	color = div_vec_scalar(color, vars.camera.sample_per_pixel);
	// /*debug*/printf("before gamma: %f %f %f\n", color.x, color.y, color.z);
	color = color_correction(color);
	// /*debug*/printf("after gamma: %f %f %f\n", color.x, color.y, color.z);
	return (create_rgb(color.x, color.y, color.z));
}
