/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:27:39 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/24 21:52:20 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// ambient
t_colour	ambient(t_hit *hit, t_ambient amb)
{
	t_colour	ambient_col;

	ambient_col = colour_multiply(hit->obj->colour, amb.colour);
	return (colour_scale(ambient_col, amb.intensity));
}

// diffuse
t_colour	diffuse(t_hit *hit, t_light *light)
{
	t_vec3	light_dir;
	float		diffuse_intensity;
	t_colour	diffuse_col;
	t_colour	material_col;
	
	// vector from intersection to light, normalized
	light_dir = vector_normalize(vector_subtract(light->position, hit->point));

	// dot product btw light dir and surface normal
	diffuse_intensity = dot_product(hit->normal, light_dir);
	if (diffuse_intensity < 0)
		diffuse_intensity = 0;
	
	// use obj's colour
	material_col = hit->obj->material.albedo;
	diffuse_col = colour_multiply(material_col, light->colour);
	diffuse_col = colour_scale(diffuse_col, light->brightness * diffuse_intensity);
	return (diffuse_col);
}

// specular
t_colour	specular(t_hit *hit, t_light *light, t_camera *camera)
{
	t_vec3	light_dir;
	t_vec3	view_dir;
	t_vec3	reflected;
	float		intensity;
	t_colour	col;

	// get dir from intersection to light & camera
	// > reflect incoming light vector ard the surface normal
	light_dir = vector_normalize(vector_subtract(light->position, hit->point));
	view_dir = vector_normalize(vector_subtract(camera->position, hit->point));
	reflected = reflect(vector_negate(light_dir), hit->normal);
	
	// get the angle btw reflected vector and the viewer
	intensity = dot_product(reflected, view_dir);
	if (intensity < 0)
		intensity = 0;
	
	// apply phong spec to get reflected dot intensity
	intensity = powf(intensity, hit->obj->material.shininess);

	// scale light col by intensity
	col = colour_scale(light->colour, intensity);
	return (col);
}

// final colour (ambient + diffuse + specular)
t_colour	light_col(t_hit *hit, t_scene *scene)
{
	t_colour	ambient_col;
	t_colour	diffuse_col;
	t_colour	specular_col;
	t_colour	final_col;

	ambient_col = ambient(hit, scene->ambient);
	diffuse_col = diffuse(hit, &scene->light);
	specular_col = specular(hit, &scene->light, &scene->camera);
	final_col = colour_add(ambient_col, diffuse_col);
	final_col = colour_add(final_col, specular_col);
	final_col = colour_clamp(final_col);
	return (final_col);
}
