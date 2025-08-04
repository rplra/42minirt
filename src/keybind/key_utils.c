/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:52:32 by hsim              #+#    #+#             */
/*   Updated: 2025/08/04 18:55:14 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "keybind.h"
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

bool	valid_keypress(int keycode)
{
	return (rotation_key(keycode) || scale_factor(keycode) ||
control_key(keycode) || translation_key(keycode));
}

void	update_bbox(t_rt *rt)
{
	int		id;
	t_obj	*obj;

	id = get_obj_index(rt->obj, rt->obj_count, rt->sel.obj_index);
	obj = &rt->obj[id];
	copy_bbox(obj->bbox_ori, obj->bbox);
	obj->bbox_center = get_bbox_center(obj->bbox);
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
	handle_show_light(rt, keycode);

	if (valid_keypress(keycode))
	{
		// init_cam(rt);
		// init_hit(rt);
		update_cam_pos(rt);
		if (keycode == KEY_UP || keycode == KEY_DOWN)
			set_render_quality(rt);
		if (scale_key(keycode) || translation_key(keycode))
			update_bbox(rt);
		free_bvh(rt->bvh);
		init_bvh_node(rt);
		my_render_image(rt);
	}
	return (0);
}
