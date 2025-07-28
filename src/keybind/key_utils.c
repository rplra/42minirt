/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:52:32 by hsim              #+#    #+#             */
/*   Updated: 2025/07/28 10:00:41 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keybind.h"

bool	rotation_key(int keycode)
{
	return (keycode == KEY_UP || keycode == KEY_DOWN ||
			keycode == KEY_LEFT || keycode == KEY_RIGHT ||
			keycode == KEY_ARROW_L || keycode == KEY_ARROW_R);
}

/* prints out current keycode number */
int	key_press(int keycode, void *param)
{
	(void)param;
	printf("🟡 keycode is %i\n", keycode);

	// add on other keypress here
	if (rotation_key(keycode))
		apply_rotation(keycode, (t_rt *)param);

	//if valid keypress, render image
	if (rotation_key(keycode))
		my_render_image((t_rt *)param);
	return (0);
}
