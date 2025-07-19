/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:18:16 by hsim              #+#    #+#             */
/*   Updated: 2025/07/13 13:06:19 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * 3d point along a vector ray
 * vec = origin + (t * direction)
 */
/* t_vec3	point_at(float t, t_ray ray)
{
	return (add_vec(ray.orig, mult_vec_scalar(ray.vector, t)));
} */

/*
 * calculates vector pt_ray -> sphere_center
 * if scalar_product of ray . surf_norm > 0, (means ray hits inner side)
 * reverse direction of surf_norm if so
 * returns a surf_norm in unit vector
 */
// intergrate get_normal in normal.c instead
// t_vec3	get_surf_norm_sph(t_ray ray, t_obj obj, float t)
// {
// 	t_vec3	pt_ray;
// 	t_vec3	surf_norm;

// 	// also known as set_face_normal
// 	pt_ray = add_vec(ray.orig, mult_vec_scalar(ray.vector, t)); // .at
// 	surf_norm = subtract_vec(pt_ray, obj.sph.pos);
// 	surf_norm = unit_vec3(surf_norm);
// 	// so, reverse surf_norm if so
// 	if (scalar_product(ray.vector, surf_norm) > 0) // pointing in same direction
// 		surf_norm = mult_vec_scalar(surf_norm, -1);
// 	return (surf_norm);
// }

// t_vec3	get_surf_norm_sph(t_ray ray, t_vec3 sph_center, float t)
// {
// 	t_vec3	pt_ray;
// 	t_vec3	surf_norm;

// 	// also known as set_face_normal
// 	pt_ray = add_vec(ray.orig, mult_vec_scalar(ray.vector, t)); // .at
// 	surf_norm = subtract_vec(pt_ray, sph_center);
// 	surf_norm = unit_vec3(surf_norm);
// 	// so, reverse surf_norm if so
// 	if (scalar_product(ray.vector, surf_norm) > 0) // pointing in same direction
// 		surf_norm = mult_vec_scalar(surf_norm, -1);
// 	return (surf_norm);
// }

/*
 * child function in mat_metal
 * adjusts fuzziness on metal surface
 * fuzz range from 0 to 1
 */
// adds randomness to a reflected ray direction to simulate rough / fuzzy metal surface
// matt surface
t_vec3	simulate_fuzz(t_vec3 bounce_ray, float fuzz, t_uint *seed)
{
	t_vec3	res;

	// check if fuzz value is too high, clamp it to max 1
	// 0 = mirror (perfect reflection), 1 = total rough (max randomness)
	if (fuzz > 1)
		fuzz = 1;

	// calc fuzzy reflection
	// bounce ray = perfect reflection direction
	// generate rand vec in any direction > scale rand by fuzz (how rough the surface is) > add scaled rand to reflection direction
	res = add_vec(bounce_ray, mult_vec_scalar(rand_unit_vec(seed), fuzz));
	return (res);
}

/*
 * child function in ray_color
 *
 * returns ray direction when surface material is metal/reflective
 * formula: in_ray - (2 * dot(in_ray, surf_norm) * surf_norm)
 * dot(...) is the magnitude, (scaling in_ray to surf_norm)
 * * surf_norm
 * = magnitude * dir
 */
// shiny surface / specular
// calcs reflection direction (like a mirror)
t_vec3	mat_metal(t_vec3 incoming_ray, t_vec3 surf_norm, \
float fuzz, t_uint *seed)
{
	t_vec3	bounce_ray;	// reflection direction
	float	magnitude;	// bounce strength (how much light reflecs off the surface)

	// calc dot product between incoming ray and surface normal
	// times 2 to have it bounce directly back (perfect reflection)
	magnitude = 2 * (scalar_product(incoming_ray, surf_norm));
	// scales surf_norm by calculated magnitude; creates a vec of incoming ray projection onto normal
	bounce_ray = mult_vec_scalar(surf_norm, magnitude);
	// subtract scaled normal from incoming ray; giving us reflection direction
	bounce_ray = unit_vec3(subtract_vec(incoming_ray, bounce_ray));
	// checks if surface has any roughness
	if (fuzz > 0.0)
		bounce_ray = simulate_fuzz(bounce_ray, fuzz, seed);
	// return final reflection direction
	return (bounce_ray);
}

/* 
 * child function in ray_color
 * returns ray direction when surface material is diffuse
 */
// diffuse (matt surface)
// diffuse light when scattered, rays are biased towards the surface normal
t_vec3	mat_lambertian(t_vec3 surf_norm, t_uint *seed)
{
	t_vec3	res;

	// takes surface normal, add random vector to it; creates scattered direction
	// result simulates how light bounces off randomly off a rough surface
	res = add_vec(surf_norm, rand_vec(seed)); //rand_unit_vec
	// check if result is close to zero (no direction)
	if (is_near_zero(res))
		res = surf_norm; // if res = 0, use surface normal as the direction
	return (res); // return final scattered direction
}

/*
 * child function in sample_pixels
 * returns background gradient color
 */
// normalize > get interpolation factor > return gradient of col based on t
// return gradient of mixed bg colour based on ray points (up / down / horizontally)
static t_vec3	bg_color(t_rt vars, t_ray ray)
{
	float	t;	// interpolation factor; between 0 and 1; how much bg colour to mix to create gradient

	// normalize ray > ensure direction has length 1
	// eg ray vector (0.7, 0.7, 0); up ad right direction; before norm = len_vec = 0.99
	// after norm = 0.7 / 0.99 = 0.707 (between -1 and +1)
	ray.vector.y /= len_vec3(ray.vector); //unit vector
	
	// calc interpolation factor
	// (0.707 + 1) / 2 = 1.707 / 2 = 0.854 (thus, 85.4% of the sky colour, 14.6% of ground color)
	t = (ray.vector.y + 1) / 2;

	// return gradient of mixed bg colour based on ray points (up / down / horizontally)
	return (lerp_rgb(vars.color_bg[1], vars.color_bg[0], t));
	// return (split_rgb(lerp_hsv(vars.color_bg[1], vars.color_bg[0], t)));
}

// Enhanced direct light sampling with area light simulation
/* t_colour	sample_direct_light_area(t_rt *vars, t_hit *hit, t_uint *seed)
{
    t_colour	total_light;
    int			samples;
    float		light_radius;
    
    total_light = new_vec3(0, 0, 0);
    samples = 32; // More samples for smoother shadows
    light_radius = 0.2; // Simulate area light
    
    for (int i = 0; i < samples; i++)
    {
        // Sample random point on area light
        t_vec3 light_pos = vars->light.pos;
        t_vec3 random_offset = mult_vec_scalar(rand_unit_vec(seed), light_radius);
        light_pos = add_vec(light_pos, random_offset);
        
        // Calculate lighting contribution
        t_vec3 light_dir = subtract_vec(light_pos, hit->at);
        float distance_to_light = len_vec3(light_dir);
        light_dir = unit_vec3(light_dir);
        
        // Shadow test
        t_ray shadow_ray;
        shadow_ray.orig = add_vec(hit->at, mult_vec_scalar(hit->surf_norm, EPSILON));
        shadow_ray.vector = light_dir;
        
        t_obj *shadow_obj = hit(vars, new_interval(EPSILON, distance_to_light), shadow_ray);
        
        if (!shadow_obj)
        {
            float diffuse_intensity = scalar_product(hit->surf_norm, light_dir);
            if (diffuse_intensity > 0)
            {
                // Attenuate light based on distance
                float attenuation = 1.0f / (1.0f + 0.1f * distance_to_light * distance_to_light);
                
                t_colour light_contribution = mult_vec(hit->obj->material.albedo, vars->light.colour);
                light_contribution = mult_vec_scalar(light_contribution, 
                    vars->light.brightness * diffuse_intensity * attenuation);
                total_light = add_vec(total_light, light_contribution);
            }
        }
    }
    
    return (div_vec_scalar(total_light, samples));
} */


// Add this function to sample direct light sources
t_colour	sample_direct_light(t_rt *vars, t_hit *hit_point, t_uint *seed)
{
    t_colour	total_light;
    t_vec3		light_dir;
    float		distance_to_light;
    t_ray		shadow_ray;
    t_obj		*shadow_obj;
    int			samples;
    
    total_light = new_vec3(0, 0, 0);
    samples = 16; // Number of light samples for soft shadows
    
    // Sample the point light multiple times for soft shadows
    for (int i = 0; i < samples; i++)
    {
        // Add some randomness to light position for soft shadows
        t_vec3		light_pos = vars->light.pos;
        t_vec3		random_offset = mult_vec_scalar(rand_unit_vec(seed), 0.1); // Light radius
        light_pos = add_vec(light_pos, random_offset);
        
        // Calculate direction to light
        light_dir = subtract_vec(light_pos, hit_point->at);
        distance_to_light = len_vec3(light_dir);
        light_dir = unit_vec3(light_dir);
        
        // Check if point is in shadow
        shadow_ray.orig = add_vec(hit_point->at, mult_vec_scalar(hit_point->surf_norm, EPSILON));
        shadow_ray.vector = light_dir;
        
        shadow_obj = hit(vars, new_interval(EPSILON, distance_to_light), shadow_ray);
        
        if (!shadow_obj) // Not in shadow
        {
            // Calculate diffuse contribution
            float diffuse_intensity = scalar_product(hit_point->surf_norm, light_dir);
            if (diffuse_intensity > 0)
            {
                t_colour light_contribution = mult_vec(hit_point->obj->material.albedo, vars->light.colour);
                light_contribution = mult_vec_scalar(light_contribution, 
                    vars->light.brightness * diffuse_intensity);
                total_light = add_vec(total_light, light_contribution);
            }
        }
    }
    
    // Average the samples
    total_light = div_vec_scalar(total_light, samples);
    return (total_light);
}

// Pure path tracing with ambient and direct light sampling
t_vec3	ray_color(t_rt *vars, t_ray ray, t_uchar ray_bounce, t_uint *seed)
{
    t_obj		*res;
    t_hit		point;
    t_colour	colour;
    t_ray		bounce;

    if (ray_bounce <= 0)
        return (new_vec3(0, 0, 0));
    
    res = hit(vars, new_interval(0.001f, 2147483647.0), ray);
    if (res != NULL)
    {
        point = vars->hit;
        
        // Always include ambient lighting (independent of ray bounces)
        colour = ambient(&point, vars->ambient);
        
        // For the first bounce, add direct light sampling for soft shadows
        if (ray_bounce == vars->camera.ray_bounce)
        {
            t_colour direct_light = sample_direct_light(vars, &point, seed);
            colour = add_vec(colour, direct_light);
        }
        
        // Path tracing for indirect lighting
        if (ray_bounce > 0)
        {
            bounce.orig = point.at;
            
            if (res->material.type == METAL)
            {
                // Specular reflection
                bounce.vector = mat_metal(ray.vector, point.surf_norm, res->material.fuzz, seed);
                t_colour reflected_light = ray_color(vars, bounce, ray_bounce - 1, seed);
                colour = add_vec(colour, mult_vec_scalar(reflected_light, res->material.reflect));
            }
            else if (res->material.type == DIFFUSE)
            {
                // Diffuse scattering (Monte Carlo)
                bounce.vector = mat_lambertian(point.surf_norm, seed);
                t_colour indirect_light = ray_color(vars, bounce, ray_bounce - 1, seed);
                
                // Multiply by albedo (this is the key for physically accurate rendering)
                colour = add_vec(colour, mult_vec(indirect_light, res->material.albedo));
            }
        }
        
        return (colour);
    }
    
    return (bg_color(*vars, ray));
}


// 4.0 - purely path tracing; soft shadows
// t_vec3	ray_color(t_rt *vars, t_ray ray, t_uchar ray_bounce, t_uint *seed)
// {
// 	t_obj		*res;
// 	t_hit		point;
// 	t_colour	colour;
// 	t_colour	reflected_col;
// 	t_ray		reflected_ray;

// 	if (ray_bounce <= 0)
// 		return (new_vec3(0, 0, 0));
// 	res = hit(vars, new_interval(0.001f, 2147483647.0), ray);
// 	if (res != NULL)
// 	{
// 		point = vars->hit;
// 		colour = light_col(&point, vars);
		
// 		if (res->material.type == METAL && ray_bounce > 0)
// 		{
// 			reflected_ray.orig = point.at;
// 			reflected_ray.vector = mat_metal(ray.vector, point.surf_norm, 0, seed);
// 			reflected_col = ray_color(vars, reflected_ray, ray_bounce - 1, seed);
// 			colour = add_vec(mult_vec_scalar(colour, 0.7f),
// 				mult_vec_scalar(reflected_col, 0.3f));
// 		}
// 		else if (res->material.type == DIFFUSE && ray_bounce > 0)
// 		{
// 			// Enhanced path tracing for soft shadows
// 			reflected_ray.orig = point.at;
// 			reflected_ray.vector = mat_lambertian(point.surf_norm, seed);
// 			reflected_col = ray_color(vars, reflected_ray, ray_bounce - 1, seed);
			
// 			// Use more path tracing for better soft shadows
// 			colour = add_vec(mult_vec_scalar(colour, 0.6f),
// 				mult_vec_scalar(mult_vec(reflected_col, res->material.albedo), 0.4f));
// 		}
// 		return (colour);
// 	}
// 	return (bg_color(*vars, ray));
// }

// 3.0 - hybrid, lighting approach, better soft shadows
/* t_vec3	ray_color(t_rt *vars, t_ray ray, t_uchar ray_bounce, t_uint *seed)
{
	t_obj		*res;
	t_hit		point;
	t_colour	colour;
	t_ray		bounce;

	if (ray_bounce <= 0)
		return (new_vec3(0, 0, 0));
	res = hit(vars, new_interval(0.001f, 2147483647.0), ray);
	if (res != NULL)
	{
		point = vars->hit;
		
		// For the first bounce, use direct lighting
		if (ray_bounce == vars->camera.ray_bounce)
		{
			colour = light_col(&point, vars);
		}
		else
		{
			// For subsequent bounces, use pure path tracing
			bounce.orig = point.at;
			if (res->material.type == METAL)
				bounce.vector = mat_metal(ray.vector, point.surf_norm, 0, seed);
			else if (res->material.type == DIFFUSE)
				bounce.vector = mat_lambertian(point.surf_norm, seed);
			
			// This is the key: pure path tracing like the commented version
			colour = mult_vec(ray_color(vars, bounce, ray_bounce - 1, seed), 
				res->material.albedo);
			return (colour);
		}
		
		// For metals, add reflection
		if (res->material.type == METAL && ray_bounce > 0)
		{
			bounce.orig = point.at;
			bounce.vector = mat_metal(ray.vector, point.surf_norm, 0, seed);
			t_colour reflected_col = ray_color(vars, bounce, ray_bounce - 1, seed);
			colour = add_vec(mult_vec_scalar(colour, 0.7f),
				mult_vec_scalar(reflected_col, 0.3f));
		}
		
		return (colour);
	}
	return (bg_color(*vars, ray));
} */

// 2.0 - pure path tracing
/* t_vec3	ray_color(t_rt *vars, t_ray ray, t_uchar ray_bounce, t_uint *seed)
{
	t_obj		*res;
	t_hit		point;
	t_colour	colour;
	t_ray		bounce;

	if (ray_bounce <= 0)
		return (new_vec3(0, 0, 0));
	res = hit(vars, new_interval(0.001f, 2147483647.0), ray);
	if (res != NULL)
	{
		point = vars->hit;
		
		// For the first bounce, use direct lighting
		if (ray_bounce == vars->camera.ray_bounce)
		{
			colour = light_col(&point, vars);
		}
		else
		{
			// For subsequent bounces, use pure path tracing
			bounce.orig = point.at;
			if (res->material.type == METAL)
				bounce.vector = mat_metal(ray.vector, point.surf_norm, 0, seed);
			else if (res->material.type == DIFFUSE)
				bounce.vector = mat_lambertian(point.surf_norm, seed);
			
			// This is the key: pure path tracing like the commented version
			colour = mult_vec(ray_color(vars, bounce, ray_bounce - 1, seed), 
				res->material.albedo);
			return (colour);
		}
		
		// For metals, add reflection
		if (res->material.type == METAL && ray_bounce > 0)
		{
			bounce.orig = point.at;
			bounce.vector = mat_metal(ray.vector, point.surf_norm, 0, seed);
			t_colour reflected_col = ray_color(vars, bounce, ray_bounce - 1, seed);
			colour = add_vec(mult_vec_scalar(colour, 0.7f),
				mult_vec_scalar(reflected_col, 0.3f));
		}
		
		return (colour);
	}
	return (bg_color(*vars, ray));
} */


// 1.0
/* t_vec3	ray_color(t_rt *vars, t_ray ray, t_uchar ray_bounce, \
t_uint *seed)
{
	t_obj		*res;
	t_hit		point;
	t_colour	colour;
	t_colour	reflected_col;
	t_ray		reflected_ray;

	if (ray_bounce <= 0)
		return (new_vec3(0, 0, 0));
	res = hit(vars, new_interval(0.001f, 2147483647.0), ray); //assigns surf_norm
	if (res != NULL)
	{
		point = vars->hit;
		colour = light_col(&point, vars);
		
		if (res->material.type == METAL && ray_bounce > 0)
		{
			reflected_ray.orig = point.at;
			reflected_ray.vector = mat_metal(ray.vector, point.surf_norm, 0, seed);
			reflected_col = ray_color(vars, reflected_ray, ray_bounce - 1, seed);
			colour = add_vec(mult_vec_scalar(colour, 0.7f),
				mult_vec_scalar(reflected_col, 0.3f));
		}
		else if (res->material.type == DIFFUSE && ray_bounce > 0)
		{
			// path tracing for diffuse materials to get soft shadows
			reflected_ray.orig = point.at;
			reflected_ray.vector = mat_lambertian(point.surf_norm, seed);
			reflected_col = ray_color(vars, reflected_ray, ray_bounce - 1, seed);
			// combine direct lighting with indirect lighting (path tracing)
			colour = add_vec(mult_vec_scalar(colour, 0.8f),
				mult_vec_scalar(mult_vec(reflected_col, res->material.albedo), 0.2f));
		}
		return (colour);
	}
	return (bg_color(*vars, ray));
} */

// 0.0
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
// 		return (mult_vec(ray_color(vars, bounce, ray_bounce - 1, seed), \
// res->material.albedo));
// // 0.5)); //weaken its color reflectance by 50% everytime it bounce

// // mult_vec_scalar(vars.sph[state].mat.albedo, 0.8)));
// // 		return (new_vector3d(0.5*255*(surf_norm.x+1),
// // 0.5*255*(surf_norm.y+1),
// // 0.5*255*(surf_norm.z+1)));
// 	}
// 	return (bg_color(*vars, ray));				// return background if no hit
// }


// superceded
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

// t_vector3d	ray_color_loop(t_vars vars, t_ray ray, unsigned int *seed)
// {
// 	int			k;
// 	float		t;
// 	t_ray		bounce;
// 	t_vector3d	surf_norm;
// 	t_vector3d	color;

// 	k = -1;
// 	bounce = ray;
// 	color = new_vector3d(1, 1, 1);

// 	t = (ray.vector.y + 1) / 2;
// 	t_vector3d sky = split_rgb(lerp_hsv(vars.color_bg[1], vars.color_bg[0], t));
// 	float factor = 1;
// 	color = sky;
// 	while (++k < vars.ray_bounce)
// 	{
// 		if (hit(vars, bounce, &surf_norm, &bounce.orig))
// 		{
// 			bounce.vector = rand_on_hemisphere(seed, surf_norm);
// 			factor /= 2;
// 		}
// 		else
// 			color = mult_vec_scalar(sky, factor);
// 	}
// 	return (color);
// }

// int	ray_color(t_vars vars, t_ray ray)
// {
// 	float		t;
// 	t_vector3d	pt_ray;
// 	// float		ratio = 1 / vars.sample_per_pixel;

// 	(void)	vars;

// 	// ray_norm = norm_vector3d(ray.vector);
// 	// if (has_hit_sphere(new_vector3d(0, 0, -1), radius, ray))
// 		// return (0xFF8080);

// 	if (hit(vars, 2147483647, &pt_ray))
// 		return (create_rgb(0.5*255*(pt_ray.x+1),
// 0.5*255*(pt_ray.y+1),
// 0.5*255*(pt_ray.z+1)));

// 	/* else render sky bg */
// 	// ray_norm = ray.vector;
// 	t = (ray.vector.y + 1) / 2;
// 	// /*debug*/printf("ray_color:t:%f ray.y:%f %f\n", t, ray.vector.y, ray_norm.y);
// 	return (lerp_hsv(vars.color_bg[1], vars.color_bg[0], t));
// }