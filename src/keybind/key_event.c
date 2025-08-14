/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:25:47 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/14 16:55:55 by rraja-az         ###   ########.fr       */
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
