/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_translate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:27:03 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/14 12:01:52 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	translation_key(int keycode)
{
	return (keycode == KEY_W || keycode == KEY_S ||
			keycode == KEY_A || keycode == KEY_D ||
			keycode == KEY_Q || keycode == KEY_E);
}

t_vec3	translation_delta(int keycode)
{
	if (keycode == KEY_W)
		return (new_vec3(0, TRANSLATE, 0));
	if (keycode == KEY_S)
		return (new_vec3(0, -TRANSLATE, 0));
	if (keycode == KEY_A)
		return (new_vec3(-TRANSLATE, 0, 0));
	if (keycode == KEY_D)
		return (new_vec3(TRANSLATE, 0, 0));
	if (keycode == KEY_Q)
		return (new_vec3(0, 0, TRANSLATE));
	if (keycode == KEY_E)
		return (new_vec3(0, 0, -TRANSLATE));
	return (new_vec3(0, 0, 0));
}

static void	translate_setup(t_rt *rt, t_vec3 delta)
{
	t_obj	*obj;
	int		id;
	
	if (rt->sel.type == SEL_CAMERA)
		rt->camera.transform.translate = 
			add_vec(rt->camera.transform.translate, delta);
	else if (rt->sel.type == SEL_LIGHT)
	{
		id = get_light_index(rt->obj, rt->obj_count);	//light is always the last obj
		obj = &rt->obj[id];
		obj->sph.pos = add_vec(obj->sph.pos, delta);
		assign_bbox_translate(obj, delta);
	}
}

static void translate_obj(t_rt *rt, t_vec3 delta)
{
	t_obj	*obj;
	int		id;

	id = get_obj_index(rt->obj, rt->obj_count, rt->sel.obj_index);
	obj = &rt->obj[id];
	if (obj->type == PLANE)
	{
		obj->plane.pos = add_vec(obj->plane.pos, delta);
		obj->plane.d = scalar_product(obj->plane.normal,
			obj->plane.pos);
	}
	else if (obj->type == SPHERE)
		obj->sph.pos = add_vec(obj->sph.pos, delta);
	else if (obj->type == CYLINDER)
	{
		obj->cyl.pos = add_vec(obj->cyl.pos, delta);
		obj->cyl.d[0] = scalar_product(obj->cyl.axis,
			subtract_vec(obj->cyl.pos, obj->cyl.axis_height));
		obj->cyl.d[1] = scalar_product(obj->cyl.axis,
			add_vec(obj->cyl.pos, obj->cyl.axis_height));
	}
	assign_bbox_translate(obj, delta);
}

void	handle_translation(t_rt *rt, int keycode)
{
	t_vec3	delta;
	
	if (!translation_key(keycode))
		return;
	delta = translation_delta(keycode);
	if (rt->sel.type == SEL_CAMERA || rt->sel.type == SEL_LIGHT)
		translate_setup(rt, delta);
	else if (rt->sel.type == SEL_OBJ)
		translate_obj(rt, delta);
}

/*
void	handle_translation(t_rt *rt, int keycode)
{
	t_vec3	delta;
	t_obj	*obj;
	int		id;

	if (!translation_key(keycode))
		return;
	delta = translation_delta(keycode);
	if (rt->sel.type == SEL_CAMERA)
		rt->camera.transform.translate = add_vec(rt->camera.transform.translate, delta);
	else if (rt->sel.type == SEL_LIGHT)
	{
		id = get_light_index(rt->obj, rt->obj_count);	//light is always the last obj
		obj = &rt->obj[id];
		obj->sph.pos = add_vec(obj->sph.pos, delta);
		assign_bbox_translate(obj, delta);
	}
	else if (rt->sel.type == SEL_OBJ)
	{
		id = get_obj_index(rt->obj, rt->obj_count, rt->sel.obj_index);
		obj = &rt->obj[id];
		if (obj->type == PLANE)
		{
			obj->plane.pos = add_vec(obj->plane.pos, delta);
			obj->plane.d = scalar_product(obj->plane.normal, obj->plane.pos);
		}
		else if (obj->type == SPHERE)
			obj->sph.pos = add_vec(obj->sph.pos, delta);
		else if (obj->type == CYLINDER)
		{
			obj->cyl.pos = add_vec(obj->cyl.pos, delta);
			obj->cyl.d[0] = scalar_product(obj->cyl.axis, \
subtract_vec(obj->cyl.pos, obj->cyl.axis_height));
			obj->cyl.d[1] = scalar_product(obj->cyl.axis, \
add_vec(obj->cyl.pos, obj->cyl.axis_height));
		}
		assign_bbox_translate(obj, delta);
	}
}
*/
