/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 08:02:08 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/22 08:58:05 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_main_img(t_rt *rt)
{
	if (rt->img.img)
		mlx_destroy_image(rt->mlx, rt->img.img);
	if (rt->img_menu.img)
		mlx_destroy_image(rt->mlx, rt->img_menu.img);
	if (rt->img_load.img)
		mlx_destroy_image(rt->mlx, rt->img_load.img);
	if (rt->img_intro.img)
		mlx_destroy_image(rt->mlx, rt->img_intro.img);
}

void	free_label_img(t_rt *rt)
{
	int	i;

	if (rt->label.camera.img)
		mlx_destroy_image(rt->mlx, rt->label.camera.img);
	if (rt->label.light.img)
		mlx_destroy_image(rt->mlx, rt->label.light.img);
	if (rt->label.sphere.img)
		mlx_destroy_image(rt->mlx, rt->label.sphere.img);
	if (rt->label.plane.img)
		mlx_destroy_image(rt->mlx, rt->label.plane.img);
	if (rt->label.cylinder.img)
		mlx_destroy_image(rt->mlx, rt->label.cylinder.img);
	i = -1;
	while (++i < 10)
		mlx_destroy_image(rt->mlx, rt->label.digits[i].img);
}

void	free_info_img(t_rt *rt)
{
	if (rt->info.pos.img)
		mlx_destroy_image(rt->mlx, rt->info.pos.img);
	if (rt->info.rot.img)
		mlx_destroy_image(rt->mlx, rt->info.rot.img);
	if (rt->info.dot.img)
		mlx_destroy_image(rt->mlx, rt->info.dot.img);
	if (rt->info.comma.img)
		mlx_destroy_image(rt->mlx, rt->info.comma.img);
	if (rt->info.minus.img)
		mlx_destroy_image(rt->mlx, rt->info.minus.img);
}
