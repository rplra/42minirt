/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:02:28 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/14 16:56:25 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	display_camera_info(t_rt *rt, int x, int *y, int line_ht)
{
	char	*pos_str;
	char	*rot_str;

	*y += line_ht + IY_OFFSET;
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->info.pos.img, x, *y);
	pos_str = get_info_str(rt->camera.pos);
	display_digit_xpm(rt, pos_str, x * IDX, *y);
	free(pos_str);
	*y += line_ht + IY;
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->info.rot.img, x, *y);
	rot_str = get_info_str(rt->camera.transform.rotate);
	display_digit_xpm(rt, rot_str, x * IDX, *y);
	free(rot_str);
}

static void	display_light_info(t_rt *rt, int x, int *y, int line_ht)
{
	char	*pos_str;
	t_vec3	transformed_light_pos;
	int		light_index;

	light_index = get_light_index(rt->obj, rt->obj_count);
	if (light_index >= 0)
		transformed_light_pos = rt->obj[light_index].sph.pos;
	else
		transformed_light_pos = rt->light.pos;
	*y += line_ht + IY_OFFSET;
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->info.pos.img, x, *y);
	pos_str = get_info_str(transformed_light_pos);
	display_digit_xpm(rt, pos_str, x * IDX, *y);
	free(pos_str);
}

static void	get_obj_info(t_rt *rt, t_vec3 *pos, t_vec3 *rot)
{
	t_obj	*obj;
	int		id;

	if (rt->sel.obj_index < 0 || (size_t)rt->sel.obj_index >= rt->obj_count)
		return ;
	id = get_obj_index(rt->obj, rt->obj_count, rt->sel.obj_index);
	obj = &rt->obj[id];
	if (obj->type == SPHERE)
	{
		*pos = obj->sph.pos;
		*rot = (t_vec3){0, 0, 0};
	}
	else if (obj->type == PLANE)
	{
		*pos = obj->plane.pos;
		*rot = obj->rotate;
	}
	else if (obj->type == CYLINDER)
	{
		*pos = obj->cyl.pos;
		*rot = obj->rotate;
	}
}

static void	display_obj_info(t_rt *rt, int x, int *y, int line_ht)
{
	char	*pos_str;
	char	*rot_str;
	t_vec3	pos;
	t_vec3	rot;
	t_obj	*obj;

	get_obj_info(rt, &pos, &rot);
	*y += line_ht + IY_OFFSET;
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->info.pos.img, x, *y);
	pos_str = get_info_str(pos);
	display_digit_xpm(rt, pos_str, x * IDX, *y);
	free(pos_str);
	obj = &rt->obj[get_obj_index(rt->obj, rt->obj_count, rt->sel.obj_index)];
	if (obj->type == PLANE || obj->type == CYLINDER)
	{
		*y += line_ht + IY;
		mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->info.rot.img, x, *y);
		rot_str = get_info_str(rot);
		display_digit_xpm(rt, rot_str, x * IDX, *y);
		free(rot_str);
	}
}

void	get_info(t_rt *rt, int x, int *y, int line_ht)
{
	if (rt->sel.type == SEL_CAMERA)
		display_camera_info(rt, x, y, line_ht);
	else if (rt->sel.type == SEL_LIGHT)
		display_light_info(rt, x, y, line_ht);
	else if (rt->sel.type == SEL_OBJ)
		display_obj_info(rt, x, y, line_ht);
}

/* static void	setup_info(t_rt *rt, int x, int *y, int line_ht)
{
	char	*pos_str;

	if (rt->sel.type == SEL_CAMERA)
	{
		*y += line_ht;
		mlx_string_put(rt->mlx, rt->mlx_win, x, *y, WHITE, "Pos:");
		pos_str = get_info_str(rt->camera.pos);
		mlx_string_put(rt->mlx, rt->mlx_win, x + 30, *y + 12, WHITE, pos_str);
		free(pos_str);
	}
	else if (rt->sel.type == SEL_LIGHT)
	{
		*y += line_ht;
		mlx_string_put(rt->mlx, rt->mlx_win, x, *y, WHITE, "Pos:");
		pos_str = get_info_str(rt->light.pos);
		mlx_string_put(rt->mlx, rt->mlx_win, x + 30, *y + 12, WHITE, pos_str);
		free(pos_str);
	}
}

static void	obj_info(t_rt *rt, int x, int *y, int line_ht)
{
	char	*pos_str;

	if (rt->sel.type == SEL_OBJ && rt->sel.obj_index >= 0 &&
		(size_t)rt->sel.obj_index < rt->obj_count)
	{
		*y += line_ht;
		mlx_string_put(rt->mlx, rt->mlx_win, x, *y, WHITE, "Pos:");
		if (rt->obj[rt->sel.obj_index].type == SPHERE)
			pos_str = get_info_str(rt->obj[rt->sel.obj_index].sph.pos);
		else if (rt->obj[rt->sel.obj_index].type == PLANE)
			pos_str = get_info_str(rt->obj[rt->sel.obj_index].plane.pos);
		else if (rt->obj[rt->sel.obj_index].type == CYLINDER)
			pos_str = get_info_str(rt->obj[rt->sel.obj_index].cyl.pos);
		else
			return ;
		mlx_string_put(rt->mlx, rt->mlx_win, x + 30, *y + 12, WHITE, pos_str);
		free(pos_str);
	}
}

void	get_info(t_rt *rt, int x, int *y, int line_ht)
{
	setup_info(rt, x, y, line_ht);
	obj_info(rt, x, y, line_ht);
}
 */

/* static void	display_camera_info(t_rt *rt, int x, int *y, int line_ht)
{
	char	*pos_str;
	char	*rot_str;
	char	*pos_str;

	*y += line_ht + 12;
	mlx_string_put(rt->mlx, rt->mlx_win, x, *y, WHITE, "Pos:");
	pos_str = get_info_str(rt->camera.pos);
	mlx_string_put(rt->mlx, rt->mlx_win, x + 30, *y, WHITE, pos_str);
	free(pos_str);
	*y += line_ht + 12;
	mlx_string_put(rt->mlx, rt->mlx_win, x, *y, WHITE, "Rot:");
	rot_str = get_info_str(rt->camera.transform.rotate);
	mlx_string_put(rt->mlx, rt->mlx_win, x + 30, *y, WHITE, rot_str);
	free(rot_str);
} */
/*
static void	display_light_info(t_rt *rt, int x, int *y, int line_ht)
{
	*y += line_ht + 12;
	mlx_string_put(rt->mlx, rt->mlx_win, x, *y, WHITE, "Pos:");
	pos_str = get_info_str(rt->light.pos);
	mlx_string_put(rt->mlx, rt->mlx_win, x + 30, *y, WHITE, pos_str);
	free(pos_str);
}
*/