/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_range.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:42:33 by hsim              #+#    #+#             */
/*   Updated: 2025/07/11 12:38:40 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

float	get_min(float a, float v)
{
	if (a <= v)
		return (a);
	return (v);
}

float	get_max(float a, float v)
{
	if (a >= v)
		return (a);
	return (v);
}

bool	overlap(float t[2], float t2[2])
{
	float	t_min;
	float	t_max;

	t_min = get_max(t[0], t2[0]);
	t_max = get_min(t[1], t2[1]);
	return (t_min < t_max);
}

/*
 * sets min = smallest value between a.min & b.min
 * same applies to max
 */
t_interval	interval(t_interval a, t_interval v)
{
	t_interval	res;

	res.min = get_min(a.min, v.min);
	res.max = get_max(a.max, v.max);
	return (res);
}

t_interval	new_interval(float min, float max)
{
	t_interval	res;

	res.min = min;
	res.max = max;
	return (res);
}