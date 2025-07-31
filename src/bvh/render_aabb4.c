/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_aabb4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:02:19 by hsim              #+#    #+#             */
/*   Updated: 2025/07/31 09:48:11 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	get_vec_min(t_vec3 j, t_vec3 k)
{
	t_vec3	pt;

	pt.x = fmin(j.x, k.x);
	pt.y = fmin(j.y, k.y);
	pt.z = fmin(j.z, k.z);
	return (pt);
}

t_vec3	get_vec_max(t_vec3 j, t_vec3 k)
{
	t_vec3	pt;

	pt.x = fmax(j.x, k.x);
	pt.y = fmax(j.y, k.y);
	pt.z = fmax(j.z, k.z);
	return (pt);
}

t_vec3	get_rotated_point(t_obj obj, int n[3])
{
	t_vec3		pt;

	// pt.x = (n[X] * obj.bbox_rot[X].max) + ((1 - n[X]) * obj.bbox_rot[X].min);
	// pt.y = (n[Y] * obj.bbox_rot[Y].max) + ((1 - n[Y]) * obj.bbox_rot[Y].min);
	// pt.z = (n[Z] * obj.bbox_rot[Z].max) + ((1 - n[Z]) * obj.bbox_rot[Z].min);
	pt.x = (n[X] * obj.bbox[X].max) + ((1 - n[X]) * obj.bbox[X].min);
	pt.y = (n[Y] * obj.bbox[Y].max) + ((1 - n[Y]) * obj.bbox[Y].min);
	pt.z = (n[Z] * obj.bbox[Z].max) + ((1 - n[Z]) * obj.bbox[Z].min);

	// /*debug*/debug_print_bbox("rot_bbox", obj.bbox);
	// /*debug*/debug_print_vec("bf_rot", pt);
	pt = quaternion_rotate_adv(pt, obj.rotate, 1);
	// /*debug*/debug_print_vec("af_rot", pt);
	return (pt);
}

//static
static void	rotate_point(t_obj obj, int n[3], t_vec3 *min, t_vec3 *max)
{
	t_vec3	pt;

	n[Z] = -1;
	while (++n[Z] < 2)
	{
		pt = get_rotated_point(obj, n);
		*min = get_vec_min(*min, pt);
		*max = get_vec_max(*max, pt);
		// /*debug*/debug_print_vec("min", *min);
		// /*debug*/debug_print_vec("max", *max);
	}
}

// void	aabb_rotate(t_obj src, t_interval dest[3])
void	aabb_rotate(t_obj obj, t_interval dest[3])
{
	t_vec3	min;
	t_vec3	max;
	int		n[3];

	n[X] = -1;
	n[Y] = -1;
	n[Z] = -1;
	min = new_vec3(2147483648, 2147483648, 2147483648);
	max = new_vec3(-2147483647, -2147483647, -2147483647);
	while (++n[X] < 2)
	{
		n[Y] = -1;
		while (++n[Y] < 2)
			rotate_point(obj, n, &min, &max);
	}
	aabb(min, max, dest);
}

// void	aabb_translate(t_obj obj, t_vec3 offset, t_interval res[3])
void	aabb_translate(t_obj obj, t_interval res[3], t_vec3 offset)
{
	res[X].min = obj.bbox[X].min + offset.x;
	res[X].max = obj.bbox[X].max + offset.x;
	res[Y].min = obj.bbox[Y].min + offset.y;
	res[Y].max = obj.bbox[Y].max + offset.y;
	res[Z].min = obj.bbox[Z].min + offset.z;
	res[Z].max = obj.bbox[Z].max + offset.z;
}

t_vec3	get_bbox_center(t_interval bbox[3])
{
	t_vec3	center;

	center.x = (bbox[X].min + bbox[X].max) / 2;
	center.y = (bbox[Y].min + bbox[Y].max) / 2;
	center.z = (bbox[Z].min + bbox[Z].max) / 2;
	return (center);
}