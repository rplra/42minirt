/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 13:45:13 by hsim              #+#    #+#             */
/*   Updated: 2025/07/09 12:15:03 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * child function in hit
 * calls respective has_hit function depending on object type
 */
void	init_hit_func(bool (*has_hit[])())
{
	has_hit[SPHERE] = has_hit_sphere;
}

/*
 * child function in hit
 * calls respective get_surf_norm function depending on object type
 */
void	init_surf_norm(t_vec3 (*get_surf_norm[])(t_ray, t_obj, float))
{
	get_surf_norm[SPHERE] = get_surf_norm_sph;
}

/*
 * child function in ray_color
 * checks if ray hits any surface
 * returns the closest point ray hits
 * at = origin + (t * direction)
 */
// t_obj	*hit(t_rt *vars, t_interval ray_range, t_ray ray, t_vec3 *at)
t_obj	*hit(t_rt *vars, t_interval ray_range, t_ray ray)
{
	float		t;
	t_obj		*res;
	bool		(*has_hit[3])(t_rt *, int, t_interval, t_ray);

	init_hit_func(has_hit);
	res = NULL;
	/*debug*/printf("_________start_hit_________\n");
	// vars->rec.t = -42;
	// vars->rec.hit = NULL;

	// int	x = -1;
	// while (++x < vars->obj_count)
	// {
		// /*debug*/printf("id:%d\n", x);
		// t = has_hit[vars->obj[x].type](vars, x, ray_range, ray); //this returns t value only, more like get_root
		t = hit_bvh(vars->bvh, ray_range, ray, vars);
		// returns -1 if fail
		// /*debug*/printf("has_hit_sphere:t:%f\n", t);
		/*debug*/printf("t! %f %d\n", t, vars->rec.index);
		// if (vars->rec.t > 0)
		if (t > 0)
		{
			res = &vars->obj[vars->rec.index];
			// ray_range.max = vars->rec.t;	//maybe no need
		}
	// }
	return (res);
}

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
			return (0);
	}
	return (1);
}

bool	hit_bvh(t_bvh_tree *bvh, t_interval ray_range, t_ray ray, t_rt *vars) //bbox belongs to t_bvh bbox
{
	bool	t[2];
	bool	(*has_hit[3])(t_rt *, int, t_interval, t_ray);

	/*debug*/debug_print_bbox("hit_bvh", bvh->bbox);
	if (!hit_aabb(ray, ray_range, bvh->bbox))
	{
		/*debug*/printf("\n\033[93mno aabb! %d~%d\033[0m\n\n", bvh->id[L], bvh->id[R]);
		return (0);
	}

	t[L] = 0;
	t[R] = 0;
	if (bvh->type[L] != BVH || bvh->type[R] != BVH)
		init_hit_func(has_hit);

	/* ******************************************** */
	if (bvh->type[L] != BVH)
	{
		/*debug*/printf("bvh_id_L:%d  %d\n", bvh->id[L], bvh->type[L]);
		t[L] = has_hit[bvh->type[L]](vars, bvh->id[L], ray_range, ray);
	}
	else
	{
		/*debug*/printf("BVH_node [L]\n");
		t[L] = hit_bvh(bvh->left, ray_range, ray, vars);
	}

	if (bvh->type[R] != BVH)
	{
		/*debug*/printf("bvh_id_R:%d  %d, rec.t:%f\n", bvh->id[R], bvh->type[R], vars->rec.t);
		if (t[L] > 0.01f)
			ray_range.max = vars->rec.t;
		t[R] = has_hit[bvh->type[R]](vars, bvh->id[R], ray_range, ray);
		// if (t[L] > 0.01f)
		// 	t[R] = has_hit[bvh->type[R]](vars, bvh->id[R], new_interval(ray_range.min, vars->rec.t), ray);
		// else
		// 	t[R] = has_hit[bvh->type[R]](vars, bvh->id[R], new_interval(ray_range.min, ray_range.max), ray);
	}
	else
	{
		/*debug*/printf("BVH_node [R]\n");
		t[R] = hit_bvh(bvh->right, ray_range, ray, vars);
	}
	/* ******************************************** */

	/*debug*/printf("t[L] & t[R]: %d %d  %d~%d\n", t[L], t[R], bvh->id[L], bvh->id[R]);
	if (t[L] > 0.001f || t[R] > 0.001f)
	{
		// /*debug*/printf("hit!\n");
		return (1);
	}
	// /*debug*/printf("hit fell\n");
	return (0);
}
