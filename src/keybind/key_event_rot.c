/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event_rot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:47:23 by hsim              #+#    #+#             */
/*   Updated: 2025/07/31 12:53:02 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	apply_rotation_obj(int keycode, t_rt *rt)
{
	float 	deg;
	t_uint	id;

	deg = 10;
	id = get_obj_index(rt->obj, rt->obj_count, 1);
	rt->obj[id].b_rotate = 1;
	if (keycode == KEY_K)
		rt->obj[id].rotate.y = fmod(rt->obj[id].rotate.y - deg, 360);
	// rt->obj[id].rotate.y = 0;
	else if (keycode == KEY_L)
		rt->obj[id].rotate.y = fmod(rt->obj[id].rotate.y + deg, 360);
	// rt->obj[id].rotate.y = 10;
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

void	reset_rotation_cam(t_rt *rt)
{
	rt->camera.transform.rotate = new_vec3(0, 0, 0);
	rt->camera.pos = new_vec3(rt->camera.ori.x, rt->camera.ori.y, rt->camera.ori.z);
}

void	handle_rotation(t_rt *rt, int keycode)
{
	if (rotation_key_cam(keycode))
		apply_rotation_cam(keycode, rt);
	if (rotation_key_obj(keycode))
		apply_rotation_obj(keycode, rt);
	if (keycode == KEY_R)
		reset_rotation_cam(rt);
}