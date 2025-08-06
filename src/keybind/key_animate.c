/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_animate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:17:00 by hsim              #+#    #+#             */
/*   Updated: 2025/08/06 13:35:22 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	init_loading_img(t_rt *rt)
// {
// 	rt->loading.i = 0;
// 	rt->loading.path = (char **)malloc(sizeof(char *) * 9);
//     rt->loading.path[0] = ft_strdup("asset/load-600/1.xpm");
//     rt->loading.path[1] = ft_strdup("asset/load-600/2.xpm");
//     rt->loading.path[2] = ft_strdup("asset/load-600/3.xpm");
//     rt->loading.path[3] = ft_strdup("asset/load-600/4.xpm");
//     rt->loading.path[4] = ft_strdup("asset/load-600/5.xpm");
//     rt->loading.path[5] = ft_strdup("asset/load-600/6.xpm");
//     rt->loading.path[6] = ft_strdup("asset/load-600/7.xpm");
//     rt->loading.path[7] = ft_strdup("asset/load-600/8.xpm");
//     rt->loading.path[8] = ft_strdup("asset/load-600/9.xpm");
// 	assign_int(rt->loading.size, 135, 49);
// }

// int	animate_loading(t_rt *rt)
// {
// 	int	i;

// 	if (rt->b_loading != 1)
// 		return (0);
// 	i = rt->loading.i;
// 	my_create_menu(rt, &rt->img_load, rt->loading.path[i], rt->loading.size);
// 	mlx_put_image_to_window(rt->mlx, rt->mlx_win, \
// rt->img_load.img, (WIN_WIDTH / 2) - (rt->loading.size[W] / 2), 
// WIN_HEIGHT / 2);

// 	rt->loading.i += 1;
// 	if (rt->loading.i > 8)
// 		rt->loading.i = 0;
// 	return (0);
// }
