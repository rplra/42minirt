/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hit_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:54:15 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/14 21:34:12 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * child function in hit
 * calls respective has_hit function depending on object type
 */
// init func pointer arrays
void	init_hit_func(bool (*has_hit[])())
{
	has_hit[PLANE] = has_hit_plane;
	has_hit[SPHERE] = has_hit_sphere;
	has_hit[CYLINDER] = has_hit_cylinder;
}

bool	has_hit_cylinder(t_obj obj, t_interval ray_range, t_ray ray)
{
	t_vec3	diff;
	float	denom;
	float	t;

	denom = scalar_product(ray.vector, obj.plane.normal);
	if (denom > -EPSILON && denom < EPSILON)
		return (-1);
	diff = subtract_vec(obj.plane.pos, ray.orig);
	t = scalar_product(diff, obj.plane.normal) / denom;
	if (t < ray_range.min || t > ray_range.max)
		return (-1);
	return (t);

	// (void) obj;
	// (void) ray;
	// (void) ray_range;

	// return (0);
}

/* child function in has_hit_sphere, records details of the hitted obj */
// updates the hit structure on details where ray hit
void	update_hit_rec(t_rt *rt, int index, t_ray ray, float t)
{
	t_vec3 (*get_surf_norm[3])(t_ray, t_obj, float);

	init_surf_norm(get_surf_norm);
	// get surface normal
	rt->hit.surf_norm = get_surf_norm[rt->obj[index].type](ray, rt->obj[index], t);	//if t>0
	// hit point
	rt->hit.at = add_vec(ray.orig, mult_vec_scalar(ray.vector, t));					//if t>0
	// which object was hit
	// rt->hit.obj = &rt->obj[index];
	rt->hit.index = index;
	// distance
	rt->hit.t = t;
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
// checks if ray intersects with sphere
bool	has_hit_sphere(t_rt *rt, int index, t_interval ray_range, t_ray ray)
{
	float		n[3];
	float		t;
	float		discriminant;
	t_vec3		ray_to_center;

	// /*debug*/printf("has_hit ent:%d\n", index);
	/* ************* get discriminant ************* */
	ray_to_center = subtract_vec(rt->obj[index].sph.pos, ray.orig);
	n[A] = scalar_product(ray.vector, ray.vector);
	n[B] = scalar_product(ray.vector, ray_to_center);
	n[C] = scalar_product(ray_to_center, ray_to_center) - \
(rt->obj[index].sph.rad * rt->obj[index].sph.rad);
	discriminant = (n[B] * n[B]) - (n[A] * n[C]);
	if (discriminant < 0.001f)
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
	/*debug*/printf("has_hit_sphere:%f %f\n", t, discriminant);

	update_hit_rec(rt, index, ray, t);
	return (1);
}

/*
 * child function in t_intersects_plane
 * checks if alpha & beta is within certain range
 * 
 * flag decides which shape it'll render
 * flag 0 = render quadrilaterals
 * flag 1 = render triangles
 */
static bool	within_range(float alpha, float beta, int flag)
{
	if (flag == 0)
		return ((alpha >= 0 && alpha <= 1) && (beta >= 0 && beta <= 1));
	else if (flag == 1)
		return (alpha > 0 && beta > 0 && (alpha + beta < 1));
	return (0);
}

/*
 * child function in has_hit_plane
 * checks if hit point, t is within surface of plane/quad
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

	intersect = add_vec(ray.orig, mult_vec_scalar(ray.vector, t));
	intersect = subtract_vec(intersect, rt->obj[i].plane.pos);
	alpha = scalar_product(rt->obj[i].plane.w, \
cross_product(intersect, rt->obj[i].plane.coord[Y]));
	beta = scalar_product(rt->obj[i].plane.w, \
cross_product(rt->obj[i].plane.coord[X], intersect));
	/*debug*/printf("has_hit_plane:%f %f\n", alpha, beta);
	if (!within_range(alpha, beta, 0))
		return (0);
	rt->hit.coord[X] = alpha;
	rt->hit.coord[Y] = beta;
	return (1);
}

/*
 * gets t(hit point) value and check if it is within plane surface
 * D = D in plane formula ABCD=0
 * d = d in (P= origin + t*d)
 * 
 * Formula:
 * t = D - dot(n, P) / dot(n, d)
 */
bool	has_hit_plane(t_rt *rt, int index, t_interval ray_range, t_ray ray)
{
	float	denom;
	float	dot_np;
	float	t;

	denom = scalar_product(rt->obj[index].plane.normal, ray.vector);
	if (fabs(denom) < EPSILON)
		return (0);
	dot_np = scalar_product(rt->obj[index].plane.normal, ray.orig);
	t = (rt->obj[index].plane.d - dot_np) / denom;
	/*debug*/printf("has_hit_pl: t: %f, ray: %f~%f\n", t, ray_range.min, ray_range.max);
	if (t < ray_range.min || t > ray_range.max)
		return (0);
	if (!t_intersects_plane(rt, index, ray, t))
		return (0);
	update_hit_rec(rt, index, ray, t);
	return (1);
}

