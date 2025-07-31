/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:52:32 by hsim              #+#    #+#             */
/*   Updated: 2025/07/31 10:12:59 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keybind.h"

bool	rotation_key_cam(int keycode)
{
	return (keycode == KEY_UP || keycode == KEY_DOWN ||
keycode == KEY_LEFT || keycode == KEY_RIGHT ||
keycode == KEY_ARROW_L || keycode == KEY_ARROW_R);
}

bool	rotation_key_obj(int keycode)
{
	return (keycode == KEY_O || keycode == KEY_P);
}

/* all keypress button that allow img render to happen */
bool	control_key(int keycode)
{
	return (keycode == KEY_R);
}

/* prints out current keycode number */
int	key_press(int keycode, void *param)
{
	t_rt	*rt;

	rt = (t_rt *)param;
	printf("🟡 keycode is %i\n", keycode);

	// add on other keypress here
	if (rotation_key_cam(keycode))
		apply_rotation_cam(keycode, rt);
	if (rotation_key_obj(keycode))
		apply_rotation_obj(keycode, rt);
	if (keycode == KEY_R)
		reset_rotation_cam((t_rt *)param);

	//if valid keypress, render image
	if (rotation_key_cam(keycode) || rotation_key_obj(keycode) || \
control_key(keycode))
	{
		init_bvh_node(rt);
		/*debug*/debug_print_arr("rot_bvh", rt->obj, rt->obj_count);
		my_render_image(rt);
	}
	return (0);
}
