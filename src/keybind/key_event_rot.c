/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event_rot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:47:23 by hsim              #+#    #+#             */
/*   Updated: 2025/07/31 22:30:29 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	apply_rotation_obj(int keycode, t_rt *rt)
// {
// 	float 	deg;
// 	t_uint	id;

// 	deg = 10;
// 	id = get_obj_index(rt->obj, rt->obj_count, 0);
// 	rt->obj[id].b_rotate = 1;
// 	if (keycode == KEY_K)
// 		rt->obj[id].rotate.y = fmod(rt->obj[id].rotate.y - deg, 360);
// 	// rt->obj[id].rotate.y = 0;
// 	else if (keycode == KEY_L)
// 		rt->obj[id].rotate.y = fmod(rt->obj[id].rotate.y + deg, 360);
// 	// rt->obj[id].rotate.y = 10;
// 	transform_bbox(rt, id);
// }

void	apply_rotation_obj(t_vec3 delta, t_rt *rt)
{
	t_uint	id;
	t_obj	*obj;

	id = get_obj_index(rt->obj, rt->obj_count, rt->sel.obj_index);
	obj = &rt->obj[id];
	obj->b_rotate = 1;
	obj->rotate = add_vec(obj->rotate, delta);

	if (fabs(obj->rotate.x) > 360 || fabs(obj->rotate.y) > 360 || fabs(obj->rotate.z) > 360)
		obj->rotate = new_vec3(fmod(obj->rotate.x, 360), fmod(obj->rotate.y, 360), fmod(obj->rotate.z, 360));
	transform_bbox(rt, id);
}

void	apply_rotation_cam(int keycode, t_rt *rt)
{
	float	deg;

	deg = 1;
	if (keycode == KEY_UP)
		rt->camera.transform.rotate.x -= deg;
	else if (keycode == KEY_DOWN)
		rt->camera.transform.rotate.x += deg;
	else if (keycode == KEY_LEFT)
		rt->camera.transform.rotate.y -= deg;
	else if (keycode == KEY_RIGHT)
		rt->camera.transform.rotate.y += deg;
	else if (keycode == KEY_ARROW_L)
		rt->camera.transform.rotate.z -= (deg + 20);
	else if (keycode == KEY_ARROW_R)
		rt->camera.transform.rotate.z += (deg + 20);
	// /*debug*/debug_print_vec("cam_rot", rt->camera.transform.rotate);
}

t_vec3	rotation_delta(int keycode)
{
	if (keycode == KEY_UP)
		return (new_vec3(-ROTATE, 0, 0));
	else if (keycode == KEY_DOWN)
		return (new_vec3(ROTATE, 0, 0));
	else if (keycode == KEY_LEFT)
		return (new_vec3(0, -ROTATE, 0));
	else if (keycode == KEY_RIGHT)
		return (new_vec3(0, ROTATE, 0));
	else if (keycode == KEY_ARROW_L)
		return (new_vec3(0, 0, -ROTATE - 20));
	else if (keycode == KEY_ARROW_R)
		return (new_vec3(0, 0, ROTATE + 20));
	return (new_vec3(0, 0, 0));
}

void	reset_rotation_cam(t_rt *rt)
{
	rt->camera.transform.rotate = new_vec3(0, 0, 0);
	rt->camera.pos = new_vec3(rt->camera.ori.x, rt->camera.ori.y, rt->camera.ori.z);
}

void	handle_rotation(t_rt *rt, int keycode)
{
	// if (rotation_key_cam(keycode))
	// apply_rotation_cam(keycode, rt);
	// if (rotation_key_obj(keycode))
	// apply_rotation_obj(keycode, rt);
	// if (keycode == KEY_R)
	// reset_rotation_cam(rt);
	
	/* ******************************************************************* */
	t_vec3	delta;
	
	if (!rotation_key_cam(keycode))
		return ;
	if (keycode == KEY_R)
		reset_rotation_cam(rt);
	delta = rotation_delta(keycode);
	if (rt->sel.type == SEL_CAMERA)
		rt->camera.transform.rotate = add_vec(rt->camera.transform.rotate, delta);
	else if (rt->sel.type == SEL_OBJ)
		apply_rotation_obj(delta, rt);
}