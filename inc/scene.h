/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:32:00 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/24 10:30:27 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

typedef unsigned char	t_uchar;
typedef unsigned int	t_uint;

//to change to t_vec3
typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef struct	s_colour
{
	t_uint		r;
	t_uint		g;
	t_uint		b;		
}				t_colour;

typedef enum	e_material_type
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

typedef struct	s_ambient
{
	float		intensity;
	t_colour	colour;
}				t_ambient;

typedef struct s_camera
{
	t_vector	position;
	t_vector	orientation;
	uint		fov;
}				t_camera;

typedef struct s_light
{
	t_vector	position;
	float		brightness;
	t_colour	colour;
}				t_light;

typedef struct s_sphere
{
	t_vector	position;
	float		diameter;
}				t_sphere;

typedef struct s_plane
{
	t_vector	position;
	t_vector	normal;
}				t_plane;

typedef struct s_cylinder
{
	t_vector	position;
	t_vector	axis;
	float		diameter;
	float		height;
}				t_cylinder;

// tag / labelling of objects
typedef enum 	e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
}				t_obj_type;

// union of shapes, stores one of several shapes, one at a time
// memory is allocated based on the largest one
typedef union	u_obj
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}				t_obj_union;

// the core object structure
typedef	struct s_object
{
	t_obj_type	type; 		// tells what type of obj
	t_obj_union	obj;		// stores the actual shape of data
	t_colour	colour;		// object's colour
	t_material	material;	// rendering data
}				t_object;

typedef struct	s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_object	*objects;
	size_t		obj_count;
}				t_scene;

#endif
