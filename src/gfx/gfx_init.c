/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 07:54:21 by hsim              #+#    #+#             */
/*   Updated: 2025/08/16 23:37:47 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * initialize mlx windows for image rendering
 * mlx_init uses malloc
 */
void	init_mlx(t_rt *rt)
{
	rt->mlx = mlx_init();
	if (rt->mlx == NULL)
	{
		free(rt->mlx);
		exit(1);
	}
	rt->mlx_win = mlx_new_window(rt->mlx, WIN_WIDTH + PANEL_WIDTH, WIN_HEIGHT,
			"miniRT");
}

