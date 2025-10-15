/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:19:22 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/16 23:44:04 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * initializes image pointer for menu
 * @param size image dimensions (width & height)
 */
void	load_menu(t_rt *rt, t_img *img, char *filepath, int size[2])
{
	img->img = mlx_xpm_file_to_image(rt->mlx, filepath, &size[W], &size[H]);
	if (!img->img)
		ft_perror("🚨 Error in creating menu image!", 0, 0);
	img->addr = mlx_get_data_addr(img->img, \
&img->bpp, \
&img->line_len, \
&img->endian);
}

void	load_menu_label_info(t_rt *rt)
{
	int	dimension[2];

	assign_int(dimension, LABEL_W, LABEL_H);
	load_menu(rt, &rt->label.camera, LABEL_C, dimension);
	load_menu(rt, &rt->label.light, LABEL_L, dimension);
	load_menu(rt, &rt->label.plane, LABEL_PL, dimension);
	load_menu(rt, &rt->label.sphere, LABEL_SP, dimension);
	load_menu(rt, &rt->label.cylinder, LABEL_CY, dimension);
	load_menu(rt, &rt->label.digits[0], DIGIT_0, dimension);
	load_menu(rt, &rt->label.digits[1], DIGIT_1, dimension);
	load_menu(rt, &rt->label.digits[2], DIGIT_2, dimension);
	load_menu(rt, &rt->label.digits[3], DIGIT_3, dimension);
	load_menu(rt, &rt->label.digits[4], DIGIT_4, dimension);
	load_menu(rt, &rt->label.digits[5], DIGIT_5, dimension);
	load_menu(rt, &rt->label.digits[6], DIGIT_6, dimension);
	load_menu(rt, &rt->label.digits[7], DIGIT_7, dimension);
	load_menu(rt, &rt->label.digits[8], DIGIT_8, dimension);
	load_menu(rt, &rt->label.digits[9], DIGIT_9, dimension);
	load_menu(rt, &rt->info.pos, INFO_POS, dimension);
	load_menu(rt, &rt->info.rot, INFO_ROT, dimension);
	load_menu(rt, &rt->info.dot, INFO_DOT, dimension);
	load_menu(rt, &rt->info.comma, INFO_COMMA, dimension);
	load_menu(rt, &rt->info.minus, INFO_MINUS, dimension);
}
