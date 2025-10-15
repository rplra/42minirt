/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit_bvh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:34:59 by hsim              #+#    #+#             */
/*   Updated: 2025/10/15 13:10:46 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * child function in hit_aabb
 * brief: updates the valid distance range along a ray where intersections happen
 * t0 = entry point, t1 = exit point of bouding box,
 * 		thus only check the hit within that range
 * efficiency and performance by range and reduced intersection calculations
 */
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

/*
 * hit function for bounding_box aabb 
 * brief: checks if the ray passes through all 3 boundaries of the bounding box
 * 
 * 1. convert ray vec to array for maths ops
 * 2. calculate inverse dir for curr axis
 * 		(used to avoid division in intersection calculation)
 * 3. distance where ray exits the box of this axis
 * 4. update ray range based on entry/exit
 * 5. checks if ray doesnt intersect the box on all axes
 * #  P = o + (t*d)
 *    t = (P-o) / d  //that is what axis_inv for (1/d)
 */
int	hit_aabb(t_ray r, t_interval ray_t, t_interval bbox[3])
{
	int		axis;
	float	axis_inv;
	float	ray_dir[3];
	float	ray_orig[3];
	float	t[2];

	axis = -1;
	vec3_to_arr(r.vector, ray_dir);
	vec3_to_arr(r.orig, ray_orig);
	while (++axis < 3)
	{
		axis_inv = 1 / ray_dir[axis];
		t[0] = (bbox[axis].min - ray_orig[axis]) * axis_inv;
		t[1] = (bbox[axis].max - ray_orig[axis]) * axis_inv;
		assign_ray_t(t[0], t[1], &ray_t);
		if (ray_t.max < ray_t.min)
			return (0);
	}
	return (1);
}

/* 
 * brief: recursively traverse a BVH tree to find which obj a ray might hit
 * recursion ensures that every obj in scene gets checked and if any ray hit it
 * t[2];	// array to store hit result for left and right children
 * 
 * 1. it will check the root of the tree first (there are objects)
 * 2. check left child > if hit > go deeper and check obj
 * 3. check right child > if hit > go deeper and check obj
 * hit = check objs inside
 * miss = skip entire subtree
 */
bool	hit_bvh(t_bvh_tree *bvh, t_interval ray_range, t_ray ray, t_rt *rt)
{
	bool	t[2];

	bool (*has_hit[3])(t_rt * rt, int i, t_interval rg, t_ray r);
	if (!hit_aabb(ray, ray_range, bvh->bbox))
		return (0);
	t[L] = 0;
	t[R] = 0;
	if (bvh->type[L] != BVH || bvh->type[R] != BVH)
		init_hit_func(has_hit);
	if (bvh->type[L] != BVH)
		t[L] = has_hit[bvh->type[L]](rt, bvh->id[L], ray_range, ray);
	else
		t[L] = hit_bvh(bvh->left, ray_range, ray, rt);
	if (t[L])
		ray_range.max = rt->hit.t;
	if (bvh->type[R] != BVH)
		t[R] = has_hit[bvh->type[R]](rt, bvh->id[R], ray_range, ray);
	else
		t[R] = hit_bvh(bvh->right, ray_range, ray, rt);
	if (t[L] || t[R])
		return (1);
	return (0);
}
