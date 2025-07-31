/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:07:08 by hsim              #+#    #+#             */
/*   Updated: 2025/07/25 20:24:58 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*dont use mlx_destroy_window, have fsan error*/
int	close_window(int keycode, t_rt *vars)
{
	(void) vars;
	if (keycode == KEY_ESC)
	{
		free_render(vars, 1);
		exit (0);
	}
	return (0);
}

/* only for linux system, can remove this for mac system */
int	close_window_x(int keycode, t_rt *vars)
{
	(void) keycode;
	(void) vars;
	// free_malloc(vars, 1);
	exit (0);
	// return (0);
}
