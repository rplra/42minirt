/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event_style.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:02:01 by hsim              #+#    #+#             */
/*   Updated: 2025/08/07 21:47:40 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_render_style(t_rt *rt, int keycode)
{
	if (!style_key(keycode))
		return ;
	if (keycode == KEY_1)
		rt->b_style = 0;	//fine style
	else if (keycode == KEY_2)
		rt->b_style = 1;	//sketchy style
	if (keycode == KEY_3)
		rt->b_style = 2;	//grunge style
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
