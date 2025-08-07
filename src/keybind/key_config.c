/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:52 by hsim              #+#    #+#             */
/*   Updated: 2025/08/07 21:48:08 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keybind.h"

/* all keypress button that allow img render to happen */
bool	control_key(int keycode)
{
	return (keycode == KEY_R || keycode == KEY_UP || keycode == KEY_DOWN
|| keycode == KEY_SPACE);
}

bool	focus_dist_key(int keycode)
{
	return (keycode == KEY_C || keycode == KEY_X);
}

/* controls for render style */
bool	style_key(int keycode)
{
	return (keycode == KEY_1 || keycode == KEY_2 || keycode == KEY_3);
}

bool	rotation_key(int keycode)
{
	return (keycode == KEY_I || keycode == KEY_J ||
keycode == KEY_K || keycode == KEY_L ||
keycode == KEY_U || keycode == KEY_O);
}