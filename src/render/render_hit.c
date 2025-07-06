/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 13:45:13 by hsim              #+#    #+#             */
/*   Updated: 2025/07/06 18:52:36 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * check all sph objects to see which is the closest hit
 * 
 * derived from quadratic equation discriminant formula
 * b sq - 4ac >= 0 (hit sphere)
 * b sq - 4ac < 0 (doesnt hit sphere)
 * full formula:
 * [-b +- sqrt(b sq - 4ac)]  /  2a
 * shortened:
 * [b +- sqrt(b sq - ac)]  /  a
 * 
 * res = discriminant
 * expanded frm sphere equation x sq + y sq + z sq - r sq = 0
 * vector from point P on ray -> sphere center C
 * 
 * returns the closest point if there are 2 roots
 * unsigned int max: 4294967295 as limit num
 * 
 * formula expansion reference:
 * https://raytracing.github.io/books/RayTracingInOneWeekend.html
 * https://youtu.be/ebzlMOw79Yw?si=8SXTPsEcSUtwft71
 */
float	has_hit_sphere(t_obj obj, t_interval ray_range, t_ray ray)
{
	float		n[3];
	float		discriminant;
	float		tmp;
	t_vec3		ray_to_center;

	ray_to_center = subtract_vec(obj.sph.orig, ray.orig);
	n[A] = scalar_product(ray.vector, ray.vector) + EPS;
	n[B] = scalar_product(ray.vector, ray_to_center) + EPS;
	n[C] = scalar_product(ray_to_center, ray_to_center) - \
(obj.sph.rad * obj.sph.rad) + EPS;

	discriminant = (n[B] * n[B]) - (n[A] * n[C]);
	if (discriminant < 0)
		return (-1);
	tmp = (n[B] - sqrt(discriminant)) / n[A];
	if (tmp <= ray_range.min || tmp >= ray_range.max) //0 to 4294967295
	{
		tmp = (n[B] + sqrt(discriminant)) / n[A];
		if (tmp <= ray_range.min || tmp >= ray_range.max)
			return (-1);
	}
	/*debug*/printf("has_hit_sphere:%f %f\n", tmp, discriminant);
	return (tmp);
}

/*
 * child function in hit
 * calls respective has_hit function depending on object type
 */
void	init_hit_func(float (*has_hit[])())
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
	// t_obj		*tmp;
	t_obj		*res;
	float		current_min;
	float		(*has_hit[3])(t_obj, t_interval, t_ray);
	t_vec3      (*get_surf_norm[3])(t_ray, t_obj, float);

	init_hit_func(has_hit);
	init_surf_norm(get_surf_norm);
	current_min = ray_range.max;
	res = NULL;
	// tmp = vars->obj;

	int	x = -1;
	// while (tmp != NULL)
	while (++x < vars->obj_count)
	{
		// /*debug*/printf("id:%d\n", x);
		t = has_hit[vars->obj[x].type](vars->obj[x], ray_range, ray); //this returns t value only, more like get_root
		// returns -1 if fail
		// /*debug*/printf("has_hit_sphere:t:%f\n", t);
		if (t > ray_range.min && t <= current_min) // if its new min, keep in record
		{
			res = &vars->obj[x];
			current_min = t;
			vars->rec.t = t; //hit hittable
			// can split this out to end (has_hit_sphere)
			vars->rec.at = add_vec(ray.orig, mult_vec_scalar(ray.vector, current_min)); //min=t
			vars->rec.surf_norm = get_surf_norm[res->type](ray, *res, current_min); //min=t
		}
	}
	return (res);
}

// t_obj	*hit(t_rt *vars, t_ray ray, t_vec3 *surf_norm, t_vec3 *at)
// {
// 	float		t;
// 	t_obj		*tmp;
// 	t_obj		*res;
// 	float		min;
// 	float		(*has_hit[3])(t_obj, t_ray);
// 	t_vec3      (*get_surf_norm[3])(t_ray, t_obj, float);

// 	init_hit_func(has_hit);
// 	init_surf_norm(get_surf_norm);
// 	min = 2147483647.0;
// 	res = NULL;
// 	tmp = vars->obj;
// 	while (tmp != NULL)
// 	{
// 		// /*debug*/printf("id:%d\n", x);
// 		t = has_hit[tmp->type](*tmp, ray);
// 		// /*debug*/printf("has_hit_sphere:t:%f\n", t);
// 		if (t > 0.001 && t <= min) // if its new min, keep in record
// 		{
// 			res = tmp;
// 			min = t;
// 			// can split this out to end
// 			*at = add_vec(ray.orig, mult_vec_scalar(ray.vector, min));
// 			*surf_norm = get_surf_norm[res->type](ray, *res, min);
// 		}
// 		tmp = tmp->next;
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
		else if (t1 < ray_t->max)
			ray_t->max = t1;
	}
	else
	{
		if (t1 > ray_t->min)
			ray_t->min = t1;
		else if (t0 < ray_t->max)
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
		if (ray_t.max <= ray_t.min)
			return (-1);
	}
	return (0);
}

int	hit_bvh(t_ray ray, t_interval ray_range, t_rt vars, t_interval bbox[3]) //bbox belongs to t_bvh bbox
{
	t_obj *hit_left;
	t_obj *hit_right;

	if (!hit_aabb(ray, ray_range, bbox))
		return (0);

	// bool hit_left = left->hit(r, ray_t, rec); //call respective git function of obj
	// bool hit_right = right->hit(r, interval(ray_t.min, hit_left ? rec.t : ray_t.max), rec);

	hit_left = hit(&vars, ray_range, vars.ray); //call hit_func based on obj_type
	if (hit_left)
		hit_right = hit(&vars, new_interval(ray_range.min, vars.rec.t), ray);
	else
		hit_right = hit(&vars, new_interval(ray_range.min, ray_range.max), ray);
	if (hit_left || hit_right)
		return (1); //return t
	return (-1);
}

static bool box_compare(t_obj a, t_obj b, int axis)
{
	(void) axis;

	t_interval	a_axis_interval[3];
	t_interval	b_axis_interval[3];

	/*debug*/debug_print_vec("a", a.sph.orig);
	/*debug*/debug_print_vec("b", b.sph.orig);
	get_bbox(&a, a_axis_interval);
	get_bbox(&b, b_axis_interval);

	/*debug*/printf("a.[%d].min: %f, b.[%d].min: %f\n", axis, a_axis_interval[axis].min, axis, b_axis_interval[axis].min);
	return (a_axis_interval[axis].min < b_axis_interval[axis].min);
	// return (a.sph.orig.z < b.sph.orig.z);
}

static bool	box_compare_x(t_obj a, t_obj b)
{
	return (box_compare(a, b, X));
}

static bool	box_compare_y(t_obj a, t_obj b)
{
	return (box_compare(a, b, Y));
}

static bool	box_compare_z(t_obj a, t_obj b)
{
	return (box_compare(a, b, Z));
}

void	init_box_compare(bool (*box_compare[])(t_obj, t_obj))
{
	box_compare[X] = box_compare_x;
	box_compare[Y] = box_compare_y;
	box_compare[Z] = box_compare_z;
}

// t_bvh_tree	*build_bvh_tree(t_obj node[2], t_rt *vars, int argc, bool (*func)(t_obj, t_obj))
t_bvh_tree	*build_bvh_tree(t_obj *obj, t_uint *seed, int argc, bool (*func[3])(t_obj, t_obj))
{
	int			mid;
	int			axis;
	t_bvh_tree	*bvh;
	t_interval	box[2][3];

	axis = rand_int(seed, 0, 2);
	// if (argc <= 0)
	// {
	// 	// bvh->left = NULL;
	// 	// bvh->right = NULL;
	// 	return (NULL);
	// }
	bvh = (t_bvh_tree *)malloc(sizeof(t_bvh_tree));
	if (argc == 1 || argc == 2)
	{
		// obj.type = OBJ;
		bvh->l_type = obj[0].type;
		bvh->left = &obj[0];
		if (argc == 1)
		{
			bvh->r_type = obj[0].type;
			bvh->right = bvh->left;
		}
		else
		{
			bvh->r_type = obj[1].type;
			bvh->right = &obj[1];
		}
	}
	else
	{
		// obj.type = BVH;
		merge_sort(obj, argc, func[axis]);
		bvh->l_type = BVH;
		bvh->r_type = BVH;
		mid = (argc / 2);
		/*debug*/printf("mid:%d %d\n", mid, argc-mid);
		debug_print_arr("obj", obj, 4);
		bvh->left = build_bvh_tree(obj, seed, mid, func);
		bvh->right = build_bvh_tree(&obj[mid], seed, argc - mid, func);
	}
	get_bbox(bvh->left, box[L]);	//box[L]=
	get_bbox(bvh->right, box[R]);	//box[R]=
	update_aabb_box(box[L], box[R], bvh->bbox);
	return (bvh);
}

// /* range[0] = start , range[1] = end */
void	init_bvh_node(t_rt *vars)
{
	bool (*box_compare[3])(t_obj, t_obj);
	init_box_compare(box_compare);
	vars->bvh = build_bvh_tree(\
vars->obj, &vars->seed, vars->obj_count, box_compare);
}
