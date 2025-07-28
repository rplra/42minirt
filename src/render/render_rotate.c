/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:08:23 by hsim              #+#    #+#             */
/*   Updated: 2025/07/27 22:14:40 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	rotate_ray_to_local(t_quat q_rot, t_ray ray)
{
	t_ray	ray_rotate;

	ray_rotate.orig = global_to_local(q_rot, ray.orig);
	ray_rotate.vector = global_to_local(q_rot, ray.vector);
	return (ray_rotate);
}
