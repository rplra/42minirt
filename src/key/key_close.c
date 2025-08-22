/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:07:08 by hsim              #+#    #+#             */
/*   Updated: 2025/08/22 10:11:47 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_window(int keycode, t_rt *rt)
{
	(void)rt;
	if (keycode == KEY_ESC)
		cleanup_and_exit(rt, 0);
	return (0);
}


int	close_window_x(t_rt *rt)
{
	cleanup_and_exit(rt, 0);
	return (0);
}
