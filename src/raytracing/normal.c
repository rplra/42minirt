/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:58:49 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/02 10:15:47 by rraja-az         ###   ########.fr       */
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
		hit->normal = (t_vec3){0,0,0};
		return;
	}
	if (obj->type == PLANE)
		hit->normal = obj->obj.plane.normal;
	else if (obj->type == SPHERE)
		hit->normal = unit_vec3(subtract_vec(hit->point, obj->obj.sph.position));
	else if (obj->type == CYLINDER)
		hit->normal = get_cylinder_normal(hit->point, &obj->obj.cyl);
}

// normalize cylinder
t_vec3	get_cylinder_normal(t_vec3 point, t_cylinder *cy)
{
	t_vec3	base_from_intersection;
	float	distance_to_axis;
	t_vec3	axis_point;
	t_vec3	normal;

	base_from_intersection = subtract_vec(point, cy->axis);
	distance_to_axis = scalar_product(base_from_intersection, cy->axis);
	// check if the intersection happens at the bottom cap
	if (distance_to_axis <= 0)
		return (mult_vec_scalar(cy->axis, -1));
	// check if the intersection happens at the top cap
	else if (distance_to_axis >= cy->height)
		return (cy->axis);
	// else, intersection happens at the sides of the cylinder
	else
	{
		axis_point = add_vec(cy->position, mult_vec_scalar(cy->axis, distance_to_axis));
		normal = subtract_vec(point, axis_point);
		return (unit_vec3(normal));
	}
}


