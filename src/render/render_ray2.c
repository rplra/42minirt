/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:41:25 by hsim              #+#    #+#             */
/*   Updated: 2025/06/25 11:48:03 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* assigns ray to value specified in arguments */
t_ray	new_ray(t_vec3 origin, t_vec3 dir)
{
	t_ray	ray;

	ray.orig = origin;
	ray.vector = dir;
	return (ray);
}