/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:08:07 by hsim              #+#    #+#             */
/*   Updated: 2025/08/14 17:31:50 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* compares which smaller and returns in as 1st param in t_interval */
t_interval	assign_min_max(float a, float v)
{
	t_interval	range;

	if (a <= v)
	{
		range.min = a;
		range.max = v;
	}
	else
	{
		range.min = v;
		range.max = a;
	}
	return (range);
}

t_vec3	get_bbox_center(t_interval bbox[3])
{
	t_vec3	center;

	center.x = (bbox[X].min + bbox[X].max) / 2;
	center.y = (bbox[Y].min + bbox[Y].max) / 2;
	center.z = (bbox[Z].min + bbox[Z].max) / 2;
	return (center);
}
