/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:02:19 by hsim              #+#    #+#             */
/*   Updated: 2025/08/22 12:50:10 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	get_rotated_point(t_obj obj, int n[3])
{
	t_vec3	pt;

	pt.x = (n[X] * obj.bbox[X].max) + ((1 - n[X]) * obj.bbox[X].min);
	pt.y = (n[Y] * obj.bbox[Y].max) + ((1 - n[Y]) * obj.bbox[Y].min);
	pt.z = (n[Z] * obj.bbox[Z].max) + ((1 - n[Z]) * obj.bbox[Z].min);
	pt = quaternion_rotate_adv(pt, obj.rotate, 1);
	return (pt);
}

// static
static void	rotate_point(t_obj obj, int n[3], t_vec3 *min, t_vec3 *max)
{
	t_vec3	pt;

	n[Z] = -1;
	while (++n[Z] < 2)
	{
		pt = get_rotated_point(obj, n);
		*min = get_vec_min(*min, pt);
		*max = get_vec_max(*max, pt);
	}
}

void	aabb_rotate(t_obj obj, t_interval dest[3])
{
	t_vec3	min;
	t_vec3	max;
	int		n[3];

	n[X] = -1;
	n[Y] = -1;
	n[Z] = -1;
	min = new_vec3(2147483648, 2147483648, 2147483648);
	max = new_vec3(-2147483647.0f, -2147483647.0f, -2147483647.0f);
	while (++n[X] < 2)
	{
		n[Y] = -1;
		while (++n[Y] < 2)
			rotate_point(obj, n, &min, &max);
	}
	aabb(min, max, dest);
}

void	aabb_translate(t_obj obj, t_interval res[3], t_vec3 offset)
{
	res[X].min = obj.bbox[X].min + offset.x;
	res[X].max = obj.bbox[X].max + offset.x;
	res[Y].min = obj.bbox[Y].min + offset.y;
	res[Y].max = obj.bbox[Y].max + offset.y;
	res[Z].min = obj.bbox[Z].min + offset.z;
	res[Z].max = obj.bbox[Z].max + offset.z;
}
