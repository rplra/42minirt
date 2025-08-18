/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_ux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:02:01 by hsim              #+#    #+#             */
/*   Updated: 2025/08/18 16:02:21 by rraja-az         ###   ########.fr       */
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

// 0 = fine, 1 = sketchy, 2 = grunge
void	handle_render_style(t_rt *rt, int keycode)
{
	if (!style_key(keycode))
		return ;
	if (keycode == KEY_1)
		rt->b_style = 0;
	else if (keycode == KEY_2)
		rt->b_style = 1;
	if (keycode == KEY_3)
		rt->b_style = 2;
}

void	handle_focus_dist(t_rt *rt, int keycode)
{
	if (!focus_dist_key(keycode))
		return ;
	if (keycode == KEY_C)
		rt->camera.focus_dist += FOCUS_DIST;
	else if (keycode == KEY_X)
		rt->camera.focus_dist -= FOCUS_DIST;
	if (rt->camera.focus_dist < 1)
		rt->camera.focus_dist = 1;
	printf(">> Focus distance: %f\n", rt->camera.focus_dist);
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

void	handle_animate(t_rt *rt, int keycode)
{
	if (keycode == KEY_4)
	{
		rt->b_animate = 1;
		rt->animate.pos = TRANSLATE;
		rt->animate.count = 0;
		rt->animate.step = 0.02;
		rt->animate.intensity = rt->ambient.intensity;
	}
	else if (keycode != KEY_4 && rt->b_animate == 1)
	{
		init_bg_color(rt, rt->ambient.intensity);
		rt->b_animate = 0;
	}
}
