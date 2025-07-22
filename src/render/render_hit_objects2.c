/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit_objects2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:47:34 by hsim              #+#    #+#             */
/*   Updated: 2025/07/22 12:21:19 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// bool	has_hit_cylinder(t_rt *rt, int index, t_interval ray_range, t_ray ray)
// {
// 	float	n[3];
// 	float	discriminant;
// 	float	t;

// 	n[A] = ft_square(ray.vector.x) + ft_square(ray.vector.z);
// 	if (n[A] < EPSILON)
// 		return (0);
// 	n[B] = (2 * ray.orig.x * ray.vector.x) + (2 * ray.orig.z * ray.vector.z);
// 	n[C] = ft_square(ray.orig.x) + ft_square(ray.orig.z) - 1; // 1 is radius sq
// 	discriminant = ft_square(n[B]) - (4 * n[A] * n[C]);
// 	if (discriminant < 0)
// 		return (0);
// 	/* *********** if t intersects obj *********** */
// 	t = (-n[B] - sqrt(discriminant)) / (2 * n[A]);
// 	if (t <= ray_range.min || t >= ray_range.max)
// 	{
// 		t = (-n[B] + sqrt(discriminant)) / (2 * n[A]);
// 		if (t <= ray_range.min || t >= ray_range.max)
// 			return (0);
// 	}
// 	/*debug*/printf("has_hit_cyl:af:: %f\n", t);
// 	// if (!t_intersects_cyl(rt, index, ray, t))
// 		// return (0);
// 	update_hit_rec(rt, index, ray, t);
// 	return (1);
// }

// int	check_cyl_cap(t_obj obj, t_ray ray, float t)
// int	check_cyl_cap(t_rt *rt, int i, t_ray ray, float t)
// {
// 	t_vec3	pt_ray;
// 	t_obj	obj;
// 	(void)	i;

// 	obj = *rt->obj;
// 	pt_ray = add_vec(ray.orig, mult_vec_scalar(ray.vector, t));	//P= O+t*d
// 	// pt_ray = subtract_vec(pt_ray, new_vec3());	//P= O+t*d
// 	pt_ray = new_vec3(pt_ray.x, 0, pt_ray.z);
// 	// pt_ray = unit_vec3(pt_ray);
// 	/*debug*/printf("check_cyl_cap: %f <= %f\n", scalar_product(pt_ray, pt_ray), ft_square(obj.cyl.rad));
// 	/*debug*/debug_print_vec("pt_ray", pt_ray);
// 	if (scalar_product(pt_ray, pt_ray) <= ft_square(obj.cyl.rad))
// 	{
// 		// if (t >= 0)
// 		/*debug*/printf("win! %f\n", t);
// 		// 	update_hit_rec(rt, i, ray, t);
// 		return (1);
// 	}
// 	return (0);
// 	// return (scalar_product(pt_ray, pt_ray) <= ft_square(obj.cyl.rad));
// }

// bool	hit_caps(t_rt *rt, int i, t_interval cyl_axis, t_ray ray)
// {
// 	float		t_cap[2];
// 	t_cylinder	cyl;
// 	bool		flag = 0;

// 	if (fabs(ray.vector.y) < EPSILON)
// 		return (0);
// 	cyl = rt->obj[i].cyl;

// 	// plane formula: 
// 	// t = dot((C-O), norm) / dot(ray_dir, norm) (norm y=1 here)
// 	t_cap[0] = (cyl_axis.min - ray.orig.y) / ray.vector.y; //bottom cap
// 	t_cap[1] = (cyl_axis.max - ray.orig.y) / ray.vector.y; //top cap

// 	//compare t[0], t[1] & hit.t, update the closest hit
// 	if (t_cap[0] < rt->hit.t)
// 		/*debug*/printf("t_cap[0] small! %f < %f\n", t_cap[0], rt->hit.t);
// 	if (t_cap[1] < rt->hit.t)
// 		/*debug*/printf("t_cap[1] small! %f < %f\n", t_cap[1], rt->hit.t);

// 	check_cyl_cap(rt, i, ray, t_cap[0]);
// 	check_cyl_cap(rt, i, ray, t_cap[1]);
// 	// if (!check_cyl_cap(rt, i, ray, t_cap[0]) && !check_cyl_cap(rt, i, ray, t_cap[1]))
// 		// return (0);

// 	// if (check_cyl_cap(rt->obj[i], ray, t_cap[0]) == 1)
// 	// {
// 		// /*debug*/printf("mew!\n");
// 	// 	// if (t_cap[0] < rt->hit.t)
// 		// if (t_cap[0] < rt->hit.t && t_cap[0] >= 0)

// 	//pt_ray check is in check_cyl_cap
// 	// if (!check_cyl_cap(rt, i, ray, t_cap[0]) && !check_cyl_cap(rt, i, ray, t_cap[1]))
// 		// return (0);
// 	// update_hit_rec(rt, i, ray, t_cap[0]);

// 		if (t_cap[0] >= 0)
// 		{
// 			flag = 1;
// 			// check_cyl_cap(rt, i, ray, t_cap[0]);
// 			// /*debug*/printf("hits_cyl_cap add bottom! %f <= %f\n", t_cap[0], rt->hit.t);
// 			update_hit_rec(rt, i, ray, t_cap[0]);
// 		}
// 	// }

// 	// if (check_cyl_cap(rt->obj[i], ray, t_cap[1]) == 1)
// 	// {
// 		// /*debug*/printf("mew2!\n");
// 	// 	// if (t_cap[1] < rt->hit.t)
// 		// if (t_cap[1] < rt->hit.t && t_cap[1] >= 0)
// 		if (t_cap[1] >= 0)
// 		{
// 			flag = 1;
// 			// check_cyl_cap(rt, i, ray, t_cap[1]);
// 			// /*debug*/printf("hits_cyl_cap add top! %f <= %f\n", t_cap[1], rt->hit.t);
// 			if (t_cap[1] < rt->hit.t)
// 				update_hit_rec(rt, i, ray, t_cap[1]);
// 		}
// 	// }
// 	// if (!check_cyl_cap(rt, i, ray, t_cap[0]) && !check_cyl_cap(rt, i, ray, t_cap[1]))
// 		// return (0);
// 	/*debug*/printf("%d:flag:%d, cyl_axis_min: %f %f\n", i, flag, cyl_axis.min,  cyl_axis.max);
// 	return (flag);
// }

// bool	t_intersects_cyl(t_rt *rt, int i, t_ray ray, float t[2])
// {
// 	t_vec3		pt_ray[2];
//     t_cylinder	cyl;
// 	t_interval	cyl_axis;

//     cyl = rt->obj[i].cyl;
// 	cyl_axis.min = cyl.pos.y - (cyl.axis.y * cyl.height / 2);
// 	cyl_axis.max = cyl.pos.y + (cyl.axis.y * cyl.height / 2);
// 	pt_ray[0] = add_vec(ray.orig, mult_vec_scalar(ray.vector, t[0]));
// 	pt_ray[1] = add_vec(ray.orig, mult_vec_scalar(ray.vector, t[1]));

// 	/* ************************************************************* */
// 	/*debug*/printf("cyl_axis: %f %f\n", cyl_axis.min, cyl_axis.max);
// 	if (pt_ray[0].y > cyl_axis.min && pt_ray[0].y < cyl_axis.max)
// 		/*debug*/printf("add t[0]! %f\n", t[0]);
// 	if (pt_ray[1].y > cyl_axis.min && pt_ray[1].y < cyl_axis.max)
// 		/*debug*/printf("add t[1]! %f\n", t[1]);
// 	/* ************************************************************* */

// 	//this decides where the cylinder truncates
// 	//hit cylinder body
// 	/********* if either one fall within range, return 1 *********/
// // 	if ((pt_ray[0].y > cyl_axis.min && pt_ray[0].y < cyl_axis.max) || \
// // (pt_ray[1].y > cyl_axis.min && pt_ray[1].y < cyl_axis.max))
// // 	return (1);

// 	/********* if both out of range, return 0 *********/
// 	// if ((pt_ray[0].y <= cyl_axis.min || pt_ray[0].y >= cyl_axis.max) && \
// // (pt_ray[1].y <= cyl_axis.min || pt_ray[1].y >= cyl_axis.max))
// 	// return (hit_caps(rt, i, cyl_axis, ray));


// 	//hit cylinder cap
// 	bool flag = 0;
// 	// /*debug*/printf("hut: %f %f hit: %f\n", t[0], t[1], rt->hit.t);
// 	// if ((pt_ray[0].y > cyl_axis.min && pt_ray[0].y < cyl_axis.max))// && t[0] >= 0 && t[0] <= rt->hit.t)
// 	// {
// 	// 	flag = 1;
// 	// 	if (t[0] > 0 && t[0] < rt->hit.t)
// 	// 		update_hit_rec(rt, i, ray, t[0]);
// 	// }
// 	// if ((pt_ray[1].y > cyl_axis.min && pt_ray[1].y < cyl_axis.max))// && t[1] >= 0 && t[1] < rt->hit.t)
// 	// {
// 	// 	flag = 1;
// 	// 	if (t[1] > 0 && t[1] < rt->hit.t)
// 	// 		update_hit_rec(rt, i, ray, t[1]);
// 	// }
// 	// check hit_cap
// 	// if (!flag)
// 		flag = hit_caps(rt, i, cyl_axis, ray);
// 	// else
// 		// hit_caps(rt, i, cyl_axis, ray);
// 	return (flag);
// }

/*
 * ( x/pointA )sq + ( y/pointB )sq = r sq
 */
static bool	t_intersects_cap(t_cylinder cyl, t_ray ray, float t)
{
	float	alpha;
	float	beta;
	t_vec3	intersect;

	intersect = add_vec(ray.orig, mult_vec_scalar(ray.vector, t));
/* ********************************************************** */
// render circle
// intersect = subtract_vec(intersect, rt->obj[i].cyl.pos); //center of cyl
// alpha = intersect.x / rt->obj[i].cyl.rad;
// beta = intersect.z / rt->obj[i].cyl.rad;
/* ********************************************************** */
intersect = subtract_vec(intersect, cyl.pos);
alpha = scalar_product(intersect, unit_vec3(cyl.coord[X])) / cyl.rad;
beta = scalar_product(intersect, unit_vec3(cyl.coord[Y])) / cyl.rad;

/*debug*/printf("has_hit_cap:%f %f\n", alpha, beta);
	/* ********************************************************** */
	if (!within_plane_range(alpha, beta, 2))
		return (0);
	// rt->hit.coord[X] = alpha;
	// rt->hit.coord[Y] = beta;
	return (1);
}

/*
 * plane formula:
 * t = dot((C-O), N) / dot(d, N)
 * 
 * C is cyl_center, N is cyl_axis or cyl_normal
 * O is ray_origin, d is d in (P=(o+t*d))
 * 
 * cyl.d = dot(cyl_center, cyl_axis)
 * Reference:
 * https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm
 * Raytracing the Next Week
 * 
 */
bool	check_hit_cap(t_rt *rt, int i, t_interval ray_range, t_ray ray, float t)
{
	float	denom;
	float	dot_np;
	float	t_cap;
	float	tmp_cap[2];
	// (void)	t;

	denom = scalar_product(rt->obj[i].cyl.axis, ray.vector);
	if (fabs(denom) < EPSILON)
		return (0);
	dot_np = scalar_product(rt->obj[i].cyl.axis, ray.orig);
	// *t_cap = (rt->obj[i].cyl.d[0] - dot_np) / denom;
	tmp_cap[0] = (rt->obj[i].cyl.d[0] - dot_np) / denom;
	tmp_cap[1] = (rt->obj[i].cyl.d[1] - dot_np) / denom;
	// take the smallest one
	if (tmp_cap[0] < tmp_cap[1])
		t_cap = tmp_cap[0];
	else
		t_cap = tmp_cap[1];
	// /*debug*/printf("has_hit_cap: t: %f, ray: %f~%f\n", t_cap, ray_range.min, ray_range.max);
	if (t_cap < ray_range.min || t_cap > ray_range.max)
		return (0);
	if (!t_intersects_cap(rt->obj[i].cyl, ray, t_cap))// || t_cap > t)
		return (0);
	// if (t_cap > t)
	// 	return (0);
	update_hit_rec(rt, i, ray, t_cap);
	/*debug*/printf("hit_cap %d: %f %f\n", i, t_cap, t);
	return (1);
}

// bool	check_hit_cap(t_rt *rt, int i, t_interval ray_range, t_ray ray, float *t_cap)
// {
// 	float	denom;
// 	float	dot_np;
// 	float	tmp_cap[2];

// 	denom = scalar_product(rt->obj[i].cyl.axis, ray.vector);
// 	if (fabs(denom) < EPSILON)
// 		return (0);
// 	dot_np = scalar_product(rt->obj[i].cyl.axis, ray.orig);
// 	// *t_cap = (rt->obj[i].cyl.d[0] - dot_np) / denom;
// 	tmp_cap[0] = (rt->obj[i].cyl.d[0] - dot_np) / denom;
// 	tmp_cap[1] = (rt->obj[i].cyl.d[1] - dot_np) / denom;
// 	// take the smallest one
// 	if (tmp_cap[0] < tmp_cap[1])
// 		*t_cap = tmp_cap[0];
// 	else
// 		*t_cap = tmp_cap[1];
// 	/*debug*/printf("has_hit_cap: t: %f, ray: %f~%f\n", *t_cap, ray_range.min, ray_range.max);
// 	if (*t_cap < ray_range.min || *t_cap > ray_range.max)
// 		return (0);
// 	if (!t_intersects_cap(rt->obj[i].cyl, ray, *t_cap)) // t_cap > t
// 		return (0);
// 	// if (t_cap > t)
// 	// return (0)
// 	// update_hit_rec();
// 	/*debug*/printf("rt_hit(cap): %f\n", *t_cap);
// 	return (1);
// }

bool	check_hit_body(t_rt *rt, int i, t_ray ray, float t[2])
{
	bool		flag;
	float		pt_hit[2];
	t_interval	cyl_height;

	cyl_height = get_cyl_axis_height(rt->obj[i].cyl);
	get_point_on_surf(rt->obj[i].cyl, ray, t, pt_hit);
	flag = 0;
	if (((pt_hit[0] > cyl_height.min && pt_hit[0] < cyl_height.max) || \
(pt_hit[1] > cyl_height.min && pt_hit[1] < cyl_height.max)))
	{
		update_hit_rec(rt, i, ray, t[0]);
		flag = 1;
	}
	return (flag);
}

/*
 * checks if hit point t, is within cyl_height_bounds
 * or checks if hit point t_cap, is within cyl_cap_bounds
 * if hits_cyl_cap, return (cyl_cap_hit)
 * else, return (cyl_body_hit)
 */
bool	t_intersects_cyl(t_rt *rt, int i, t_interval ray_range, t_ray ray, float t[2])
{
	(void)		ray_range;
	(void)		t;
	int			flag = 0;
	// float		t_cap = 0;
	// float		pt_hit[2];
	// t_interval	cyl_height;

	/* ************** check if t_caps lies within plane range (plane-ray formula) ************** */
	// flag = check_hit_cap(rt, i, ray_range, ray, t[0]);

	// if (!flag)
		flag = check_hit_body(rt, i, ray, t);
	// if (!flag)
		// flag = 0;
	/* *********************** long version *********************** */

		// cyl_height = get_cyl_axis_height(rt->obj[i].cyl);
		// get_point_on_surf(rt->obj[i].cyl, ray, t, pt_hit);

	// if (flag)
// 	if (flag && t_cap < t[0]) //,update_hit_rec
// 		update_hit_rec(rt, i, ray, t_cap);
// 	else
// 	{
// 		update_hit_rec(rt, i, ray, t[0]);
// 		if (((pt_hit[0] > cyl_height.min && pt_hit[0] < cyl_height.max) || \
// (pt_hit[1] > cyl_height.min && pt_hit[1] < cyl_height.max)))
// 	{
// 		flag = 1;
// 	}
// 	}
	// else
		// flag = 0;
	return (flag);
}


/*
 * checks if ray to point falls within the cylinder space
 * formula modifies from <Raytracing in One Weekend>, sphere intersection formula
 * just modified y to be assigned to 0
 * 
 * Reference:
 * https://raytracing.github.io/books/RayTracingInOneWeekend.html
 * #addingasphere/ray-sphereintersection
 */
bool	has_hit_cylinder(t_rt *rt, int index, t_interval ray_range, t_ray ray)
{
	(void)	ray_range;
	(void)	rt;
	(void)	index;
	(void)	ray;

	float	t[2];
	float	n[3];
	float	discriminant;
	t_vec3	ray_to_center;
	t_vec3	ray_dir;
	// t_vec3	ray_to_center2;
	// t_vec3	ray_dir2;
	t_vec3	highlighted_axis;

	// /*debug*/printf("has_hit ent:%d\n", index);
	/* ************* get discriminant ************* */
	ray_to_center = subtract_vec(rt->obj[index].cyl.pos, ray.orig); // C-O
	highlighted_axis = mult_vec_scalar(rt->obj[index].cyl.axis, scalar_product(ray_to_center, rt->obj[index].cyl.axis));
	ray_to_center = subtract_vec(ray_to_center, highlighted_axis); // C-O - ((C-0).V)*V
    ray_dir =  subtract_vec(ray.vector, mult_vec_scalar(rt->obj[index].cyl.axis, scalar_product(ray.vector, rt->obj[index].cyl.axis))); // d - (d.V)*V
	
	/* initial version */
	// ray_to_center = subtract_vec(rt->obj[index].cyl.pos, ray.orig); // C-O
    // ray_to_center = new_vec3(ray_to_center.x, 0, ray_to_center.z); //set y to 0
	// ray_dir = new_vec3(ray.vector.x, 0, ray.vector.z);

	// /*debug*/debug_print_vec("ray_dir", ray_dir);
	// /*debug*/debug_print_vec("ray_dir2", ray_dir2);

	n[A] = scalar_product(ray_dir, ray_dir);
	// if (n[A] < EPSILON)
		// /*debug*/printf("\na is 0!\n\n");
	// {
	// 	if (!intersect_caps(rt, index, ray))
	// 		return (0);
	// 	return (1);
	// }
	n[B] = scalar_product(ray_dir, ray_to_center);
	n[C] = scalar_product(ray_to_center, ray_to_center) - \
ft_square(rt->obj[index].cyl.rad);
	discriminant = ft_square(n[B]) - (n[A] * n[C]);
	if (discriminant < 0.001f)
		return (0);

	/* ****************** get t ****************** */
	t[0] = (n[B] - sqrt(discriminant)) / n[A];
	t[1] = (n[B] + sqrt(discriminant)) / n[A];

	/* *************** if t intersects obj ************** */
	if (t[0] <= ray_range.min || t[0] >= ray_range.max)
	{
		t[0] = (n[B] + sqrt(discriminant)) / n[A];
		if (t[0] <= ray_range.min || t[0] >= ray_range.max)
			return (0);
	}

	// if (!cyl_body)
	// return (0)
	// if (cyl_cap)
	// return (cyl_cap)
	// else
	// return (cyl_body)

	// /*debug*/printf("has_hit_cyl:%f %f\n", t[0], rt->hit.t);

	// /*debug*/printf("rt_hit(init): %f\n\n", rt->hit.t);
	/* ***********  truncate cylinder height  *********** */
    // if (!check_hit_cap(rt, index, ray_range, ray))
    if (!t_intersects_cyl(rt, index, ray_range, ray, t))
		return (0);
	// /*debug*/printf("rt_hit(fin): %f\n\n", rt->hit.t);
	return (1);
}
