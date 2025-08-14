/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:52 by hsim              #+#    #+#             */
/*   Updated: 2025/08/14 16:50:45 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keybind.h"

/* all keypress button that allow img render to happen */
bool	control_key(int keycode)
{
	return (keycode == KEY_R || keycode == KEY_UP
		|| keycode == KEY_DOWN || keycode == KEY_SPACE);
}

bool	focus_dist_key(int keycode)
{
	return (keycode == KEY_C || keycode == KEY_X);
}

/* controls for render style */
bool	style_key(int keycode)
{
	return (keycode == KEY_1 || keycode == KEY_2
		|| keycode == KEY_3 || keycode == KEY_4);
}

bool	rotation_key(int keycode)
{
	return (keycode == KEY_I || keycode == KEY_J
		|| keycode == KEY_K || keycode == KEY_L
		|| keycode == KEY_U || keycode == KEY_O);
}
