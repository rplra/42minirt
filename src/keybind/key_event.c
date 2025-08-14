/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:25:47 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/14 12:33:16 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_render_mode(t_rt *rt, int keycode)
{
	if (keycode == KEY_DOWN)
		rt->b_preview_mode = 1;
	if (keycode == KEY_UP)
		rt->b_preview_mode = 0;
}

void	handle_show_light(t_rt *rt, int keycode)
{
	if (keycode != KEY_SPACE)
		return ;
	if (rt->sel.type == SEL_LIGHT)
	{
		if (!rt->b_show_light && keycode == KEY_SPACE)
			rt->b_show_light = 1;
		else if (rt->b_show_light && keycode == KEY_SPACE)
			rt->b_show_light = 0;
	}
}





// void	handle_translation(t_rt *rt, int keycode)
// {
// 	t_vec3	delta;
// 	t_obj	*obj;
// 	int		id;

// 	if (!translation_key(keycode))
// 		return;

// 	delta = translation_delta(keycode);

// 	if (rt->sel.type == SEL_CAMERA)
// 	{
// 		/*debug*/printf("++ Translating CAMERA\n");
// 		rt->camera.transform.translate = add_vec(rt->camera.transform.translate, delta);
// 		/*debug*/debug_print_vec("   New CAMERA Pos", rt->camera.pos);
// 	}
// 	else if (rt->sel.type == SEL_LIGHT)
// 	{
// 		/*debug*/printf("++ Translating LIGHT\n");
// 		id = get_light_index(rt->obj, rt->obj_count);	//light is always the last obj
// 		obj = &rt->obj[id];
// 		obj->sph.pos = add_vec(obj->sph.pos, delta);
// 		/*debug*/debug_print_vec("   New LIGHT Pos", obj->sph.pos);
// 		assign_bbox_translate(obj, delta);
// 	}
// 	else if (rt->sel.type == SEL_OBJ)
// 	{
// 		id = get_obj_index(rt->obj, rt->obj_count, rt->sel.obj_index);
// 		obj = &rt->obj[id];
// 		/*debug*/printf("++ Translating OBJECT %d (%s)\n", rt->sel.obj_index,
// obj->type == SPHERE ? "SPHERE" :
// obj->type == PLANE ? "PLANE" :
// obj->type == CYLINDER ? "CYLINDER" : "UNKNOWN");

// 		if (obj->type == PLANE)
// 		{
// 			/*debug*/printf("   Old Pos @%p: (%.2f, %.2f, %.2f)\n", (void*)&obj->plane.pos,
// obj->plane.pos.x, obj->plane.pos.y, obj->plane.pos.z);
// 			obj->plane.pos = add_vec(obj->plane.pos, delta);
// 			obj->plane.d = scalar_product(obj->plane.normal, obj->plane.pos);
// 			/*debug*/debug_print_vec("   New Pos", obj->plane.pos);
// 		}
// 		else if (obj->type == SPHERE)
// 		{
// 			/*debug*/printf("   Old Pos @%p: (%.2f, %.2f, %.2f)\n", (void*)&obj->sph.pos,
// obj->sph.pos.x, obj->sph.pos.y, obj->sph.pos.z);
// 			obj->sph.pos = add_vec(obj->sph.pos, delta);
// 			/*debug*/debug_print_vec("   New Pos", obj->sph.pos);
// 		}
// 		else if (obj->type == CYLINDER)
// 		{
// 			/*debug*/printf("   Old Pos @%p: (%.2f, %.2f, %.2f)\n", (void*)&obj->cyl.pos,
// obj->cyl.pos.x, obj->cyl.pos.y, obj->cyl.pos.z);
			
// 			obj->cyl.pos = add_vec(obj->cyl.pos, delta);
// 			obj->cyl.d[0] = scalar_product(obj->cyl.axis, \
// subtract_vec(obj->cyl.pos, obj->cyl.axis_height));
// 			obj->cyl.d[1] = scalar_product(obj->cyl.axis, \
// add_vec(obj->cyl.pos, obj->cyl.axis_height));

// 			/*debug*/debug_print_vec("   New Pos", obj->cyl.pos);
// 		}
// 		assign_bbox_translate(obj, delta);
// 	}
// }
