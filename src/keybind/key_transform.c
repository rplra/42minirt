/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:33:48 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/31 12:53:13 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	translation_key(int keycode)
{
	return (keycode == KEY_W || keycode == KEY_S ||
			keycode == KEY_A || keycode == KEY_D ||
			keycode == KEY_Q || keycode == KEY_E);
}

t_vec3	translation_delta(int keycode)
{
	if (keycode == KEY_W)
		return (new_vec3(0, TRANSLATE, 0));
	if (keycode == KEY_S)
		return (new_vec3(0, -TRANSLATE, 0));
	if (keycode == KEY_A)
		return (new_vec3(-TRANSLATE, 0, 0));
	if (keycode == KEY_D)
		return (new_vec3(TRANSLATE, 0, 0));
	if (keycode == KEY_Q)
		return (new_vec3(0, 0, TRANSLATE));
	if (keycode == KEY_E)
		return (new_vec3(0, 0, -TRANSLATE));
	return (new_vec3(0, 0, 0));
}

bool	scale_key(int keycode)
{
	return (keycode == KEY_PLUS || keycode == KEY_MINUS);
}

float	scale_factor(int keycode)
{
	if (keycode == KEY_PLUS)
		return (SCALE_UP);
	if (keycode == KEY_MINUS)
		return (SCALE_DOWN);
	return (1.0f);
}

bool	rotation_key_cam(int keycode)
{
	return (keycode == KEY_UP || keycode == KEY_DOWN ||
keycode == KEY_LEFT || keycode == KEY_RIGHT ||
keycode == KEY_ARROW_L || keycode == KEY_ARROW_R);
}

bool	rotation_key_obj(int keycode)
{
	return (keycode == KEY_K || keycode == KEY_L);
}

/* all keypress button that allow img render to happen */
bool	control_key(int keycode)
{
	return (keycode == KEY_R);
}
