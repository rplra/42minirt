/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_selection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 20:23:59 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/05 15:05:42 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// helper function for label generation
static void get_label(char *label, t_obj_type type, size_t index)
{
	const char *names[] = {"Sphere", "Plane", "Cylinder"};
	int			len;

	if (type >= SPHERE && type <= CYLINDER)
	{
		len = ft_strlcpy(label, names[type - SPHERE], 20);
		label[len] = ' ';
		label[len + 1] = '0' + (index % 10);
		label[len + 2] = '\0';
	}
	else
		label[0] = '\0';
}

// highlight color selection
static int	highlight_sel(t_rt *rt, t_sel_type type, int index)
{
	const int	cols[2] = {WHITE, CYAN};
	int			is_highlighted;
	
	is_highlighted = 0;
	if (type == SEL_CAMERA && rt->sel.type == SEL_CAMERA)
		is_highlighted = 1;	
	else if (type == SEL_LIGHT && rt->sel.type == SEL_LIGHT)
		is_highlighted = 1;	
	else if (type == SEL_OBJ && rt->sel.type == SEL_OBJ
		&& rt->sel.obj_index == index)
		is_highlighted = 1;	
	return(cols[is_highlighted]);
}

// setup selection
static void	setup_selection(t_rt *rt, int x, int *y, int line_ht)
{
	char	*names[] = {"Camera", "Light"};
	t_sel_type	types[2];
	int			i;
	int			col;

	types[0] = SEL_CAMERA;
	types[1] = SEL_LIGHT;
	i = -1;
	while (++i < 2)
	{
		*y += line_ht;
		col = highlight_sel(rt, types[i], 0);
		mlx_string_put(rt->mlx, rt->mlx_win, x, *y, col, names[i]);
		// mlx_string_put(rt->mlx, rt->mlx_win, x + 20, *y, col, names[i]);
	}
}

// object selection
static void obj_selection(t_rt *rt, int x, int *y, int line_ht)
{
	size_t	i;
	int		col;
	char	label[32];

	i = -1;
	while (++i < rt->obj_count)
	{
		get_label(label, rt->obj[i].type, i);
		if (label[0])
		{
			*y += line_ht;
			col = highlight_sel(rt, SEL_OBJ, i);
			mlx_string_put(rt->mlx, rt->mlx_win, x, *y, col, label);
			// mlx_string_put(rt->mlx, rt->mlx_win, x + 20, *y, col, label);
		}
	}
}

// main key_selection
void	selection_guide(t_rt *rt)
{
	int	x;
	int	y;
	int	line_ht;

	x = WIN_WIDTH + (PANEL_WIDTH * 0.48);
	y = WIN_HEIGHT * 0.9;
	line_ht = 12;
	mlx_string_put(rt->mlx, rt->mlx_win, x, y, WHITE, "SELECTION");
	setup_selection(rt, x, &y, line_ht);
	obj_selection(rt, x, &y, line_ht);
}

/* original selection guide */
// void	selection_guide(t_rt *rt)
// {
// 	int	x;
// 	int	y;
// 	int	line_ht;

// 	x = WIN_WIDTH + 20;
// 	y = 290;
// 	line_ht = 12;
// 	mlx_string_put(rt->mlx, rt->mlx_win, x, y, WHITE, "SELECTION");
// 	setup_selection(rt, x, &y, line_ht);
// 	obj_selection(rt, x, &y, line_ht);
// }
