/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:33:48 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/27 23:03:39 by rraja-az         ###   ########.fr       */
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

// to update
bool	rotation_key(int keycode)
{
	return (keycode == KEY_UP || keycode == KEY_DOWN ||
			keycode == KEY_LEFT || keycode == KEY_RIGHT);
}

// rotation