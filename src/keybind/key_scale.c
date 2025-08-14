/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:33:48 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/14 12:30:42 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	scale_key(int keycode)
{
	return (keycode == KEY_PLUS || keycode == KEY_MINUS);
}

float	scale_factor(int keycode)
{
	if (keycode == KEY_PLUS)
		return (SCALE_UP);
	if (keycode == KEY_MINUS)
		return (SCALE_DOWN);
	return (1.0f);
}

static void scale_obj(t_rt *rt, float scale)
{
	t_obj	*obj;
	t_vec3	n;
	int		id;

	id = get_obj_index(rt->obj, rt->obj_count, rt->sel.obj_index);
	obj = &rt->obj[id];
	if (obj->type == SPHERE)
		obj->sph.rad *= scale;
	else if (obj->type == CYLINDER)
	{
		obj->cyl.rad *= scale;
		obj->cyl.height *= scale;
		obj->cyl.coord[X] = mult_vec_scalar(obj->cyl.coord[X], scale);
		obj->cyl.coord[Y] = mult_vec_scalar(obj->cyl.coord[Y], scale);
		obj->cyl.d[0] = scalar_product(obj->cyl.axis, subtract_vec(obj->cyl.pos,
			mult_vec_scalar(obj->cyl.axis, obj->cyl.height / 2)));
		obj->cyl.d[1] = scalar_product(obj->cyl.axis, add_vec(obj->cyl.pos,
			mult_vec_scalar(obj->cyl.axis, obj->cyl.height / 2)));
		n = cross_product(obj->cyl.coord[X], obj->cyl.coord[Y]);
		obj->cyl.w = div_vec_scalar(n, scalar_product(n, n));
	}
	assign_bbox(obj);
}

void	handle_scale(t_rt *rt, int keycode)
{
	float	scale;

	if (!scale_key(keycode))
		return;
	scale = scale_factor(keycode);
	if (rt->sel.type == SEL_OBJ)
		scale_obj(rt, scale);
}

/* 
void	handle_scale(t_rt *rt, int keycode)
{
	int		id;
	t_obj	*obj;
	float	scale;

	if (!scale_key(keycode))
		return;
	scale = scale_factor(keycode);
	if (rt->sel.type == SEL_OBJ)
	{
		id = get_obj_index(rt->obj, rt->obj_count, rt->sel.obj_index);
		obj = &rt->obj[id];
		if (obj->type == SPHERE)
			obj->sph.rad *= scale;
		else if (obj->type == CYLINDER)
		{
			obj->cyl.rad *= scale;
			obj->cyl.height *= scale;
			obj->cyl.coord[X] = mult_vec_scalar(obj->cyl.coord[X], scale);
			obj->cyl.coord[Y] = mult_vec_scalar(obj->cyl.coord[Y], scale);
			obj->cyl.d[0] = scalar_product(obj->cyl.axis, subtract_vec(obj->cyl.pos, \
mult_vec_scalar(obj->cyl.axis, obj->cyl.height / 2)));
			obj->cyl.d[1] = scalar_product(obj->cyl.axis, add_vec(obj->cyl.pos, \
mult_vec_scalar(obj->cyl.axis, obj->cyl.height / 2)));
			t_vec3	n = cross_product(obj->cyl.coord[X], obj->cyl.coord[Y]);
			obj->cyl.w = div_vec_scalar(n, scalar_product(n, n));
		}
		assign_bbox(obj);
	}
}
*/