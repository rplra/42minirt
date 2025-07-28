/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 13:45:13 by hsim              #+#    #+#             */
/*   Updated: 2025/07/28 10:02:24 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

// hit without bvh
// /*
// ray_range: defines the minimum and maximum valid t values (distance along the ray).
// ray: the ray being tested against all scene objects
// */
// t_obj	*hit(t_rt *rt, t_interval ray_range, t_ray ray)
// {
// 	float		t;
// 	t_obj		*res;
// 	bool		(*has_hit[3])(t_rt *, int, t_interval, t_ray);

// 	init_hit_func(has_hit);
// 	res = NULL;

// 	int	x = -1;
// 	while (++x < rt->obj_count)
// 	{
// 		t = has_hit[rt->obj[x].type](rt, x, ray_range, ray);
// 		if (t > 0)
// 		{
// 			res = &rt->obj[rt->hit.index];
// 			ray_range.max = rt->hit.t;
// 		}
// 	}
// 	return (res);
// }

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
ray_range: defines the minimum and maximum valid t values (distance along the ray).
ray: the ray being tested against all scene objects
*/
t_obj	*hit(t_rt *rt, t_interval ray_range, t_ray ray)
{
	float		t;
	t_obj		*res;

	res = NULL;
	
	t = hit_bvh(rt->bvh, ray_range, ray, rt);
	if (t > 0)
	{
		res = &rt->obj[rt->hit.index];
		// if (res->b_rotate == 1)
		// {
		// 	rt->hit.at = local_to_global(res->rotate, rt->hit.at);
		// 	rt->hit.surf_norm = local_to_global(res->rotate, rt->hit.surf_norm);
		// }
		// /*debug*/printf("hitted type: %d\n", res->type);
		// /*debug*/debug_print_vec(" |hitted", res->cyl.pos);
		// /*debug*/debug_print_vec(" |hitted_col", res->material.albedo);
	}
	return (res);
}

// t_obj	*hit(t_rt *rt, t_interval ray_range, t_ray ray)
// {
// 	float		t;
// 	t_obj		*res;

// 	res = NULL;

// 	t = hit_bvh(rt->bvh, ray_range, ray, rt);
// 	if (t > 0)
// 	{
// 		res = &rt->obj[rt->hit.index];
// 		// /*debug*/printf("hitted type: %d\n", res->type);
// 		// /*debug*/debug_print_vec(" |hitted", res->cyl.pos);
// 		// /*debug*/debug_print_vec(" |hitted_col", res->material.albedo);
// 	}
// 	return (res);
// }

/* child function in hit_aabb */
void	assign_ray_t(float t0, float t1, t_interval *ray_t)
{
	if (t0 < t1)
	{
		if (t0 > ray_t->min)
			ray_t->min = t0;
		if (t1 < ray_t->max)
			ray_t->max = t1;
	}
	else
	{
		if (t1 > ray_t->min)
			ray_t->min = t1;
		if (t0 < ray_t->max)
			ray_t->max = t0;
	}
}

/* hit function for bounding_box aabb */
int	hit_aabb(t_ray r, t_interval ray_t, t_interval bbox[3])
{
	int		axis;
	float	axis_inv; //inverse axis, adinv
	float	ray_vec[3];
	float	ray_orig[3];
	float	t[2];

	axis = -1;
	vec3_to_arr(r.vector, ray_vec);
	vec3_to_arr(r.orig, ray_orig);
	while (++axis < 3)
	{
		axis_inv = 1 / ray_vec[axis];
		t[0] = (bbox[axis].min - ray_orig[axis]) * axis_inv;
		t[1] = (bbox[axis].max - ray_orig[axis]) * axis_inv;
		assign_ray_t(t[0], t[1], &ray_t);
		if (ray_t.max < ray_t.min)
		{
			// /*debug*/printf("hit_aabb: %f %f\n", ray_t.max, ray_t.min);
			return (0);
		}
	}
	return (1);
}

bool	hit_bvh(t_bvh_tree *bvh, t_interval ray_range, t_ray ray, t_rt *vars)
{
	bool	t[2];
	bool	(*has_hit[3])(t_rt *, int, t_interval, t_ray);

	// /*debug*/debug_print_bbox("hit_bvh", bvh->bbox);
	if (!hit_aabb(ray, ray_range, bvh->bbox))
	{
		// /*debug*/printf("\n\033[93mno aabb! %d~%d\033[0m\n\n", bvh->id[L], bvh->id[R]);
		return (0);
	}

	t[L] = 0;
	t[R] = 0;
	if (bvh->type[L] != BVH || bvh->type[R] != BVH)
		init_hit_func(has_hit);

	/* ******************************************** */
	if (bvh->type[L] != BVH)
	{
		// /*debug*/printf("bvh_id_L:%d  %d\n", bvh->id[L], bvh->type[L]);
		// transform frm world space to obj space
		t[L] = has_hit[bvh->type[L]](vars, bvh->id[L], ray_range, ray);
	}
	else
		t[L] = hit_bvh(bvh->left, ray_range, ray, vars);

	if (bvh->type[R] != BVH)
	{
		// /*debug*/printf("bvh_id_R:%d  %d, rec.t:%f\n", bvh->id[R], bvh->type[R], vars->hit.t);
		if (t[L] > EPSILON)
			ray_range.max = vars->hit.t;
		t[R] = has_hit[bvh->type[R]](vars, bvh->id[R], ray_range, ray);
	}
	else
		t[R] = hit_bvh(bvh->right, ray_range, ray, vars);
	/* ******************************************** */
	// /*debug*/printf("t[L] & t[R]: %d %d  %d~%d\n", t[L], t[R], bvh->id[L], bvh->id[R]);
	if (t[L] > EPSILON || t[R] > EPSILON)
		return (1);
	return (0);
}
