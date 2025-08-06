/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit_objects3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:16:30 by hsim              #+#    #+#             */
/*   Updated: 2025/08/06 15:48:23 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//static
/*
 * ( x/pointA )sq + ( y/pointB )sq = r sq
 */
bool	t_intersects_cap(t_cylinder cyl, int id, t_ray ray, float t)
{
	float	alpha;
	float	beta;
	t_vec3	intersect;
	t_vec3	axis_height;

/* ********************************************************** */
	// p= o +t*d
	intersect = add_vec(ray.orig, mult_vec_scalar(ray.vector, t));

	axis_height = mult_vec_scalar(cyl.axis, cyl.height/2);
	if (id == 1) //id=top_cap
		intersect = subtract_vec(intersect, add_vec(cyl.pos, axis_height)); // center or corner?
	else if (id == 0) //id=bottom_cap
		intersect = subtract_vec(intersect, subtract_vec(cyl.pos, axis_height));

	alpha = scalar_product(cyl.w, \
cross_product(intersect, (cyl.coord[Y])));
	beta = scalar_product(cyl.w, \
cross_product((cyl.coord[X]), intersect));

	if (!within_plane_range(alpha, beta, 2))
		return (0);
	return (1);
}

int	smallest_t(float t_cap[2])
{
	if (t_cap[0] < t_cap[1])
		return (0);
	return (1);
}

//static
int	closest_t(t_interval ray_range, float t_cap[2])
{
	if ((t_cap[0] < ray_range.min || t_cap[0] > ray_range.max) && \
(t_cap[1] < ray_range.min || t_cap[1] > ray_range.max))
	return (-1); //both invalid,return error

	else if (t_cap[0] < ray_range.min || t_cap[0] > ray_range.max)
		return (1);
	else if (t_cap[1] < ray_range.min || t_cap[1] > ray_range.max)
		return (0);
	else if (t_cap[0] < t_cap[1]) //both valid
		return (0);
	return (1);
}

//static
int	t_in_cap_range(t_cylinder cyl, t_interval ray_range, t_ray ray, float tmp_cap[2])
{
	int flag[2];

	flag[0] = t_intersects_cap(cyl, 0, ray, tmp_cap[0]);
	flag[1] = t_intersects_cap(cyl, 1, ray, tmp_cap[1]);

	if (!flag[0] && !flag[1])
		return (-1);
	if (flag[0] && flag[1])
		return (closest_t(ray_range, tmp_cap));
	if (flag[0] && tmp_cap[0] >= ray_range.min && tmp_cap[0] <= ray_range.max)
		return (0);
	if (flag[1] && tmp_cap[1] >= ray_range.min && tmp_cap[1] <= ray_range.max)
		return (1);
	return (-1);
}

/*
 * plane formula:
 * t = dot((C-O), N) / dot(d, N)
 * 
 * C is cyl_center, N is cyl_axis or cyl_normal
 * O is ray_origin, d is d in (P=(o+t*d))
 * 
 * cyl.d = dot(cyl_center, cyl_axis)
 * 
 * Reference:
 * https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm
 * Raytracing the Next Week
 * 
 */
float	has_hit_cap(t_rt *rt, int i, t_interval ray_range, t_ray ray)
{
	float	denom;
	float	dot_np;
	float	t_cap;
	float	tmp_cap[2];
	int		id;

	//should we do both axises, +1 & -1
	denom = scalar_product(rt->obj[i].cyl.axis, ray.vector);
	if (fabs(denom) < EPSILON)
		return (-1);
	dot_np = scalar_product(rt->obj[i].cyl.axis, ray.orig);
	tmp_cap[0] = (rt->obj[i].cyl.d[0] - dot_np) / denom; //might need to flip axis
	tmp_cap[1] = (rt->obj[i].cyl.d[1] - dot_np) / denom;

	// take the smallest
	// id = closest_t(ray_range, tmp_cap);
	id = smallest_t(tmp_cap);
	// /*debug*/printf("hit_cap: %d | %f < %f\n", id, tmp_cap[0], tmp_cap[1]);
	// id = t_in_cap_range(rt->obj[i].cyl, ray_range, ray, tmp_cap);
	// if (id == -1)
		// return (-1);
	// return (tmp_cap[id]);
	
	/* ************************************************************************** */
	t_cap = tmp_cap[id];
	if (t_cap < ray_range.min || t_cap > ray_range.max)
		return (-1);
	if (!t_intersects_cap(rt->obj[i].cyl, id, ray, t_cap))
		return (-1);
	return (t_cap);
}

/*
 * child function in check_hit_body
 * returns cyl_height considering its axis
 * using dot(pos, axis)*axis to mask the correct axis value
 * eg if axis=(0,1,0), cyl_axis_pos returns y value in cyl position
 * 
 * eg. if axis=(0,1,0) (y-axis), will be
 * cyl_height.max = cyl.pos.y + (cyl.axis.y * cyl.height / 2)
 * cyl_height.min = cyl.pos.y - (cyl.axis.y * cyl.height / 2)
 */
t_interval	get_cyl_axis_height(t_cylinder cyl)
{
	t_vec3		cyl_axis_pos;
	t_vec3		cyl_axis_height;
	t_interval	cyl_height;

	cyl_axis_pos = mult_vec_scalar(cyl.axis, scalar_product(cyl.pos, cyl.axis));
	cyl_axis_height = mult_vec_scalar(cyl.axis, cyl.height / 2);
	cyl_height.min = scalar_product(cyl.axis, subtract_vec(cyl_axis_pos, cyl_axis_height));
	cyl_height.max = scalar_product(cyl.axis, add_vec(cyl_axis_pos, cyl_axis_height));

	return (cyl_height);
}

/*
 * child function in check_hit_body
 * returns point on surface correspondiing to the cyl_axis
 * eg. if cyl_axis=(0,1,0) , point_on_surf=(3,2,1) returns 2 (value of y)
 */
void	get_point_on_surf(t_cylinder cyl, t_ray ray, float t[2], float res[2])
{
	t_vec3		pt_ray[2];

	pt_ray[0] = add_vec(ray.orig, mult_vec_scalar(ray.vector, t[0]));
	pt_ray[1] = add_vec(ray.orig, mult_vec_scalar(ray.vector, t[1]));
	res[0] = scalar_product(cyl.axis, pt_ray[0]);
	res[1] = scalar_product(cyl.axis, pt_ray[1]);
}