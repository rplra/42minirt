/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:19:29 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/16 22:38:04 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_ambient(const t_ambient *ambient)
{
	printf("Ambient ratio: %f\n", ambient->intensity);
	debug_print_vec("Ambient", ambient->colour);
}

void	print_camera(const t_camera *camera)
{
	debug_print_vec("Camera pos", camera->pos);
	debug_print_vec("Camera ort", camera->lookat_ori);
	printf("Camera fov: %f\n", camera->hfov);
}

void	print_light(const t_light *light)
{
	debug_print_vec("Light pos", light->pos);
	printf("Light brightness: %f\n", light->brightness);
	debug_print_vec("Light col", light->colour);
}

void	print_obj(const t_obj *obj)
{
	if (obj->type == PLANE)
	{
		debug_print_vec("Plane pos", obj->plane.pos);
		debug_print_vec("Plane normal", obj->plane.normal);
		debug_print_vec("Plane col", obj->material.albedo);
	}
	else if (obj->type == SPHERE)
	{
		debug_print_vec("Sphere pos", obj->sph.pos);
		printf("Sphere diameter: %f\n", obj->sph.rad);
		debug_print_vec("Sphere col", obj->material.albedo);
	}
	else if (obj->type == CYLINDER)
	{
		debug_print_vec("Cylinder pos", obj->cyl.pos);
		debug_print_vec("Cylinder axis", obj->cyl.axis);
		printf("Cylinder diameter: %f\n", obj->cyl.rad);
		printf("Cylinder height: %f\n", obj->cyl.height);
		debug_print_vec("Cylinder col", obj->material.albedo);
	}
	else
		printf("Debug error: Unkown obj\n");
}
