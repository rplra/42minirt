/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:15:49 by hsim              #+#    #+#             */
/*   Updated: 2025/08/18 15:52:57 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * Template function from mlx documentation
 * brief: places a col dot (pixel) on image at the right spot (mem offset)
 *
 * Reference:
 * https://harm-smits.github.io/42docs/libs/minilibx/
 * getting_started.html#writing-pixels-to-a-image/
 */
void	ft_mlx_pixel_put(t_rt rt, int x, int y, int color)
{
	int		offset;
	char	*dst;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	offset = ((y * rt.img.line_len) + (x * (rt.img.bpp / 8)));
	dst = rt.img.addr + offset;
	*(unsigned int *)dst = color;
}

/* Renders the image in black color */
void	clear_image(t_rt rt, int win_width, int win_height, int color)
{
	int	tmp;

	while (win_height >= 0)
	{
		tmp = win_width;
		while (tmp >= 0)
			ft_mlx_pixel_put(rt, tmp--, win_height, color);
		win_height--;
	}
}

/* Create image container to start draw */
void	ft_create_img(t_rt *rt, t_img *img)
{
	img->img = mlx_new_image(rt->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img->img)
		ft_perror("🚨 Error in creating image!", 0, 0);
	img->addr = mlx_get_data_addr(img->img, \
&img->bpp, \
&img->line_len, \
&img->endian);
}
