/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:19:29 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/11 16:49:23 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void print_ambient(const t_ambient *ambient)
{
	printf("Ambient ratio: %f\n", ambient->intensity);
	printf("Ambient colour: (r=%f, g=%f, b=%f)\n",
ambient->colour.r, ambient->colour.g, ambient->colour.b);
}

void print_camera(const t_camera *camera)
{
    printf("Camera pos: (x=%f, y=%f, z=%f)\n",
		camera->pos.x, camera->pos.y, camera->pos.z);
	printf("Camera ort: (x=%f, y=%f, z=%f)\n",
		camera->vup.x, camera->vup.y, camera->vup.z);
	printf("Camera fov: %f\n", camera->vfov);
}

void print_light(const t_light *light)
{
    printf("Light pos: (x=%f, y=%f, z=%f)\n",
		light->pos.x, light->pos.y, light->pos.z);
	printf("Light brightness: %f\n", light->brightness);
	printf("Light colour: (r=%f, g=%f, b=%f)\n",
		light->colour.r, light->colour.g, light->colour.b);
}

void print_plane(const t_obj *obj)
{
    printf("Plane pos: (x=%f, y=%f, z=%f)\n",
        obj->plane.pos.x, obj->plane.pos.y, obj->plane.pos.z);
    printf("Plane normal: (x=%f, y=%f, z=%f)\n",
        obj->plane.normal.x, obj->plane.normal.y, obj->plane.normal.z);
    printf("Plane colour: (r=%f, g=%f, b=%f)\n",
        obj->material.albedo.r, obj->material.albedo.g, obj->material.albedo.b);
}

void	print_sphere(const t_obj *obj)
{
	printf("Sphere pos: (x=%f, y=%f, z=%f)\n",
        obj->sph.pos.x, obj->sph.pos.y, obj->sph.pos.z);
	printf("Sphere diameter: %f\n", obj->sph.rad);
	printf("Sphere colour: (r=%f, g=%f, b=%f)\n",
        obj->material.albedo.r, obj->material.albedo.g, obj->material.albedo.b);
}

void	print_cylinder(const t_obj *obj)
{
	printf("Cylinder pos: (x=%f, y=%f, z=%f)\n",
        obj->cyl.pos.x, obj->cyl.pos.y, obj->cyl.pos.z);
	printf("Cylinder axis: (x=%f, y=%f, z=%f)\n",
		obj->cyl.axis.x, obj->cyl.axis.y, obj->cyl.axis.z);
	printf("Cylinder diameter: %f\n", obj->cyl.rad);
	printf("Cylinder height: %f\n", obj->cyl.height);
	printf("Cylinder colour: (r=%f, g=%f, b=%f)\n",
        obj->material.albedo.r, obj->material.albedo.g, obj->material.albedo.b);
}