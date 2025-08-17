/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit_pl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:29:51 by hsim              #+#    #+#             */
/*   Updated: 2025/08/17 15:37:12 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * child function in t_intersects_plane
 * checks if alpha & beta (barycentric coords) is within certain range
 * 
 * flag decides which shape it'll render
 * flag 0 = render quadrilaterals
 * flag 1 = render triangles
 * flag 2 = render ellipse (for cylinder cap only)
 * 
 * brief: checks if intersection point's coords are within the visible part of the plane
 * else, the ray hit infinite part of the plane which we dont want to care
 */
bool	within_plane_range(float alpha, float beta, int flag)
{
	if (flag == 0) 
		return ((alpha >= -0.5 && alpha <= 0.5) && (beta >= -0.5 && beta <= 0.5));
	else if (flag == 1)
		return (alpha > 0 && beta > 0 && (alpha + beta < 1));
	else if (flag == 2)
		return (ft_square(alpha) + ft_square(beta) <= ft_square(0.5));
	return (0);
}

/*
 * child function in has_hit_plane
 * checks if hit point, t is within surface of plane/quad
 * ensures only hits within finite surface is valid
 * 
 * Formula:
 * alpha = w . (p x v)
 * beta  = w . (u x p)
 * note: i = index
 * 
 * Formula Reference:
 * https://raytracing.github.io/books/RayTracingTheNextWeek.html
 * #quadrilaterals/derivingtheplanarcoordinates
 */
static bool	t_intersects_plane(t_rt *rt, int i, t_ray ray, float t)
{
	t_vec3	intersect;
	float	alpha;
	float	beta;

	// pt = o + t*d, then pt - C
	/* ******************* for quads only & triangles ******************* */
	intersect = add_vec(ray.orig, mult_vec_scalar(ray.vector, t));
	intersect = subtract_vec(intersect, rt->obj[i].plane.pos);
	
	/* ******** for ellipse, need to shift from corner to center ******** */
	// t_vec3	center = add_vec(add_vec(rt->obj[i].plane.pos, div_vec_scalar(rt->obj[i].plane.coord[Y],2)), div_vec_scalar(rt->obj[i].plane.coord[X], 2));
	// intersect = subtract_vec(intersect, center); //default=corner, if ellipse=center 

	/* ******************* alpha beta calculation ********************** */
	alpha = scalar_product(rt->obj[i].plane.w, \
cross_product(intersect, rt->obj[i].plane.coord[Y]));
	beta = scalar_product(rt->obj[i].plane.w, \
cross_product(rt->obj[i].plane.coord[X], intersect));
	// /*debug*/printf("has_hit_plane:%f %f\n", alpha, beta);
	if (!within_plane_range(alpha, beta, 0))
		return (0);

	/* ******************* optional if no texture ********************** */
	// rt->hit.coord[X] = alpha;
	// rt->hit.coord[Y] = beta;
	return (1);
}

/*
 * gets t(hit point) value and check if it is within plane surface
 * D = D in plane formula ABCD=0, D=dot(plane.corner, norm)
 * d = d in (P= ray_origin + t*d)
 * 
 * Formula:
 * t = D - dot(n, P) / dot(n, d)
 * 
 * denom: dot prod btw plane's normal and ray's direction (if near 0, ray is parallel)
 * 1. get denom > plane's norm > distance from ray's origin to hit point
 * 2. check if hit point is within ray range 
 * 3. check if hit point is within finite bounds
 */

bool	has_hit_plane(t_rt *rt, int index, t_interval ray_range, t_ray ray)
{
	float	denom;
	float	dot_np;
	float	t;

	// transform frm world space to obj space
	if (rt->obj[index].b_rotate == 1)
		ray = transform_ray(rt->obj[index], ray);

	denom = scalar_product(rt->obj[index].plane.normal, ray.vector);
	if (fabs(denom) < EPSILON) //if ray parallel to plane
		return (0);
	dot_np = scalar_product(rt->obj[index].plane.normal, ray.orig);
	t = (rt->obj[index].plane.d - dot_np) / denom;
	// /*debug*/printf("pl_d: %d %f\n", index, rt->obj[index].plane.d);
	// /*debug*/printf("has_hit_pl: t: %f, ray: %f~%f\n", t, ray_range.min, ray_range.max);
	if (t < ray_range.min || t > ray_range.max)
		return (0);
	if (!t_intersects_plane(rt, index, ray, t))
		return (0);
	update_hit_rec(rt, index, ray, t);
	return (1);
}
