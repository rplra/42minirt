/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:19:29 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/02 11:14:06 by rraja-az         ###   ########.fr       */
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
		camera->position.x, camera->position.y, camera->position.z);
	printf("Camera ort: (x=%f, y=%f, z=%f)\n",
		camera->orientation.x, camera->orientation.y, camera->orientation.z);
	printf("Camera fov: %u\n", camera->fov);
}

void print_light(const t_light *light)
{
    printf("Light pos: (x=%f, y=%f, z=%f)\n",
		light->position.x, light->position.y, light->position.z);
	printf("Light brightness: %f\n", light->brightness);
	printf("Light colour: (r=%f, g=%f, b=%f)\n",
		light->colour.r, light->colour.g, light->colour.b);
}

void print_plane(const t_object *obj)
{
    printf("Plane pos: (x=%f, y=%f, z=%f)\n",
        obj->obj.plane.position.x, obj->obj.plane.position.y, obj->obj.plane.position.z);
    printf("Plane normal: (x=%f, y=%f, z=%f)\n",
        obj->obj.plane.normal.x, obj->obj.plane.normal.y, obj->obj.plane.normal.z);
    printf("Plane colour: (r=%f, g=%f, b=%f)\n",
        obj->colour.r, obj->colour.g, obj->colour.b);
}

void	print_sphere(const t_object *obj)
{
	printf("Sphere pos: (x=%f, y=%f, z=%f)\n",
        obj->obj.sph.position.x, obj->obj.sph.position.y, obj->obj.sph.position.z);
	printf("Sphere diameter: %f\n", obj->obj.sph.diameter);
	printf("Sphere colour: (r=%f, g=%f, b=%f)\n",
        obj->colour.r, obj->colour.g, obj->colour.b);
}

void	print_cylinder(const t_object *obj)
{
	printf("Cylinder pos: (x=%f, y=%f, z=%f)\n",
        obj->obj.cyl.position.x, obj->obj.cyl.position.y, obj->obj.cyl.position.z);
	printf("Cylinder axis: (x=%f, y=%f, z=%f)\n",
		obj->obj.cyl.axis.x, obj->obj.cyl.axis.y, obj->obj.cyl.axis.z);
	printf("Cylinder diameter: %f\n", obj->obj.cyl.diameter);
	printf("Cylinder height: %f\n", obj->obj.cyl.height);
	printf("Cylinder colour: (r=%f, g=%f, b=%f)\n",
        obj->colour.r, obj->colour.g, obj->colour.b);
}