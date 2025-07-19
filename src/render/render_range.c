/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_range.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:42:33 by hsim              #+#    #+#             */
/*   Updated: 2025/07/19 16:12:55 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

// brief: backbone of interval and bounding box math (intersection + spatial organization)

/* used with intervals or bounding box */
float	get_min(float a, float v)
{
	if (a <= v)
		return (a);
	return (v);
}

/* used with intervals or bounding box */
float	get_max(float a, float v)
{
	if (a >= v)
		return (a);
	return (v);
}

/* 
 * brief: check if 2 intervals overlap
 * finds max lower bounds and min upper bounds
 * checks if ray's valid range overlaps with object's bounding box
 * intersection tests for bvh
 */
bool	overlap(float t[2], float t2[2])
{
	float	t_min;
	float	t_max;

	t_min = get_max(t[0], t2[0]);
	t_max = get_min(t[1], t2[1]);
	return (t_min < t_max);
}

/*
 * brief: creates a new interval smallest minimum and the largest maximum of 2 intervals
 * sets min = smallest value between a.min & b.min
 * same applies to max
 * used to combine or expand intervals - aabb combining 2 boxes that enclose multiple objects
 */ 
t_interval	interval(t_interval a, t_interval v)
{
	t_interval	res;

	res.min = get_min(a.min, v.min);
	res.max = get_max(a.max, v.max);
	return (res);
}

/*
 * creates new interval struct with given min and max
 * used to define valid range for ray intersections
 * used for bounding box and spatial partitioning
 */
t_interval	new_interval(float min, float max)
{
	t_interval	res;

	res.min = min;
	res.max = max;
	return (res);
}