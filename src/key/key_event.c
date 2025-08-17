/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:25:47 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/17 12:18:47 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_render_mode(t_rt *rt, int keycode)
{
	if (keycode == KEY_DOWN)
		rt->b_preview_mode = 1;
	if (keycode == KEY_UP)
		rt->b_preview_mode = 0;
}

void	handle_show_light(t_rt *rt, int keycode)
{
	if (keycode != KEY_SPACE)
		return ;
	if (rt->sel.type == SEL_LIGHT)
	{
		if (!rt->b_show_light && keycode == KEY_SPACE)
			rt->b_show_light = 1;
		else if (rt->b_show_light && keycode == KEY_SPACE)
			rt->b_show_light = 0;
	}
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