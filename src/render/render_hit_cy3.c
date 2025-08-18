/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit_cy3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:41:54 by hsim              #+#    #+#             */
/*   Updated: 2025/08/17 17:20:09 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//static
/*
 * ( x/pointA )sq + ( y/pointB )sq = r sq
 * // intersect (p= o + t*d)
 * (id == 1) //id=top_cap, (id == 0) //id=bottom_cap
 */
bool	t_intersects_cap(t_cy cyl, int id, t_ray ray, float t)
{
	float	alpha;
	float	beta;
	t_vec3	intersect;

	intersect = add_vec(ray.orig, mult_vec_scalar(ray.vector, t));
	if (id == 1)
		intersect = subtract_vec(intersect,
				add_vec(cyl.pos, cyl.axis_height));
	else if (id == 0)
		intersect = subtract_vec(intersect,
				subtract_vec(cyl.pos, cyl.axis_height));
	alpha = scalar_product(cyl.w,
			cross_product(intersect, (cyl.coord[Y])));
	beta = scalar_product(cyl.w,
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
	if ((t_cap[0] < ray_range.min || t_cap[0] > ray_range.max)
		&& (t_cap[1] < ray_range.min || t_cap[1] > ray_range.max))
		return (-1);
	else if (t_cap[0] < ray_range.min || t_cap[0] > ray_range.max)
		return (1);
	else if (t_cap[1] < ray_range.min || t_cap[1] > ray_range.max)
		return (0);
	else if (t_cap[0] < t_cap[1])
		return (0);
	return (1);
}

//static
int	t_in_cap_range(t_cy cyl, t_interval ray_range, t_ray ray, float tmp_cap[2])
{
	int	flag[2];

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
 * https://hugi.scene.org/online/hugi24/coding%20graphics%
 * 	20chris%20dragan%20raytracing%20shapes.htm
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

	denom = scalar_product(rt->obj[i].cyl.axis, ray.vector);
	if (fabs(denom) < EPSILON)
		return (-1);
	dot_np = scalar_product(rt->obj[i].cyl.axis, ray.orig);
	tmp_cap[0] = (rt->obj[i].cyl.d[0] - dot_np) / denom;
	tmp_cap[1] = (rt->obj[i].cyl.d[1] - dot_np) / denom;
	id = smallest_t(tmp_cap);
	t_cap = tmp_cap[id];
	if (t_cap < ray_range.min || t_cap > ray_range.max)
		return (-1);
	if (!t_intersects_cap(rt->obj[i].cyl, id, ray, t_cap))
		return (-1);
	return (t_cap);
}

// float	has_hit_cap(t_rt *rt, int i, t_interval ray_range, t_ray ray)
// {
// 	float	denom;
// 	float	dot_np;
// 	float	t_cap;
// 	float	tmp_cap[2];
// 	int		id;

// 	//should we do both axises, +1 & -1
// 	denom = scalar_product(rt->obj[i].cyl.axis, ray.vector);
// 	if (fabs(denom) < EPSILON)
// 		return (-1);
// 	dot_np = scalar_product(rt->obj[i].cyl.axis, ray.orig);
// 	tmp_cap[0] = (rt->obj[i].cyl.d[0] - 
//		dot_np) / denom; //might need to flip axis
// 	tmp_cap[1] = (rt->obj[i].cyl.d[1] - dot_np) / denom;

// 	// take the smallest
// 	// id = closest_t(ray_range, tmp_cap);
// 	id = smallest_t(tmp_cap);
// 	// /*debug*/printf("hit_cap: %d | %f < %f\n", id, tmp_cap[0], tmp_cap[1]);
// 	// id = t_in_cap_range(rt->obj[i].cyl, ray_range, ray, tmp_cap);
// 	// if (id == -1)
// 		// return (-1);
// 	// return (tmp_cap[id]);
// 	/* ***************************************************************** */
// 	t_cap = tmp_cap[id];
// 	if (t_cap < ray_range.min || t_cap > ray_range.max)
// 		return (-1);
// 	if (!t_intersects_cap(rt->obj[i].cyl, id, ray, t_cap))
// 		return (-1);
// 	return (t_cap);
// }
