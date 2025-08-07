/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:52:32 by hsim              #+#    #+#             */
/*   Updated: 2025/08/07 20:56:39 by hsim             ###   ########.fr       */
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

bool	valid_keypress(int keycode)
{
	return (rotation_key(keycode) || scale_key(keycode) ||
control_key(keycode) || translation_key(keycode) ||
focus_dist_key(keycode) || style_key(keycode));
}

void	update_bbox(t_rt *rt, int keycode)
{
	int		id;
	t_obj	*obj;

	if (!scale_key(keycode) && !translation_key(keycode))
		return ;
	id = get_obj_index(rt->obj, rt->obj_count, rt->sel.obj_index);
	obj = &rt->obj[id];
	copy_bbox(obj->bbox_ori, obj->bbox);	//update bbox_ori to translated bbox
	// copy_bbox(obj->bbox, obj->bbox_ori);	//update bbox_ori to translated bbox
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
	handle_focus_dist(rt, keycode);
	handle_render_style(rt, keycode);

	if (valid_keypress(keycode))
	{
		update_cam_pos(rt);
		if (keycode == KEY_UP || keycode == KEY_DOWN)
		{
			mlx_put_image_to_window(rt->mlx, rt->mlx_win,
rt->img_load.img, (WIN_WIDTH / 2) - (LOADBAR_W / 2), WIN_HEIGHT * 0.05);
			set_render_quality(rt);
		}
		// update_bbox(rt, keycode);
		free_bvh(rt->bvh);
		init_bvh_node(rt);
		my_render_img(rt);
	}
	return (0);
}
