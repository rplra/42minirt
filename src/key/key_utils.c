/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:52:32 by hsim              #+#    #+#             */
/*   Updated: 2025/08/18 16:08:08 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_uint	get_obj_index(t_obj *obj, int obj_count, t_uint id)
{
	int	i;

	i = -1;
	while (++i < obj_count)
	{
		if (obj[i].id == id)
			return (i);
	}
	return (0);
}

t_uint	get_light_index(t_obj *obj, int obj_count)
{
	int	i;

	i = -1;
	while (++i < obj_count)
	{
		if (obj[i].material.type == LIGHT)
			return (i);
	}
	return (0);
}
