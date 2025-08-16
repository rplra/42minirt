/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:52:32 by hsim              #+#    #+#             */
/*   Updated: 2025/08/16 23:31:48 by rraja-az         ###   ########.fr       */
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
	return (rotation_key(keycode) || scale_key(keycode)
		|| control_key(keycode) || translation_key(keycode)
		|| focus_dist_key(keycode) || style_key(keycode));
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
	handle_animate(rt, keycode);
	if (valid_keypress(keycode))
	{
		update_cam_pos(rt, keycode);
		if (keycode == KEY_UP || keycode == KEY_DOWN)
		{
			mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img_load.img,
				(WIN_WIDTH / 2) - (LOADBAR_W / 2), WIN_HEIGHT * 0.05);
			set_render_quality(rt);
		}
		free_bvh(rt->bvh);
		init_bvh_node(rt);
		render(rt);
	}
	/*debug*/ printf("Selected OBJ index = %d\n", rt->sel.obj_index);
	/*debug*/ print_selected(rt);
	return (0);
}
