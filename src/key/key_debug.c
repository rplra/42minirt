/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:41:42 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/22 08:01:46 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_selected_setup(t_rt *rt)
{
	t_obj	*obj;
	int		id;

	if (rt->sel.type == SEL_CAMERA)
	{
		printf(">> Selected: CAMERA\n");
		debug_print_vec("   Pos", rt->camera.pos);
		debug_print_vec("   Rot", rt->camera.transform.rotate);
	}
	else if (rt->sel.type == SEL_LIGHT)
	{
		id = get_light_index(rt->obj, rt->obj_count);
		obj = &rt->obj[id];
		printf(">> Selected: LIGHT\n");
		debug_print_vec("   Pos", obj->sph.pos);
		debug_print_vec("   Rot", obj->rotate);
	}
}

static void	print_obj_details(t_obj *obj)
{
	if (obj->type == SPHERE)
	{
		printf("SPHERE)\n");
		debug_print_vec("   Pos", obj->sph.pos);
	}
	else if (obj->type == PLANE)
	{
		printf("PLANE)\n");
		debug_print_vec("   Pos", obj->plane.pos);
	}
	else if (obj->type == CYLINDER)
	{
		printf("CYLINDER)\n");
		debug_print_vec("   Pos", obj->cyl.pos);
	}
	else
		printf(">> Selected: UNKNOWN obj\n");
}

static void	print_selected_obj(t_rt *rt)
{
	t_obj	*obj;
	int		id;

	id = get_obj_index(rt->obj, rt->obj_count, rt->sel.obj_index);
	obj = &rt->obj[id];
	printf(">> Selected: OBJECT %d (", rt->sel.obj_index);
	print_obj_details(obj);
	debug_print_vec("   Rot", obj->rotate);
}

void	print_selected(t_rt *rt)
{
	if (rt->sel.type == SEL_CAMERA || rt->sel.type == SEL_LIGHT)
		print_selected_setup(rt);
	else if (rt->sel.type == SEL_OBJ)
		print_selected_obj(rt);
	else
		printf(">> Selected: UNKNOWN\n");
}
