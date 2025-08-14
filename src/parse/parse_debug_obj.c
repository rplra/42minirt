/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_debug_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:39:24 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/14 17:55:01 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_plane(const t_obj *obj)
{
	printf("Plane pos: (x=%f, y=%f, z=%f)\n", obj->plane.pos.x,
		obj->plane.pos.y, obj->plane.pos.z);
	printf("Plane normal: (x=%f, y=%f, z=%f)\n", obj->plane.normal.x,
		obj->plane.normal.y, obj->plane.normal.z);
	printf("Plane colour: (r=%f, g=%f, b=%f)\n", obj->material.albedo.R,
		obj->material.albedo.G, obj->material.albedo.B);
}

void	print_sphere(const t_obj *obj)
{
	printf("Sphere pos: (x=%f, y=%f, z=%f)\n", obj->sph.pos.x, obj->sph.pos.y,
		obj->sph.pos.z);
	printf("Sphere diameter: %f\n", obj->sph.rad);
	printf("Sphere colour: (r=%f, g=%f, b=%f)\n", obj->material.albedo.R,
		obj->material.albedo.G, obj->material.albedo.B);
}

void	print_cylinder(const t_obj *obj)
{
	printf("Cylinder pos: (x=%f, y=%f, z=%f)\n", obj->cyl.pos.x, obj->cyl.pos.y,
		obj->cyl.pos.z);
	printf("Cylinder axis: (x=%f, y=%f, z=%f)\n", obj->cyl.axis.x,
		obj->cyl.axis.y, obj->cyl.axis.z);
	printf("Cylinder diameter: %f\n", obj->cyl.rad);
	printf("Cylinder height: %f\n", obj->cyl.height);
	printf("Cylinder colour: (r=%f, g=%f, b=%f)\n", obj->material.albedo.R,
		obj->material.albedo.G, obj->material.albedo.B);
}
