/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:25:47 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/19 02:12:27 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	valid_keypress(int keycode)
{
	return (rotation_key(keycode) || scale_key(keycode)
		|| control_key(keycode) || translation_key(keycode)
		|| focus_dist_key(keycode) || style_key(keycode));
}

static void	handle_event(t_rt *rt, int keycode)
{
	handle_render_mode(rt, keycode);
	handle_selection(rt, keycode);
	handle_translation(rt, keycode);
	handle_scale(rt, keycode);
	handle_rotation(rt, keycode);
	handle_show_light(rt, keycode);
	handle_focus_dist(rt, keycode);
	handle_render_style(rt, keycode);
	handle_animate(rt, keycode);
}

/* prints out current keycode number */
int	key_press(int keycode, t_rt *rt)
{
	printf("🟡 keycode is %i\n", keycode);
	// close_window(keycode, rt);
	handle_event(rt, keycode);
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
	printf("Selected OBJ index = %d\n", rt->sel.obj_index);
	print_selected(rt);
	return (0);
}

void	event_loop(t_rt *rt)
{
	printf(LBLUE ">> use tabs to select cam/light/obj,"
		" then → translate/rotate/scale keys to transform\n" RESET);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img_intro.img,
		(WIN_WIDTH / 2) - (INTRO_W / 2), WIN_HEIGHT / 2);
	mlx_hook(rt->mlx_win, ON_KEYDOWN, 1L << 0, key_press, rt);
	mlx_hook(rt->mlx_win, 17, 0, close_window_x, rt);
	mlx_key_hook(rt->mlx_win, close_window, rt);
	mlx_loop_hook(rt->mlx, animate_light, rt);
	mlx_loop(rt->mlx);
}
