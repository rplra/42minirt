/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:32:08 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/31 12:48:45 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_panel(t_rt *rt)
{
	int	x;
	int	y;

	x = WIN_WIDTH;
	while (x < (WIN_WIDTH + PANEL_WIDTH))
	{
		y = -1;
		while (++y < WIN_HEIGHT)
			mlx_pixel_put(rt->mlx, rt->mlx_win, x, y, 0x000000);
		x++;
	}
}

void	keybind_guide(t_rt *rt)
{
	int	x;
	int	y;

	x = WIN_WIDTH + 10;
	y = 0;
	mlx_string_put(rt->mlx, rt->mlx_win, x, y += 20, WHITE, "CONTROLS");
	mlx_string_put(rt->mlx, rt->mlx_win, x, y += 35, WHITE, "MODE");
	mlx_string_put(rt->mlx, rt->mlx_win, x + 20, y += 15, WHITE, "R: Render");
	mlx_string_put(rt->mlx, rt->mlx_win, x + 20, y += 12, WHITE, "P: Preview");
	mlx_string_put(rt->mlx, rt->mlx_win, x, y += 25, WHITE, "MOVE");
	mlx_string_put(rt->mlx, rt->mlx_win, x + 20, y += 15, WHITE, "W/S: Up/Down");
	mlx_string_put(rt->mlx, rt->mlx_win, x + 20, y += 12, WHITE, "A/D: Left/Right");
	mlx_string_put(rt->mlx, rt->mlx_win, x + 20, y += 12, WHITE, "Q/E: Front/Back");
	mlx_string_put(rt->mlx, rt->mlx_win, x, y += 25, WHITE, "SCALE");
	mlx_string_put(rt->mlx, rt->mlx_win, x + 20, y += 15, WHITE, "+: Big");
	mlx_string_put(rt->mlx, rt->mlx_win, x + 20, y += 12, WHITE, "-: Small");
	mlx_string_put(rt->mlx, rt->mlx_win, x, y += 25, WHITE, "ROTATE");
	mlx_string_put(rt->mlx, rt->mlx_win, x + 20, y += 15, WHITE, "X: Horizontal");
	mlx_string_put(rt->mlx, rt->mlx_win, x + 20, y += 12, WHITE, "Y: Vertical");
	mlx_string_put(rt->mlx, rt->mlx_win, x + 20, y += 12, WHITE, "Z: Depth");
}
