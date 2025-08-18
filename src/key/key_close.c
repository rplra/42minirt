/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:07:08 by hsim              #+#    #+#             */
/*   Updated: 2025/08/19 02:45:59 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*dont use mlx_destroy_window, have fsan error*/
int	close_window(int keycode, t_rt *rt)
{
	(void)rt;
	if (keycode == KEY_ESC)
		cleanup_and_exit(rt, 0);
	return (0);
}

/* only for linux system, can remove this for mac system */
// int	close_window_x(int keycode, t_rt *vars)
int	close_window_x(t_rt *rt)
{
	// (void)keycode;
	// (void)vars;
	// free_malloc(vars, 1);
	cleanup_and_exit(rt, 0);
	// exit(0);
	return (0);
}
