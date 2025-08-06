/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:41:42 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/06 11:25:00 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_selected(t_rt *rt)
{
	t_obj	*obj;
	int		id;

	if (rt->sel.type == SEL_CAMERA)
	{
		printf(">> Selected: CAMERA\n");
		printf("   Pos: (%.2f, %.2f, %.2f)\n",
			rt->camera.pos.x, rt->camera.pos.y, rt->camera.pos.z);
		debug_print_vec("   Rot", rt->camera.transform.rotate);
	}
	else if (rt->sel.type == SEL_LIGHT)
	{
		id = get_light_index(rt->obj, rt->obj_count);
		obj = &rt->obj[id];
		printf(">> Selected: LIGHT\n");
		printf("   Pos: (%.2f, %.2f, %.2f)\n",
obj->sph.pos.x, obj->sph.pos.y, obj->sph.pos.z);
		debug_print_vec("   Rot", obj->rotate);

// rt->light.pos.x, rt->light.pos.y, rt->light.pos.z);
	}
	else if (rt->sel.type == SEL_OBJ)
	{
		id = get_obj_index(rt->obj, rt->obj_count, rt->sel.obj_index);
		obj = &rt->obj[id];
		printf(">> Selected: OBJECT %d (", rt->sel.obj_index);
		if (obj->type == SPHERE)
		{
			printf("SPHERE)\n");
			printf("   Pos: (%.2f, %.2f, %.2f)\n",
				obj->sph.pos.x, obj->sph.pos.y, obj->sph.pos.z);
		}
		else if (obj->type == PLANE)
		{
			printf("PLANE)\n");
			printf("   Pos: (%.2f, %.2f, %.2f)\n",
				obj->plane.pos.x, obj->plane.pos.y, obj->plane.pos.z);
		}
		else if (obj->type == CYLINDER)
		{
			printf("CYLINDER)\n");
			printf("   Pos: (%.2f, %.2f, %.2f)\n",
				obj->cyl.pos.x, obj->cyl.pos.y, obj->cyl.pos.z);
		}
		else
			printf("UNKNOWN TYPE)\n");
		debug_print_vec("   Rot", obj->rotate);
	}
	else
		printf(">> Selected: UNKNOWN\n");
}
