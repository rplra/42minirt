/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_rotation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:47:23 by hsim              #+#    #+#             */
/*   Updated: 2025/07/28 10:00:45 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keybind.h"

void	apply_rotation(int keycode, t_rt *rt)
{
	float	deg;

	deg = 1;
	if (keycode == KEY_UP)
		rt->camera.transform.rotate.x -= deg;
	else if (keycode == KEY_DOWN)
		rt->camera.transform.rotate.x += deg;
	else if (keycode == KEY_LEFT)
		rt->camera.transform.rotate.y -= deg;
	else if (keycode == KEY_RIGHT)
		rt->camera.transform.rotate.y += deg;
	else if (keycode == KEY_ARROW_L)
		rt->camera.transform.rotate.z -= (deg + 5);
	else if (keycode == KEY_ARROW_R)
		rt->camera.transform.rotate.z += (deg + 5);
}