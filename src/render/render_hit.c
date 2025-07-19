/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 13:45:13 by hsim              #+#    #+#             */
/*   Updated: 2025/07/14 21:45:40 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * child function in hit
 * calls respective get_surf_norm function depending on object type
 */
// void	init_surf_norm(t_vec3 (*get_surf_norm[])(t_ray, t_obj, float))
// {
// 	get_surf_norm[SPHERE] = get_surf_norm_sph;
// }

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

/*
ray_range: defines the minimum and maximum valid t values (distance along the ray).
ray: the ray being tested against all scene objects
*/
// checks if a ray hits any object in the scene
// tells what object it hits first and how far away is it
t_obj	*hit(t_rt *vars, t_interval ray_range, t_ray ray)
{
	float		t;						// distance to the closest intersection point
	t_obj		*res;					// pointer to the closest object hit
	// bool		(*has_hit[3])(t_rt *, int, t_interval, t_ray); // check for intersections with diff obj types

	// init_hit_func(has_hit);				// init func pointer array with respective obj funcs
	res = NULL;							// sets pointer to null (not obj hit yet)

	// int	x = -1;
	// while (++x < vars->obj_count)
	// {
		// /*debug*/printf("id:%d\n", x);
		// t = has_hit[vars->obj[x].type](vars, x, ray_range, ray); //this returns t value only, more like get_root
		
		// use bvh tree to efficiently find intersections (returns boolean)
		t = hit_bvh(vars->bvh, ray_range, ray, vars);
		// /*debug*/printf("t! %f %d\n", t, vars->hit.index);
		
		// check if hit was found
		if (t > 0)
		{
			// get a pointer to the actual object hit using index
			res = &vars->obj[vars->hit.index];
			// ray_range.max = vars->rec.t;	//maybe no need
		}
	// }
	// returns pointer to the object hit
	return (res);
}

/* child function in hit_aabb */
// updates the valid distance range along a ray where intersections happen
// t0 = entry point, t1 = exit point of bouding box, thus only check the hit within that range
// efficiency and performance by range and reduced intersection calculations
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
// checks if the ray passes through all 3 boundaries of the bounding box
int	hit_aabb(t_ray r, t_interval ray_t, t_interval bbox[3])
{
	int		axis;
	float	axis_inv; //inverse axis, adinv
	float	ray_vec[3];
	float	ray_orig[3];
	float	t[2];

	axis = -1;
	// converts ray direction and origin to array format
	vec3_to_arr(r.vector, ray_vec);
	vec3_to_arr(r.orig, ray_orig);
	while (++axis < 3)
	{
		// calculate inverse dir for curr axis (used to avoid division in intersection calculation)
		axis_inv = 1 / ray_vec[axis];
		t[0] = (bbox[axis].min - ray_orig[axis]) * axis_inv; 	// distance where ray enters the box of this axis
		t[1] = (bbox[axis].max - ray_orig[axis]) * axis_inv; 	// distance where ray exits the box of this axis
		assign_ray_t(t[0], t[1], &ray_t);						// update ray range based on entry/exit
		if (ray_t.max < ray_t.min)								// checks if ray doesnt intersect the box on all axes
		{
			// /*debug*/printf("hit_aabb: %f %f\n", ray_t.max, ray_t.min);
			return (0);
		}
	}
	return (1);
}

// recursively traverse a BVH tree to find which obj a ray might hit
// recursion ensures that every obj in scene gets checked and if any ray hit it
// 1. it will check the root of the tree first (there are objects)
// 2. check left child > if hit > go deeper and check obj
// 3. check right child > if hit > go deeper and check obj
// hit = check objs inside
// miss = skip entire subtree
bool	hit_bvh(t_bvh_tree *bvh, t_interval ray_range, t_ray ray, t_rt *vars)
{
	bool	t[2];	// array to store hit result for left and right children
	bool	(*has_hit[3])(t_rt *, int, t_interval, t_ray); // func pointers checking intersections with different obj types

	// /*debug*/debug_print_bbox("hit_bvh", bvh->bbox);
	// check if ray hits the current node's bounding box
	if (!hit_aabb(ray, ray_range, bvh->bbox))
	{
		/*debug*/printf("\n\033[93mno aabb! %d~%d\033[0m\n\n", bvh->id[L], bvh->id[R]);
		return (0);
	}

	// init hit results for left and right children to false
	t[L] = 0;
	t[R] = 0;

	// if either child is an obj and not bvh node > init func pointer array
	if (bvh->type[L] != BVH || bvh->type[R] != BVH)
		init_hit_func(has_hit);

	/* ******************************************** */
	// check if left child is an object
	if (bvh->type[L] != BVH)
	{
		// /*debug*/printf("bvh_id_L:%d  %d\n", bvh->id[L], bvh->type[L]);
		// check intersection with the object
		t[L] = has_hit[bvh->type[L]](vars, bvh->id[L], ray_range, ray);
	}
	else
		// if it is node instead of obj, recursively call hit_bvh of left tree
		t[L] = hit_bvh(bvh->left, ray_range, ray, vars);

	// check if right child is an obj
	if (bvh->type[R] != BVH)
	{
		// /*debug*/printf("bvh_id_R:%d  %d, rec.t:%f\n", bvh->id[R], bvh->type[R], vars->hit.t);
		// if left child was hit, update ray range to exclude farther than the current closest hit
		if (t[L] > EPSILON)
			ray_range.max = vars->hit.t;
		// check intersection with right object
		t[R] = has_hit[bvh->type[R]](vars, bvh->id[R], ray_range, ray);
	}
	else
		// if node is bvh, recursively call hit_bvh
		t[R] = hit_bvh(bvh->right, ray_range, ray, vars);
	/* ******************************************** */
	// /*debug*/printf("t[L] & t[R]: %d %d  %d~%d\n", t[L], t[R], bvh->id[L], bvh->id[R]);

	// if neither child was hit, return true
	if (t[L] > EPSILON || t[R] > EPSILON)
		return (1);
	return (0);
}
