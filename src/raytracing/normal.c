/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:58:49 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/24 10:35:34 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// we get the surface normal to determine how light reacts with the surface at the intersection point
void	get_normal(t_hit *hit)
{
	t_object	*obj;
	
	obj = hit->obj;
	if (!obj)
	{
		hit->normal = (t_vector){0,0,0};
		return;
	}
	if (obj->type == PLANE)
		hit->normal = obj->obj.plane.normal;
	else if (obj->type == SPHERE)
		hit->normal = vector_normalize(vector_subtract(hit->point, obj->obj.sphere.position));
	else if (obj->type == CYLINDER)
		hit->normal = get_cylinder_normal(hit->point, &obj->obj.cylinder);
}

// normalize cylinder
t_vector	get_cylinder_normal(t_vector point, t_cylinder *cy)
{
	t_vector	base_from_intersection;
	float		distance_to_axis;
	t_vector	axis_point;
	t_vector	normal;

	base_from_intersection = vector_subtract(point, cy->axis);
	distance_to_axis = dot_product(base_from_intersection, cy->axis);
	// check if the intersection happens at the bottom cap
	if (distance_to_axis <= 0)
		return (vector_negate(cy->axis));
	// check if the intersection happens at the top cap
	else if (distance_to_axis >= cy->height)
		return (cy->axis);
	// else, intersection happens at the sides of the cylinder
	else
	{
		axis_point = vector_add(cy->position, vector_scale(cy->axis, distance_to_axis));
		normal = vector_subtract(point, axis_point);
		return (vector_normalize(normal));
	}
}


