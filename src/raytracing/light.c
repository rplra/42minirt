/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:27:39 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/07 10:31:43 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// ambient
t_colour	ambient(t_hit *hit, t_ambient amb)
{
	t_colour	ambient_col;

	ambient_col = mult_vec(hit->obj->material.albedo, amb.colour);
	return (mult_vec_scalar(ambient_col, amb.intensity));
}

// diffuse
t_colour	diffuse(t_hit *hit, t_light *light)
{
	t_vec3		light_dir;
	float		diffuse_intensity;
	t_colour	diffuse_col;
	t_colour	material_col;
	
	// vector from intersection to light, normalized
	light_dir = unit_vec3(subtract_vec(light->pos, hit->at));

	// dot product btw light dir and surface normal
	diffuse_intensity = scalar_product(hit->surf_norm, light_dir);
	if (diffuse_intensity < 0)
		diffuse_intensity = 0;
	
	// use obj's colour
	material_col = hit->obj->material.albedo;
	diffuse_col = mult_vec(material_col, light->colour);
	diffuse_col = mult_vec_scalar(diffuse_col, light->brightness * diffuse_intensity);
	return (diffuse_col);
}

// specular
t_colour	specular(t_hit *hit, t_light *light, t_camera *camera)
{
	t_vec3		light_dir;
	t_vec3		view_dir;
	t_vec3		reflected;
	float		intensity;
	t_colour	col;

	// get dir from intersection to light & camera
	// > reflect incoming light vector ard the surface normal
	light_dir = unit_vec3(subtract_vec(light->pos, hit->at));
	view_dir = unit_vec3(subtract_vec(camera->pos, hit->at));
	reflected = reflect(mult_vec_scalar(light_dir, -1), hit->surf_norm);
	
	// get the angle btw reflected vector and the viewer
	intensity = scalar_product(reflected, view_dir);
	if (intensity < 0)
		intensity = 0;
	
	// apply phong spec to get reflected dot intensity
	intensity = powf(intensity, hit->obj->material.shininess);

	// scale light col by intensity
	col = mult_vec_scalar(light->colour, intensity);
	return (col);
}

// final colour (ambient + diffuse + specular)
t_colour	light_col(t_hit *hit, t_rt *rt)
{
	t_colour	ambient_col;
	t_colour	diffuse_col;
	t_colour	specular_col;
	t_colour	final_col;

	ambient_col = ambient(hit, rt->ambient);
	diffuse_col = diffuse(hit, &rt->light);
	specular_col = specular(hit, &rt->light, &rt->camera);
	final_col = add_vec(ambient_col, diffuse_col);
	final_col = add_vec(final_col, specular_col);
	// final_col = colour_clamp(final_col);
	return (final_col);
}
