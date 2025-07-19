/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:27:39 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/19 17:29:59 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// ambient
t_col	ambient(t_hit *hit, t_ambient amb)
{
	t_col	ambient_col;

	ambient_col = mult_vec(hit->obj->material.albedo, amb.colour);
	return (mult_vec_scalar(ambient_col, amb.intensity));
}

/*
 * brief: adds light col to albedo
 * mult with brightness and intensity (how much surface hits light)
 */
t_col	diffuse(t_rt *rt, t_hit *point, float intensity)
{
	t_col	light_contribution;

	light_contribution = mult_vec(point->obj->material.albedo,
			rt->light.colour);
	light_contribution = mult_vec_scalar(light_contribution,
			rt->light.brightness * intensity);
	// /*debug*/printf("light_contribution: (%f, %f, %f)\n", light_contribution.x, light_contribution.y, light_contribution.z);
	return (light_contribution);
}

/*
 * brief: get rand offset light post within radius
 * used to get soft shadow
 * light origin > offset > get new rand light pos
 */
static t_vec3	randomized_light_pos(t_rt *rt, t_uint *seed)
{
	t_vec3	rand_light_pos;
	t_vec3	rand_offset;

	rand_light_pos = rt->light.pos;
	rand_offset = mult_vec_scalar(rand_unit_vec(seed), LIGHT_RADIUS);
	rand_light_pos = add_vec(rand_light_pos, rand_offset);
	return (rand_light_pos);
}

/* 
 * brief: get total light col on that point
 * get t, and direction > check if not shadowed
 * if not > get dot prod > check if prod > 0 (pretty much same dir)
 * return diffused light col + albedo on that point > else black if in shadow
 */
t_col	get_total_light(t_rt *rt, t_hit *point, t_uint *seed)
{
	t_vec3		light_pos;
	t_vec3		light_dir;
	float		t;
	float		diffuse_intensity;

	light_pos = randomized_light_pos(rt, seed);
	light_dir = subtract_vec(light_pos, point->at);
	t = len_vec3(light_dir);
	light_dir = unit_vec3(light_dir);
	if (!is_shadowed(rt, point, light_dir, t))
	{
		diffuse_intensity = scalar_product(point->surf_norm, light_dir);
		if (diffuse_intensity > 0)
			return (diffuse(rt, point, diffuse_intensity));
	}
	return (new_vec3(0, 0, 0));
}

/* 
 * brief: sample light to get average col on that point
 * sampling n controlled offset light rays to get avg for soft shadows
 * get total and avg by n samples
 */
t_col	sample_direct_light(t_rt *rt, t_hit *point, t_uint *seed)
{
	t_col	total_light;
	int		samples;
	int		i;

	if (!point || !point->obj || rt->light.brightness <= 0)
		return (new_vec3(0, 0, 0));
	total_light = new_vec3(0, 0, 0);
	samples = SAMPLE_SOFT_SHADOW;
	i = -1;
	while (++i < samples)
		total_light = add_vec(total_light, get_total_light(rt, point, seed));
	// /*debug*/printf("before avg: %f %f %f\n", total_light.x, total_light.y, total_light.z);
	return (div_vec_scalar(total_light, samples));
}

// diffuse
// t_colour	diffuse(t_hit *hit, t_light *light)
// {
// 	t_vec3		light_dir;
// 	float		diffuse_intensity;
// 	t_colour	diffuse_col;
// 	t_colour	material_col;

// 	// vector from intersection to light, normalized
// 	light_dir = unit_vec3(subtract_vec(light->pos, hit->at));

// 	// dot product btw light dir and surface normal
// 	diffuse_intensity = scalar_product(hit->surf_norm, light_dir);
// 	if (diffuse_intensity < 0)
// 		diffuse_intensity = 0;

// 	// use obj's colour
// 	material_col = hit->obj->material.albedo;
// 	diffuse_col = mult_vec(material_col, light->colour);
// 	diffuse_col = mult_vec_scalar(diffuse_col, light->brightness * diffuse_intensity);
// 	return (diffuse_col);
// }

// // specular
// t_colour	specular(t_hit *hit, t_light *light, t_camera *camera)
// {
// 	t_vec3		light_dir;
// 	t_vec3		view_dir;
// 	t_vec3		reflected;
// 	float		intensity;
// 	t_colour	col;

// 	// get dir from intersection to light & camera
// 	// > reflect incoming light vector ard the surface normal
// 	light_dir = unit_vec3(subtract_vec(light->pos, hit->at));
// 	view_dir = unit_vec3(subtract_vec(camera->pos, hit->at));
// 	reflected = reflect(mult_vec_scalar(light_dir, -1), hit->surf_norm);
	
// 	// get the angle btw reflected vector and the viewer
// 	intensity = scalar_product(reflected, view_dir);
// 	if (intensity < 0)
// 		intensity = 0;
	
// 	// apply phong spec to get reflected dot intensity
// 	intensity = powf(intensity, hit->obj->material.shininess);

// 	// scale light col by intensity
// 	col = mult_vec_scalar(light->colour, intensity);
// 	return (col);
// }

// // final colour (ambient + diffuse + specular)
// t_colour	light_col(t_hit *hit, t_rt *rt)
// {
// 	t_colour	ambient_col;
// 	t_colour	diffuse_col;
// 	t_colour	specular_col;
// 	t_colour	final_col;
// 	int			shadow;

// 	shadow = is_shadow(rt, hit->at, hit->surf_norm);
// 	if (shadow)
// 		return (ambient(hit, rt->ambient));
// 	ambient_col = ambient(hit, rt->ambient);
// 	diffuse_col = diffuse(hit, &rt->light);
// 	specular_col = specular(hit, &rt->light, &rt->camera);
// 	final_col = add_vec(ambient_col, diffuse_col);
// 	return (add_vec(final_col, specular_col));
// }