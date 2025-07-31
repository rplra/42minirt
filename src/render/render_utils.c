/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:18:14 by hsim              #+#    #+#             */
/*   Updated: 2025/07/31 10:15:28 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* checks if all vector values is near to zero */
bool	is_near_zero(t_vec3 vec)
{
	float	res[3];
	float	s;

	s = 0.001f;
	res[X] = fabs(vec.x);
	res[Y] = fabs(vec.y);
	res[Z] = fabs(vec.z);
	return ((res[X] < s) && (res[Y] < s) && (res[Z] < s));
}

/* assigns value in t_vec3 to float[3] */
void	vec3_to_arr(t_vec3 pt, float res[3])
{
	res[X] = pt.x;
	res[Y] = pt.y;
	res[Z] = pt.z;
}

void	swap_float(float t[2])
{
	float	tmp;

	if (t[0] > t[1])
	{
		/*debug*/printf("swap!\n");
		tmp = t[0];
		t[0] = t[1];
		t[1] = tmp;
	}
}

t_uint	get_obj_index(t_obj *obj, int obj_count, t_uint id)
{
	int	i;

	i = -1;
	while (++i <= obj_count)
	{
		if (obj[i].id == id)
			return (i);
	}
	return (0);
}