/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:32:00 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/07 17:16:42 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "../lib/quaternion/ft_vector.h" 

typedef unsigned char	t_uchar;
typedef unsigned int	t_uint;
typedef t_vec3			t_colour;

# define r	x
# define g	y
# define b	z

// //to change to t_vec3
// typedef struct	s_vector
// {
// 	float		x;
// 	float		y;
// 	float		z;
// }				t_vec3;

// typedef struct s_colour
// {
// 	float		r;
// 	float		g;
// 	float		b;		
// }				t_colour;

typedef enum e_material_type
{
	DIFFUSE,
	METAL,
	// DIELEC
	// BUBBLE
}				t_material_type;

typedef struct s_material
{
	t_colour	albedo;				// obj's base colour
	float		ambient;			// ambient reflectance
	float		specular;			// specular intensity (PHONG)
	float		shininess;			// highlight sharpness (PHONG)
	float		reflect;			// mirror reflectivity (ray bounce)
	float		refract;			// transparency (glass-like)
	float		refractive_index;	// index of refraction (for Snell's law) 
	t_uchar		type;				// diffuse / metal / dielec? / bubble?
}				t_material;

typedef struct s_ambient
{
	float		intensity;
	t_colour	colour;
}				t_ambient;

typedef struct s_camera
{
	t_vec3		pos;
	t_vec3		vup;				//camera orientation
	float		vfov;				//vertical fov (need change to hfov)

	t_vec3		lookat;				//camera pointing to				
	float		focus_dist;
	float		defoc_ang;			//blur angle
	t_vec3		defoc_disk[2];
	int			sample_per_pixel;
	t_uchar		ray_bounce;			//how many times a ray should bounce
}				t_camera;

typedef struct s_light
{
	t_vec3		pos;
	float		brightness;
	t_colour	colour;
}				t_light;

typedef struct s_sphere
{
	t_vec3		pos;
	float		rad;
}				t_sphere;

typedef struct s_plane
{
	t_vec3		pos;
	t_vec3		normal;
}				t_plane;

typedef struct s_cylinder
{
	t_vec3		pos;
	t_vec3		axis;
	float		rad;
	float		height;
}				t_cylinder;

// tag / labelling of objects
typedef enum	e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
}				t_obj_type;

// union of shapes, stores one of several shapes, one at a time
// memory is allocated based on the largest one
// typedef union u_obj
// {
// 	t_sphere	sph;
// 	t_plane		plane;
// 	t_cylinder	cyl;
// }				t_obj_union;

// the core object structure
// !!refactor to hsim's t_obj
typedef struct s_obj
{
	t_obj_type	type;				// tells what type of obj
	union							// stores the actual shape of data 
	{
		t_sphere	sph;
		t_plane		plane;
		t_cylinder	cyl;
	};
	// t_colour	colour;				// obj's colour, removed since mat has albedo
	t_material	material;			// rendering data
}				t_obj;


// typedef struct s_scene
// {
// 	t_ambient	ambient;
// 	t_camera	camera;
// 	t_light		light;
// 	t_object	*objects;
// 	size_t		obj_count;
// }				t_scene;

#endif
