/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:13:15 by hsim              #+#    #+#             */
/*   Updated: 2025/07/10 09:02:51 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_obj	new_sphere(t_vec3 position, float sph_radius, t_vec3 color, t_uchar mat_type)
// {
// 	t_obj	target;

// 	target.type = SPHERE;
// 	target.sph.pos = position;
// 	target.sph.rad = sph_radius;
// 	target.material.albedo = color;
// 	target.material.type = mat_type;
// 	create_bbox(&target, target.bbox);
// 	return (target);
// }

// /*
//  * returns obj function that returns a malloc-ed pointer
//  * for specified obj_type
//  */
// void	init_new_obj_func2(t_obj (*add_obj[])(t_vec3, float, t_vec3, t_uchar))
// {
// 	add_obj[SPHERE] = new_sphere;
// }
