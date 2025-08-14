/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:15:49 by hsim              #+#    #+#             */
/*   Updated: 2025/08/12 17:51:27 by rraja-az         ###   ########.fr       */
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
void	my_mlx_pixel_put(t_rt rt, int x, int y, int color)
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
			my_mlx_pixel_put(rt, tmp--, win_height, color);
		win_height--;
	}
}

/* Create image container to start draw */
void	my_create_img(t_rt *rt, t_img *img)
{
	img->img = mlx_new_image(rt->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img->img)
		ft_perror("Create img: 🚨 Error in creating main image!", 0, 0);
	img->addr = mlx_get_data_addr(img->img, \
&img->bpp, \
&img->line_len, \
&img->endian);
}

/*
 * initializes image pointer for menu
 * @param size image dimensions (width & height)
 */
void	my_create_menu(t_rt *rt, t_img *img, char *filepath, int size[2])
{
	img->img = mlx_xpm_file_to_image(rt->mlx, filepath, &size[W], &size[H]);
	if (!img->img)
		ft_perror("Create menu: 🚨 Error in creating main image!", 0, 0);
	img->addr = mlx_get_data_addr(img->img, \
&img->bpp, \
&img->line_len, \
&img->endian);
}

/* void load_label(t_rt *rt)
{
    int size[2];

    my_create_menu(rt, &rt->label.camera, LABEL_C, size);
    my_create_menu(rt, &rt->label.light, LABEL_L, size);
	my_create_menu(rt, &rt->label.plane, LABEL_PL, size);
    my_create_menu(rt, &rt->label.sphere, LABEL_SP, size);
    my_create_menu(rt, &rt->label.cylinder, LABEL_CY, size);
}

void load_info(t_rt *rt)
{
    int size[2];

    my_create_menu(rt, &rt->info.pos, INFO_POS, size);
    my_create_menu(rt, &rt->info.rot, INFO_ROT, size);
	my_create_menu(rt, &rt->info.dot, INFO_DOT, size);
    my_create_menu(rt, &rt->info.comma, INFO_COMMA, size);
    my_create_menu(rt, &rt->info.minus, INFO_MINUS, size);
} */
