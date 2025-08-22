/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_selection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 20:23:59 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/22 08:12:35 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// (rt->sel.obj_index < (int)rt->obj_count - 2) //-1 for light
void	handle_selection(t_rt *rt, int keycode)
{
	if (keycode == KEY_TAB)
	{
		if (rt->sel.type == SEL_CAMERA)
			rt->sel.type = SEL_LIGHT;
		else if (rt->sel.type == SEL_LIGHT)
		{
			if (rt->obj_count > 0)
			{
				rt->sel.type = SEL_OBJ;
				rt->sel.obj_index = 0;
			}
			else
				rt->sel.type = SEL_CAMERA;
		}
		else if (rt->sel.type == SEL_OBJ)
		{
			if (rt->sel.obj_index < (int)rt->obj_count - 2)
				rt->sel.obj_index++;
			else
				rt->sel.type = SEL_CAMERA;
		}
		else
			rt->sel.type = SEL_CAMERA;
		render(rt);
	}
}

static void	setup_selection(t_rt *rt, int x, int *y, int line_ht)
{
	(void)x;
	*y += line_ht;
	if (rt->sel.type == SEL_CAMERA)
	{
		mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->label.camera.img,
			WIN_WIDTH + (PANEL_WIDTH / LX), *y - LY);
	}
	else if (rt->sel.type == SEL_LIGHT)
	{
		mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->label.light.img,
			WIN_WIDTH + (PANEL_WIDTH / LX), *y - LY);
	}
}

static void	display_obj_label(t_rt *rt, t_obj *obj, int y)
{
	if (obj->type == SPHERE)
	{
		mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->label.sphere.img,
			WIN_WIDTH + (PANEL_WIDTH / LX), y - LY);
	}
	else if (obj->type == PLANE)
	{
		mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->label.plane.img,
			WIN_WIDTH + (PANEL_WIDTH / LX), y - LY);
	}
	else if (obj->type == CYLINDER)
	{
		mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->label.cylinder.img,
			WIN_WIDTH + (PANEL_WIDTH / LX), y - LY);
	}
}

static void	obj_selection(t_rt *rt, int x, int *y)
{
	t_obj	*obj;
	int		id;
	int		digit;

	(void)x;
	if (rt->sel.type != SEL_OBJ || rt->sel.obj_index < 0
		|| (size_t)rt->sel.obj_index >= rt->obj_count)
		return ;
	id = get_obj_index(rt->obj, rt->obj_count, rt->sel.obj_index);
	obj = &rt->obj[id];
	display_obj_label(rt, obj, *y);
	digit = rt->sel.obj_index % 10;
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->label.digits[digit].img, x
		+ LD, *y - LY + DY);
}

void	selection_guide(t_rt *rt)
{
	int	x;
	int	y;
	int	line_ht;

	x = WIN_WIDTH + (PANEL_WIDTH * 0.44);
	y = WIN_HEIGHT * 0.9;
	line_ht = (double)3.8;
	setup_selection(rt, x, &y, line_ht);
	obj_selection(rt, x, &y);
	get_info(rt, WIN_WIDTH * IX, &y, line_ht);
}
