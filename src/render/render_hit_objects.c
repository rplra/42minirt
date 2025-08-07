/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:54:15 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/07 18:03:26 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
bool	has_hit_sphere(t_rt *rt, int index, t_interval ray_range, t_ray ray)
{
	float		n[3];
	float		t;
	float		discriminant;
	t_vec3		ray_to_center;

	// /*debug*/printf("has_hit ent:%d\n", index);
	/* ************* get discriminant ************* */
	// if (rt->obj[index].b_rotate == 1)
		// ray = transform_ray(rt->obj[index], ray);

	ray_to_center = subtract_vec(rt->obj[index].sph.pos, ray.orig);
	n[A] = scalar_product(ray.vector, ray.vector);
	n[B] = scalar_product(ray.vector, ray_to_center);
	n[C] = scalar_product(ray_to_center, ray_to_center) - \
(rt->obj[index].sph.rad * rt->obj[index].sph.rad);
	discriminant = ft_square(n[B]) - (n[A] * n[C]);
	if (discriminant < 0)
		return (0);

	/* ****************** get t ****************** */
	t = (n[B] - sqrt(discriminant)) / n[A];
	/* *********** if t intersects obj *********** */
	if (t <= ray_range.min || t >= ray_range.max)
	{
		t = (n[B] + sqrt(discriminant)) / n[A];
		if (t <= ray_range.min || t >= ray_range.max)
			return (0);
	}
	// /*debug*/printf("has_hit_sphere:%f %f\n", t, discriminant);
	update_hit_rec(rt, index, ray, t);
	return (1);
}

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
