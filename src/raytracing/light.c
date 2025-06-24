/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:27:39 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/23 13:06:52 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// ambient
t_colour	ambient(t_object *obj, t_ambient amb)
{
	t_colour	ambient_col;

	ambient_col = colour_multiply(obj->colour, amb.colour);
	return (colour_scale(ambient_col, amb.intensity));
}

// diffuse
t_colour	diffuse(t_object *obj, t_light *light, t_vector intersection, t_vector normal)
{
	t_vector	light_dir;
	float		diffuse_intensity;
	t_colour	diffuse_col;
	t_colour	material_col;
	
	// vector from intersection to light, normalized
	light_dir = vector_normalize(vector_subtract(light->position, intersection));

	// dot product btw light dir and surface normal
	diffuse_intensity = dot_product(normal, light_dir);
	if (diffuse_intensity < 0)
		diffuse_intensity = 0;
	
	// use obj's colour
	material_col = obj->material.diffuse;
	diffuse_col = colour_multiply(material_col, light->colour);
	diffuse_col = colour_scale(diffuse_col, light->brightness *diffuse_intensity);
	return (diffuse_col);
}

// specular
t_colour	specular(t_object *obj, t_light *light, t_vector intersection, t_camera *camera)
{
	t_vector	light_dir;
	t_vector	view_dir;
	t_vector	reflected;
	float		reflect_dot;
	float		specular_intensity;
	t_colour	specular_colour;

	light_dir = vector_normalize(vector_subtract(light->position, intersection));
	view_dir = vector_normalize(vector_subtract(camera->position, intersection));
	reflected = reflect(vector_negate(light_dir), get_normal(intersection, obj)));
	
	reflect_dot = dot_product(reflected, view_dir);
	if (reflect_dot < 0)
		reflect_dot = 0;
	
	specular_intensity = powf(reflect_dot, obj->material.shininess);
	specular_colour = colour_scale(light->colour, light->brightness * obj->material.specular * specular_intensity);
	return (specular_colour);
}

// final colour (ambient + diffuse + specular)
