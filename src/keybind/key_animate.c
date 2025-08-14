/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_animate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:17:00 by hsim              #+#    #+#             */
/*   Updated: 2025/08/14 16:47:53 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	handle_animate_light(t_rt *rt)
{
	int		id;
	t_obj	*obj;
	t_vec3	delta;

	rt->animate.count += 1;
	if (rt->animate.count % 4 == 3)
		rt->animate.pos *= -1;
	if (rt->animate.count == 4)
		rt->animate.count = 0;
	delta = new_vec3(0, rt->animate.pos, 0);
	id = get_light_index(rt->obj, rt->obj_count);
	obj = &rt->obj[id];
	obj->sph.pos = add_vec(obj->sph.pos, delta);
	assign_bbox_translate(obj, delta);
}

static void	handle_animate_ambient(t_rt *rt)
{
	if (rt->animate.intensity >= 1)
		rt->animate.step *= -1;
	else if (rt->animate.intensity <= 0.16)
		rt->animate.step = 0.08;
	rt->animate.intensity += rt->animate.step;
}

int	animate_light(t_rt *rt)
{
	float	rotate;

	if (rt->b_animate == 0)
		return (0);
	handle_animate_ambient(rt);
	init_bg_color(rt, rt->animate.intensity);
	handle_animate_light(rt);
	rotate = rt->animate.step * 20;
	rt->camera.transform.rotate = add_vec(rt->camera.transform.rotate,
			new_vec3(0, rotate, 0));
	rt->sel.type = SEL_CAMERA;
	update_cam_pos(rt, 0);
	free_bvh(rt->bvh);
	init_bvh_node(rt);
	my_render_img(rt);
	return (0);
}
