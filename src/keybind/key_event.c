/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:25:47 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/31 13:07:58 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_render_mode(t_rt *rt, int keycode)
{
	if (keycode == KEY_P)
		rt->preview_mode = 1;
	if (keycode == KEY_R)
		rt->preview_mode = 0;
	// /*debug*/printf("preview_mode=%d\n", rt->preview_mode);
	// init_cam(rt);
	// init_bvh_node(rt);
	// init_hit(rt);
	// my_render_image(rt);
	// /*debug*/printf("rendered img after switching mode\n");
}

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
			if (rt->sel.obj_index < (int)rt->obj_count - 1)
				rt->sel.obj_index++;
			else
				rt->sel.type = SEL_CAMERA;
		}
		else
			rt->sel.type = SEL_CAMERA;
	}
	/*debug*/printf("Selected OBJ index = %d\n", rt->sel.obj_index);
	/*debug*/print_selected(rt);
}

void	handle_translation(t_rt *rt, int keycode)
{
	t_vec3	delta;
	t_obj	*obj;

	if (!translation_key(keycode))
		return;

	delta = translation_delta(keycode);

	if (rt->sel.type == SEL_CAMERA)
	{
		/*debug*/printf("++ Translating CAMERA\n");
		rt->camera.pos = add_vec(rt->camera.pos, delta);
		/*debug*/printf("   New CAMERA Pos: (%.2f, %.2f, %.2f)\n",
			rt->camera.pos.x, rt->camera.pos.y, rt->camera.pos.z);
	}
	else if (rt->sel.type == SEL_LIGHT)
	{
		/*debug*/printf("++ Translating LIGHT\n");
		rt->light.pos = add_vec(rt->light.pos, delta);
		/*debug*/printf("   New LIGHT Pos: (%.2f, %.2f, %.2f)\n",
			rt->light.pos.x, rt->light.pos.y, rt->light.pos.z);
	}
	else if (rt->sel.type == SEL_OBJ)
	{
		obj = &rt->obj[rt->sel.obj_index];
		/*debug*/printf("++ Translating OBJECT %d (%s)\n", rt->sel.obj_index,
			obj->type == SPHERE ? "SPHERE" :
			obj->type == PLANE ? "PLANE" :
			obj->type == CYLINDER ? "CYLINDER" : "UNKNOWN");

		if (obj->type == PLANE)
		{
			/*debug*/printf("   Old Pos @%p: (%.2f, %.2f, %.2f)\n", (void*)&obj->plane.pos,
				obj->plane.pos.x, obj->plane.pos.y, obj->plane.pos.z);
			obj->plane.pos = add_vec(obj->plane.pos, delta);
			/*debug*/printf("   New Pos: (%.2f, %.2f, %.2f)\n",
				obj->plane.pos.x, obj->plane.pos.y, obj->plane.pos.z);
		}
		else if (obj->type == SPHERE)
		{
			/*debug*/printf("   Old Pos @%p: (%.2f, %.2f, %.2f)\n", (void*)&obj->sph.pos,
				obj->sph.pos.x, obj->sph.pos.y, obj->sph.pos.z);
			obj->sph.pos = add_vec(obj->sph.pos, delta);
			/*debug*/printf("   New Pos: (%.2f, %.2f, %.2f)\n",
				obj->sph.pos.x, obj->sph.pos.y, obj->sph.pos.z);
		}
		else if (obj->type == CYLINDER)
		{
			/*debug*/printf("   Old Pos @%p: (%.2f, %.2f, %.2f)\n", (void*)&obj->cyl.pos,
				obj->cyl.pos.x, obj->cyl.pos.y, obj->cyl.pos.z);
			obj->cyl.pos = add_vec(obj->cyl.pos, delta);
			/*debug*/printf("   New Pos: (%.2f, %.2f, %.2f)\n",
				obj->cyl.pos.x, obj->cyl.pos.y, obj->cyl.pos.z);
		}
	}
}

void	handle_scale(t_rt *rt, int keycode)
{
	float	scale;;
	t_obj	*obj;

	if (!scale_key(keycode))
		return;
	scale = scale_factor(keycode);
	if (rt->sel.type == SEL_OBJ)
	{
		obj = &rt->obj[rt->sel.obj_index];
		if (obj->type == SPHERE)
			obj->sph.rad *= scale;
		else if (obj->type == CYLINDER)
		{
			obj->cyl.rad *= scale;
			obj->cyl.height *= scale;
		}
	}
}
