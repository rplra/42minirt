/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:58:49 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/21 12:53:00 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// we get the surface normal to determine how light reacts with the surface at the intersection point
t_vector	get_normal(t_vector	intersection_point, t_object *obj)
{
	if (!obj)
		return ((t_vector){0,0,0});
	if (obj->type == obj_plane)
		return (obj->obj.plane.normal);
	else if (obj->type == obj_sphere)
		return (vector_normalize(subtract(intersection_point, obj->obj.sphere.position)));
	else if (obj->type == obj_cylinder)
		return (get_cylinder_normal(intersection_point, obj->obj.cylinder));
}

// normalize cylinder
t_vector	get_cylinder_normal(t_vector intersection_point, t_cylinder cylinder)
{
	t_vector	base_from_intersection;
	t_vector	distance_to_axis;
	t_vector	axis_point;
	t_vector	normal;

	base_from_intersection = vector_subtract(intersection_point, cy->axis);
	distance_to_axis = dot(base_from_intersection, cy->axis);
	// check if the intersection happens at the bottom cap
	if (distance_to_axis <= 0)
		return (-cy->axis);
	// check if the intersection happens at the top cap
	else if (distance_to_axis >= cy->height)
		return (cy->axis);
	// else, intersection happens at the sides of the cylinder
	else
	{
		axis_point = vector_add(cy->center, vector_scale(cy->axis, distance_to_axis);
		normal = intersection_point - axis_point;
		return (vector_normalize(normal));
	}
}


