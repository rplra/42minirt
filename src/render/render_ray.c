/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:18:16 by hsim              #+#    #+#             */
/*   Updated: 2025/06/27 13:11:33 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * check all sph objects to see which is the closest hit
 * 
 * derived from quadratic equation discriminant formula
 * b sq - 4ac >= 0 (hit sphere)
 * b sq - 4ac < 0 (doesnt hit sphere)
 * full formula:
 * [-b +- sqrt(b sq - 4ac)]  /  2a
 * shortened:
 * [b +- sqrt(b sq - ac)]  /  a
 * 
 * res = discriminant
 * expanded frm sphere equation x sq + y sq + z sq - r sq = 0
 * vector from point P on ray -> sphere center C
 * 
 * returns the closest point if there are 2 roots
 * unsigned int max: 4294967295 as limit num
 * 
 * formula expansion reference:
 * https://raytracing.github.io/books/RayTracingInOneWeekend.html
 * https://youtu.be/ebzlMOw79Yw?si=8SXTPsEcSUtwft71
 */
float	has_hit_sphere(t_vec3 sph_orig, float radius, t_ray ray)
{
	float		n[3];
	float		discriminant;
	float		tmp;
	t_vec3		ray_to_center;

	ray_to_center = subtract_vec(sph_orig, ray.orig);
	n[A] = scalar_product(ray.vector, ray.vector) + EPS;
	n[B] = scalar_product(ray.vector, ray_to_center) + EPS;
	n[C] = scalar_product(ray_to_center, ray_to_center) - \
(radius * radius) + EPS;

	discriminant = (n[B] * n[B]) - (n[A] * n[C]);
	if (discriminant < 0)
		return (-1);
	tmp = (n[B] - sqrt(discriminant)) / n[A];
	if (tmp <= 0 || tmp >= 4294967295)
		tmp = (n[B] + sqrt(discriminant)) / n[A];
	/*debug*/printf("has_hit_sphere:%f %f\n", discriminant, INFINITY);

	if (tmp <= 0 || tmp >= 4294967295)
		return (-1);
	return (tmp);
}

/*
 * 3d point along a vector ray
 * vec = origin + (t * direction)
 */
t_vec3	point_at(float t, t_ray r)
{
	return (add_vec(r.orig, mult_vec_scalar(r.vector, t)));
}

/*
 * calculates vector pt_ray -> sphere_center
 * if scalar_product of ray . surf_norm > 0, (means ray hits inner side)
 * reverse direction of surf_norm if so
 * returns a surf_norm in unit vector
 */
t_vec3	get_surf_norm(t_ray ray, t_vec3 sph_center, float t)
{
	t_vec3	pt_ray;
	t_vec3	surf_norm;

	// also known as set_face_normal
	pt_ray = add_vec(ray.orig, mult_vec_scalar(ray.vector, t)); // .at
	surf_norm = subtract_vec(pt_ray, sph_center);
	surf_norm = unit_vec3(surf_norm);
	// so, reverse surf_norm if so
	if (scalar_product(ray.vector, surf_norm) > 0) // pointing in same direction
		surf_norm = mult_vec_scalar(surf_norm, -1);
	return (surf_norm);
}

/*
 * child function in ray_color
 * checks if ray hits any surface
 * returns the closest point ray hits
 * at = origin + (t * direction)
 */
int	hit(t_rt vars, t_ray ray, t_vec3 *surf_norm, t_vec3 *at)
{
	int			x;
	float		t;
	int			res;
	float		min;

	x = -1;
	res = -1;
	min = 2147483647;
	while (++x < vars.count_sph)
	{
		/*debug*/printf("id:%d\n", x);
		t = has_hit_sphere(vars.sph[x].orig, vars.sph[x].rad, ray);
		/*debug*/printf("has_hit_sphere:t:%f\n", t);
		if (t > 0.001 && t <= min)
		{
			res = x;
			min = t;
			*at = add_vec(ray.orig, mult_vec_scalar(ray.vector, t));
			*surf_norm = get_surf_norm(ray, vars.sph[x].orig, t);
		}
	}
	return (res);
}

t_vec3	simulate_fuzz(t_vec3 bounce_ray, float fuzz, t_uint *seed)
{
	t_vec3	res;

	if (fuzz > 1)
		fuzz = 1;
	res = add_vec(bounce_ray, mult_vec_scalar(rand_unit_vec(seed), fuzz));
	return (res);
}

/*
 * get reflected ray direction when when surface material is metal/reflective
 * formula: in_ray - (2 * dot(in_ray, surf_norm) * surf_norm)
 * dot(...) is the magnitude, (scaling in_ray to surf_norm)
 * * surf_norm
 * = magnitude * dir
 */
t_vec3	mat_metal(t_vec3 incoming_ray, t_vec3 surf_norm, \
float fuzz, t_uint *seed)
{
	t_vec3	bounce_ray;
	float		magnitude;

	magnitude = 2 * (scalar_product(incoming_ray, surf_norm));
	bounce_ray = mult_vec_scalar(surf_norm, magnitude);
	bounce_ray = unit_vec3(subtract_vec(incoming_ray, bounce_ray));
	if (fuzz > 0.0)
		bounce_ray = simulate_fuzz(bounce_ray, fuzz, seed);
	return (bounce_ray);
}

/* get reflected ray direction when when surface material is diffuse */
t_vec3	mat_lambertian(t_vec3 surf_norm, t_uint *seed)
{
	t_vec3	res;

	res = add_vec(surf_norm, rand_vec(seed)); //rand_unit_vec
	if (is_near_zero(res))
		res = surf_norm;
	return (res);
}

/*
 * child function in sample_pixels
 * checks if ray hits any object
 * defines what color should the ray be
 */
t_vec3	ray_color(t_rt vars, t_ray ray, t_uchar ray_bounce, \
t_uint *seed)
{
	float		t;
	int			state;
	t_ray		bounce;
	t_vec3		surf_norm;

	if (ray_bounce <= 0)
		return (new_vec3(0, 0, 0));
	state = hit(vars, ray, &surf_norm, &bounce.orig); //assigns surf_norm
	if (state >= 0)
	{
		if (vars.sph[state].mat.type == METAL)
			bounce.vector = mat_metal(ray.vector, surf_norm, 0, seed);
		else if (vars.sph[state].mat.type == DIFFUSE)
			bounce.vector = mat_lambertian(surf_norm, seed);
		return (mult_vec(ray_color(vars, bounce, ray_bounce - 1, seed), \
vars.sph[state].mat.albedo));
// 0.5)); //weaken its color reflectance by 50% everytime it bounce

// mult_vec_scalar(vars.sph[state].mat.albedo, 0.8)));
// 		return (new_vector3d(0.5*255*(surf_norm.x+1),
// 0.5*255*(surf_norm.y+1),
// 0.5*255*(surf_norm.z+1)));
	}

	/* else render sky bg */
	ray.vector.y /= len_vec3(ray.vector); //unit vector
	t = (ray.vector.y + 1) / 2;
	// vec.y ranges from -1 to 1, add 1 makes it positive, div 2 makes it 1
	return (lerp_rgb(vars.color_bg[1], vars.color_bg[0], t));
	// return (split_rgb(lerp_hsv(vars.color_bg[1], vars.color_bg[0], t)));
}

// t_vector3d	ray_color_loop(t_vars vars, t_ray ray, unsigned int *seed)
// {
// 	int			k;
// 	float		t;
// 	t_ray		bounce;
// 	t_vector3d	surf_norm;
// 	t_vector3d	color;

// 	k = -1;
// 	bounce = ray;
// 	color = new_vector3d(1, 1, 1);

// 	t = (ray.vector.y + 1) / 2;
// 	t_vector3d sky = split_rgb(lerp_hsv(vars.color_bg[1], vars.color_bg[0], t));
// 	float factor = 1;
// 	color = sky;
// 	while (++k < vars.ray_bounce)
// 	{
// 		if (hit(vars, bounce, &surf_norm, &bounce.orig))
// 		{
// 			bounce.vector = rand_on_hemisphere(seed, surf_norm);
// 			factor /= 2;
// 		}
// 		else
// 			color = mult_vec_scalar(sky, factor);
// 	}
// 	return (color);
// }

// int	ray_color(t_vars vars, t_ray ray)
// {
// 	float		t;
// 	t_vector3d	pt_ray;
// 	// float		ratio = 1 / vars.sample_per_pixel;

// 	(void)	vars;

// 	// ray_norm = norm_vector3d(ray.vector);
// 	// if (has_hit_sphere(new_vector3d(0, 0, -1), radius, ray))
// 		// return (0xFF8080);

// 	if (hit(vars, 2147483647, &pt_ray))
// 		return (create_rgb(0.5*255*(pt_ray.x+1),
// 0.5*255*(pt_ray.y+1),
// 0.5*255*(pt_ray.z+1)));

// 	/* else render sky bg */
// 	// ray_norm = ray.vector;
// 	t = (ray.vector.y + 1) / 2;
// 	// /*debug*/printf("ray_color:t:%f ray.y:%f %f\n", t, ray.vector.y, ray_norm.y);
// 	return (lerp_hsv(vars.color_bg[1], vars.color_bg[0], t));
// }