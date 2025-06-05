/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:19:29 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/05 13:31:11 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void print_vector(const char *label, t_vector v)
{
    printf("%s: (%.2f, %.2f, %.2f)\n", label, v.x, v.y, v.z);
}

void print_colour(const char *label, t_colour c)
{
    printf("%s: (%u, %u, %u)\n", label, c.r, c.g, c.b);
}

void print_ambient(t_ambient *a)
{
    printf("Ambient ratio: %.2f\n", a->ratio);
    print_colour("Ambient colour", a->colour);
}

void print_camera(t_camera *c)
{
    print_vector("Camera position", c->position);
    print_vector("Camera orientation", c->orientation);
    printf("Camera FOV: %u\n", c->fov);
}

void print_light(t_light *l)
{
    print_vector("Light position", l->position);
    printf("Light brightness: %.2f\n", l->brightness);
    print_colour("Light colour", l->colour);
}

void print_object(t_object *obj)
{
    if (obj->type == obj_sphere)
	{
        printf("Sphere:\n");
        print_vector("  Position", obj->obj.sphere.position);
        printf("  Diameter: %.2f\n", obj->obj.sphere.diameter);
    }
	else if (obj->type == obj_plane)
	{
        printf("Plane:\n");
        print_vector("  Position", obj->obj.plane.position);
        print_vector("  Normal", obj->obj.plane.normal);
    }
	else if (obj->type == obj_cylinder)
	{
        printf("Cylinder:\n");
        print_vector("  Position", obj->obj.cylinder.position);
        print_vector("  Axis", obj->obj.cylinder.axis);
        printf("  Diameter: %.2f\n", obj->obj.cylinder.diameter);
        printf("  Height: %.2f\n", obj->obj.cylinder.height);
    }
    print_colour("  Colour", obj->colour);
}

void print_scene(t_scene *scene)
{
    print_ambient(&scene->ambient);
    print_camera(&scene->camera);
    print_light(&scene->light);
    for (size_t i = 0; i < scene->obj_count; i++)
        print_object(&scene->objects[i]);
}