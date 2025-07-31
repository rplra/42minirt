/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:52:32 by hsim              #+#    #+#             */
/*   Updated: 2025/07/31 13:26:46 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keybind.h"
#include "render.h"

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

bool	valid_keypress(int keycode)
{
	return (rotation_key_cam(keycode) || rotation_key_obj(keycode) ||
control_key(keycode) || translation_key(keycode));
}

/* prints out current keycode number */
int	key_press(int keycode, t_rt *rt)
{
	printf("🟡 keycode is %i\n", keycode);

	// close_window(keycode, rt);
	handle_render_mode(rt, keycode);
	handle_selection(rt, keycode);
	handle_translation(rt, keycode);
	handle_scale(rt, keycode);
	handle_rotation(rt, keycode);

	//if valid keypress, render image
	// if (rotation_key_cam(keycode) || rotation_key_obj(keycode) || \
// control_key(keycode) || translation_key(keycode))
	if (valid_keypress(keycode))
	{
		// init_cam(rt);
		// init_hit(rt);

		update_cam_pos(rt);
		init_bvh_node(rt);
		my_render_image(rt);
	}
	return (0);
}
