/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils_draw1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:15:49 by hsim              #+#    #+#             */
/*   Updated: 2025/06/24 22:15:02 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * Template function from mlx documentation
 * Places pixels on image
 *
 * Reference:
 * https://harm-smits.github.io/42docs/libs/minilibx/
 * getting_started.html#writing-pixels-to-a-image/
 */
void	my_mlx_pixel_put(t_rt vars, int x, int y, int color)
{
	int		offset;
	char	*dst;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	offset = ((y * vars.img.line_len) + (x * (vars.img.bpp / 8)));
	dst = vars.img.addr + offset;
	*(unsigned int *)dst = color;
}

/* Renders the image black color*/
void	clear_image(t_rt vars, int win_width, int win_height, int color)
{
	int	tmp;

	while (win_height >= 0)
	{
		tmp = win_width;
		while (tmp >= 0)
			my_mlx_pixel_put(vars, tmp--, win_height, color);
		win_height--;
	}
}

/* Create image container to start draw */
void	my_create_image(t_rt *vars, t_img *img)
{
	img->img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img->img)
		ft_perror("🚨 Error in creating main image!", 0, 0);
	img->addr = mlx_get_data_addr(img->img, \
&img->bpp, \
&img->line_len, \
&img->endian);
}
