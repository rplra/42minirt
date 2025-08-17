/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 13:45:13 by hsim              #+#    #+#             */
/*   Updated: 2025/08/17 15:38:11 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * brief: gets the coordinate of the intersection hit
 * returns a 3d point along a vector ray
 * vec = origin + (t * direction)
 */
t_vec3	point_at(float t, t_ray ray)
{
	return (add_vec(ray.orig, mult_vec_scalar(ray.vector, t)));
}

/*
 * child function in hit
 * calls respective has_hit function depending on object type
 */
void	init_hit_func(bool (*has_hit[])())
{
	has_hit[PLANE] = has_hit_plane;
	has_hit[SPHERE] = has_hit_sphere;
	has_hit[CYLINDER] = has_hit_cylinder;
}

/*
 * ray_range: defines the minimum and maximum valid t values (distance along the ray).
 * ray: the ray being tested against all scene objects
 * 1. use bvh tree to efficiently find intersections (returns boolean)
 * 2. check for hit > get ptr to obj > return ptr to obj hit
*/
t_obj	*hit(t_rt *rt, t_interval ray_range, t_ray ray)
{
	float	t;
	t_obj	*res;

	res = NULL;

	t = hit_bvh(rt->bvh, ray_range, ray, rt);
	if (t > 0)
	{
		res = &rt->obj[rt->hit.index];
		if (res->b_rotate == 1)
			transform_hit_pt(rt, *res);
		// rt->hit.at = add_vec(rt->hit.at, rt->camera.transform.translate);
		// /*debug*/printf("hitted type: %d\n", res->type);
		// /*debug*/debug_print_vec(" |hitted", res->cyl.pos);
		// /*debug*/debug_print_vec(" |hitted_col", res->material.albedo);
	}
	return (res);
}

/* child function in has_hit_sphere, records details of the hitted obj */
int	update_hit_rec(t_rt *rt, int index, t_ray ray, float t)
{
	t_vec3 (*get_surf_norm[3])(t_ray, t_obj, float, t_uchar);

	init_surf_norm(get_surf_norm);
	rt->hit.surf_norm = get_surf_norm[rt->obj[index].type](ray, rt->obj[index], t, rt->hit.setting);	//if t>0
	rt->hit.at = add_vec(ray.orig, mult_vec_scalar(ray.vector, t));
	rt->hit.obj = &rt->obj[index];
	rt->hit.index = index;
	rt->hit.t = t;
	// /*debug*/printf("update_hit_rec: t! %f\n", t);
	return (1);
}

/*
 * child function in ray_color
 * checks if ray hits any surface
 * returns the closest point ray hits
 * at = origin + (t * direction)
 */
// t_obj	*hit(t_rt *vars, t_interval ray_range, t_ray ray, t_vec3 *at)
// using linked list
// t_obj	*hit(t_rt *vars, t_interval ray_range, t_ray ray)
// {
// 	float		t;
// 	t_obj		*tmp;
// 	t_obj		*res;
// 	float		min;
// 	float		(*has_hit[3])(t_obj, t_interval, t_ray);
// 	t_vec3      (*get_surf_norm[3])(t_ray, t_obj, float);

// 	init_hit_func(has_hit);
// 	init_surf_norm(get_surf_norm);
// 	min = ray_range.max;
// 	res = NULL;
// 	tmp = vars->obj;
// 	while (tmp != NULL)
// 	{
// 		// /*debug*/printf("id:%d\n", x);
// 		t = has_hit[tmp->type](*tmp, ray_range, ray); //this returns t value only, more like get_root
// 		// /*debug*/printf("has_hit_sphere:t:%f\n", t);
// 		if (t > ray_range.min && t <= min) // if its new min, keep in record
// 		{
// 			res = tmp;
// 			min = t;
// 			vars->rec.t = t; //hit hittable
// 			// can split this out to end (has_hit_sphere)
// 			vars->rec.at = add_vec(ray.orig, mult_vec_scalar(ray.vector, min)); //min=t
// 			vars->rec.surf_norm = get_surf_norm[res->type](ray, *res, min); //min=t
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (res);
// }


// t_obj	*hit(t_rt *vars, t_interval ray_range, t_ray ray)
// {
// 	float		t;
// 	t_obj		*res;
// 	bool		(*has_hit[3])(t_rt *, int, t_interval, t_ray);
	
// 	int	x = -1;
// 	int	obj_count = vars->obj_count;

// 	init_hit_func(has_hit);
// 	res = NULL;
// 	while (++x < obj_count)
// 	{
// 		// /*debug*/printf("id:%d\n", x);
// 		t = has_hit[vars->obj[x].type](vars, x, ray_range, ray); //this returns t value only, more like get_root
// 		// /*debug*/printf("t! %f %d\n", t, vars->hit.index);
// 		if (t > 0)
// 		{
// 			res = &vars->obj[vars->hit.index];
// 			ray_range.max = vars->hit.t;
// 		}
// 	}
// 	return (res);
// }

