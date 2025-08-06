/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:25:47 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/06 15:33:05 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_render_mode(t_rt *rt, int keycode)
{
	if (keycode == KEY_DOWN)
		rt->b_preview_mode = 1;
	if (keycode == KEY_UP)
		rt->b_preview_mode = 0;
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
			if (rt->sel.obj_index < (int)rt->obj_count - 2) //-1 for light
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

void	handle_translation(t_rt *rt, int keycode)
{
	t_vec3	delta;
	t_obj	*obj;
	int		id;

	if (!translation_key(keycode))
		return;

	delta = translation_delta(keycode);

	if (rt->sel.type == SEL_CAMERA)
	{
		/*debug*/printf("++ Translating CAMERA\n");
		rt->camera.transform.translate = add_vec(rt->camera.transform.translate, delta);
		/*debug*/debug_print_vec("   New CAMERA Pos", rt->camera.pos);
	}
	else if (rt->sel.type == SEL_LIGHT)
	{
		/*debug*/printf("++ Translating LIGHT\n");
		id = get_light_index(rt->obj, rt->obj_count);
		obj = &rt->obj[id];
		obj->sph.pos = add_vec(obj->sph.pos, delta);
		// rt->light.pos = add_vec(rt->light.pos, delta);
		/*debug*/debug_print_vec("   New LIGHT Pos", obj->sph.pos);
		aabb_translate(*obj, obj->bbox, delta);
	}
	else if (rt->sel.type == SEL_OBJ)
	{
		id = get_obj_index(rt->obj, rt->obj_count, rt->sel.obj_index);
		obj = &rt->obj[id];
		/*debug*/printf("++ Translating OBJECT %d (%s)\n", rt->sel.obj_index,
obj->type == SPHERE ? "SPHERE" :
obj->type == PLANE ? "PLANE" :
obj->type == CYLINDER ? "CYLINDER" : "UNKNOWN");

		if (obj->type == PLANE)
		{
			/*debug*/printf("   Old Pos @%p: (%.2f, %.2f, %.2f)\n", (void*)&obj->plane.pos,
obj->plane.pos.x, obj->plane.pos.y, obj->plane.pos.z);
			obj->plane.pos = add_vec(obj->plane.pos, delta);
			obj->plane.d = scalar_product(obj->plane.normal, obj->plane.pos);
			/*debug*/debug_print_vec("   New Pos", obj->plane.pos);
		}
		else if (obj->type == SPHERE)
		{
			/*debug*/printf("   Old Pos @%p: (%.2f, %.2f, %.2f)\n", (void*)&obj->sph.pos,
obj->sph.pos.x, obj->sph.pos.y, obj->sph.pos.z);
			obj->sph.pos = add_vec(obj->sph.pos, delta);
			/*debug*/debug_print_vec("   New Pos", obj->sph.pos);
		}
		else if (obj->type == CYLINDER)
		{
			/*debug*/printf("   Old Pos @%p: (%.2f, %.2f, %.2f)\n", (void*)&obj->cyl.pos,
			obj->cyl.pos.x, obj->cyl.pos.y, obj->cyl.pos.z);
			
			obj->cyl.pos = add_vec(obj->cyl.pos, delta);

			t_vec3	axis_height = mult_vec_scalar(obj->cyl.axis, obj->cyl.height / 2);
			obj->cyl.d[0] = scalar_product(obj->cyl.axis, \
subtract_vec(obj->cyl.pos, axis_height));
			obj->cyl.d[1] = scalar_product(obj->cyl.axis, \
add_vec(obj->cyl.pos, axis_height));
			/*debug*/debug_print_vec("   New Pos", obj->cyl.pos);
		}
		aabb_translate(*obj, obj->bbox, delta);
	}
}

void	handle_scale(t_rt *rt, int keycode)
{
	int		id;
	t_obj	*obj;
	float	scale;

	if (!scale_key(keycode))
		return;
	scale = scale_factor(keycode);
	if (rt->sel.type == SEL_OBJ)
	{
		id = get_obj_index(rt->obj, rt->obj_count, rt->sel.obj_index);
		obj = &rt->obj[id];
		if (obj->type == SPHERE)
			obj->sph.rad *= scale;
		else if (obj->type == CYLINDER)
		{
			obj->cyl.rad *= scale;
			obj->cyl.height *= scale;

			obj->cyl.coord[X] = mult_vec_scalar(obj->cyl.coord[X], scale);
			obj->cyl.coord[Y] = mult_vec_scalar(obj->cyl.coord[Y], scale);
			obj->cyl.d[0] = scalar_product(obj->cyl.axis, subtract_vec(obj->cyl.pos, \
mult_vec_scalar(obj->cyl.axis, obj->cyl.height / 2)));
			obj->cyl.d[1] = scalar_product(obj->cyl.axis, add_vec(obj->cyl.pos, \
mult_vec_scalar(obj->cyl.axis, obj->cyl.height / 2)));
			t_vec3	n = cross_product(obj->cyl.coord[X], obj->cyl.coord[Y]);
			obj->cyl.w = div_vec_scalar(n, scalar_product(n, n));
			//coord, n, d, w, bbox
		}
		create_bbox(obj, obj->bbox);
	}
}

void	handle_focus_dist(t_rt *rt, int keycode)
{
	if (!focus_dist_key(keycode))
		return ;
	if (keycode == KEY_C)
		rt->camera.focus_dist += FOCUS_DIST;
	else if (keycode == KEY_X)
		rt->camera.focus_dist -= FOCUS_DIST;
	if (rt->camera.focus_dist < 1)
		rt->camera.focus_dist = 1;
	printf(">> Focus distance: %f\n", rt->camera.focus_dist);
}
