/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:12:29 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/19 19:59:19 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*  
 * 1. gets the direction of reflected ray using mat's properties
 * 2. recursively calls ray_color col until bounce exhausted
 * 3. scales reflected col by mat's reflectivity
*/
static t_col	handle_metal(t_rt *rt, t_ray *ray, t_hit *point, t_uint *seed)
{
	t_mat	*mat;
	t_ray	bounce;
	t_col	reflected_light;
	
	mat = &point->obj->material;
	bounce.orig = point->at;
	bounce.vector = mat_metal(ray->vector, point->surf_norm, mat->fuzz, seed);
	reflected_light = ray_color(rt, bounce, rt->camera.ray_bounce - 1, seed);
	return (mult_vec_scalar(reflected_light, mat->reflect));
}

/*  
 * 1. gets new ray direction via Lambertian scattering
 * 2. recursively calls ray_color col until bounce exhausted
 * 3. multiplies col result by mat's albedo
*/
static t_col	handle_diffuse(t_rt *rt, t_hit *point, t_uint *seed)
{
	t_mat	*mat;
	t_ray	bounce;
	t_col	indirect_light;

	mat = &point->obj->material;
	bounce.orig = point->at;
	bounce.vector = mat_lambertian(point->surf_norm, seed);
	indirect_light = ray_color(rt, bounce, rt->camera.ray_bounce - 1, seed);
	return (mult_vec(indirect_light, mat->albedo));
}

static t_col	handle_material(t_rt *rt, t_ray *ray, t_hit *point, t_uint *seed)
{
	if (point->obj->material.type == METAL)
		return (handle_metal(rt, ray, point, seed));
	else if (point->obj->material.type == DIFFUSE)
		return (handle_diffuse(rt, point, seed));
	else
		return (new_vec3(0, 0, 0));
}

/* 
 * brief: gets the total colour of direct light and indirect light
 * 1. check bounce count > if no more then return black
 * 2. check for hit > if no hit > return bg colour
 * 3. if hit > get ambient col at hit point first
 * 4. check if first bounce > get direct light
 * 5. for the rest, add indirect light contribution from material
 * recursion = global illumination
 */
t_vec3	ray_color(t_rt *rt, t_ray ray, t_uchar ray_bounce, t_uint *seed)
{
	t_obj	*obj_hit;
	t_hit	point;
	t_col	colour;

	if (ray_bounce <= 0)
		return (new_vec3(0, 0, 0));
	obj_hit = hit(rt, new_interval(0.001f, 2147483647.0), ray);
	if (obj_hit == NULL)
		return (bg_color(*rt, ray));
	point = rt->hit;
	if (point.obj == NULL)
		return (new_vec3(0, 0, 0));
	colour = ambient(&point, rt->ambient);
	if (ray_bounce == rt->camera.ray_bounce)
		colour = add_vec(colour, sample_direct_light(rt, &point, seed));
	if (ray_bounce > 0)
		colour = add_vec(colour, handle_material(rt, &ray, &point, seed));
	// /*debug*/printf("final col: (%f, %f, %f)\n", colour.x, colour.y, colour.z);
	return (colour);
}

// /*
//  * ray_bounce is the recursion depth; how many times we want it to bounce
//  * seed for soft shadows (lambertian - monte carlo)
//  * find closest hit within range 
//  * if hit > get hit details > get ambient on hit point
//  */
// t_vec3	ray_color(t_rt *rt, t_ray ray, t_uchar ray_bounce, t_uint *seed)
// {
// 	t_obj	*obj_hit;
// 	t_hit	point;
// 	t_col	colour;

// 	if (ray_bounce <= 0)
// 		return (new_vec3(0, 0, 0));
// 	obj_hit = hit(rt, new_interval(0.001f, 2147483647.0), ray);
// 	if (obj_hit != NULL)
// 	{
// 		point = rt->hit;
// 		if (point.obj != NULL)
// 		{
// 			colour = ambient(&point, rt->ambient);
// 			if (ray_bounce == rt->camera.ray_bounce)
// 				colour = add_vec(colour, 
// 							sample_direct_light(rt, &point, seed));
// 			if (ray_bounce > 0)
// 				colour = add_vec(colour, 
// 							handle_material(rt, &ray, &point, seed));
// 		}
// 		return (colour);
// 	}
// 	return (bg_color(*rt, ray));
// }

// t_vec3	ray_color(t_rt *vars, t_ray ray, t_uchar ray_bounce, \
// t_uint *seed)
// {
// 	(void) ray;									// unused param
// 	(void) seed;								// unused param
// 	t_obj	*res;								// obj pointer
// 	t_ray		bounce;							// reflected ray
// 	// t_vec3		surf_norm;	

// 	// check bounce limit
// 	if (ray_bounce <= 0) 
// 		return (new_vec3(0, 0, 0)); // return black if no more bounces
// 	res = hit(vars, new_interval(0.001f, 2147483647.0), ray); //assigns surf_norm // check for hits
// 	//debug printf("res_7: %d\n", res);

// 	if (res != NULL) 							// if ray hits something
// 	{
// 		bounce.orig = vars->hit.at;				// set bounce origin to hit point
// 		if (res->material.type == METAL)		// check if metal
// 			bounce.vector = mat_metal(ray.vector, vars->hit.surf_norm, res->material.fuzz, seed); // metal reflection
// 		else if (res->material.type == DIFFUSE)	// check if diffuse
// 			bounce.vector = mat_lambertian(vars->hit.surf_norm, seed);	//diffuse scattering
// 		// /*debug*/t_colour final = mult_vec(ray_color(vars, bounce, ray_bounce - 1, seed), \
// res->material.albedo);
// 		// /*debug*/printf("RAY color: (%f, %f, %f)\n", final.r, final.g, final.b);
// 		// /*debug*/return (final);
// 		///*ORI*/return (mult_vec(ray_color(vars, bounce, ray_bounce - 1, seed), res->material.albedo));
// // 0.5)); //weaken its color reflectance by 50% everytime it bounce

// // mult_vec_scalar(vars.sph[state].mat.albedo, 0.8)));
// // 		return (new_vector3d(0.5*255*(surf_norm.x+1),
// // 0.5*255*(surf_norm.y+1),
// // 0.5*255*(surf_norm.z+1)));
// 	}
// 	// /*debug*/t_colour bg = bg_color(*vars, ray);
// 	// /*debug*/printf("BG color: (%f, %f, %f)\n", bg.r, bg.g, bg.b);
// 	// /*debug*/return (bg);
// 	///*ORI*/return (bg_color(*vars, ray));				// return background if no hit
// }

/*
 * child function in sample_pixels
 * checks if ray hits any object
 * defines what color the ray should be
 */
/* t_vec3	ray_color(t_rt *vars, t_ray ray, t_uchar ray_bounce, \
t_uint *seed)
{
	(void) ray;
	(void) seed;
	t_obj	*res;
	t_ray		bounce;
	// t_vec3		surf_norm;

	if (ray_bounce <= 0)
		return (new_vec3(0, 0, 0));
	res = hit(vars, new_interval(0.001f, 2147483647.0), ray); //assigns surf_norm
	// debugprintf("res_7: %d\n", res);

	if (res != NULL)
	{
		bounce.orig = vars->hit.at;
		if (res->material.type == METAL)
			bounce.vector = mat_metal(ray.vector, vars->hit.surf_norm, 0, seed);
		else if (res->material.type == DIFFUSE)
			bounce.vector = mat_lambertian(vars->hit.surf_norm, seed);
		return (mult_vec(ray_color(vars, bounce, ray_bounce - 1, seed), \
res->material.albedo));
// 0.5)); //weaken its color reflectance by 50% everytime it bounce

// mult_vec_scalar(vars.sph[state].mat.albedo, 0.8)));
// 		return (new_vector3d(0.5*255*(surf_norm.x+1),
// 0.5*255*(surf_norm.y+1),
// 0.5*255*(surf_norm.z+1)));
	}
	return (bg_color(*vars, ray));
} */
