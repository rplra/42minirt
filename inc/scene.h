/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:32:00 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/22 09:42:23 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "../lib/quaternion/ft_vector.h" 
# include "interval.h"
# include "transform.h"

typedef unsigned char	t_uchar;
typedef unsigned int	t_uint;
typedef t_vec3			t_col;

# define R	x
# define G	y
# define B	z

typedef enum e_mat_type
{
	DIFFUSE,
	METAL,
	LIGHT
}			t_mat_type;

typedef struct s_material
{
	t_col		albedo;				// obj's base colour
	float		ambient;			// ambient reflectance
	float		specular;			// specular intensity (PHONG)
	// float	shininess;			// highlight sharpness (PHONG)
	float		reflect;			// mirror reflectivity (ray bounce)
	// float	refract;			// transparency (glass-like)
	// float	refractive_index;	// index of refraction (for Snell's law) 
	float		fuzz;				// material fuzziness (only for metal)
	t_mat_type	type;				// diffuse / metal / dielec? / bubble?
}				t_mat;

typedef struct s_ambient
{
	float		intensity;
	t_col		colour;
}				t_ambient;

typedef struct s_cam_config
{
	t_vec3		pos;
	t_vec3		vup;				//camera up vector
	t_vec3		lookat;
}				t_cam_config;

typedef struct s_camera
{
	t_vec3		pos;
	t_vec3		ori;
	t_vec3		vup;				//camera up vector
	t_vec3		vup_ori;			//ori camera up vector
	t_vec3		lookat;				//specific point that camera pointing to
	t_vec3		lookat_ori;			//specific point that camera pointing to
	// t_cam_config	ori;
	// t_cam_config	dup;
	float		hfov;				//horizontal fov
	float		focus_dist;
	float		defoc_ang;			//blur angle
	t_vec3		defoc_disk[2];
	int			sample_per_pixel;
	t_uchar		ray_bounce;			//how many times a ray should bounce
	t_transform	transform;
}				t_camera;

//vup, lookat, pos

typedef struct s_light
{
	t_vec3		pos;
	float		brightness;
	t_col		colour;
}				t_light;

typedef struct s_sphere
{
	t_vec3		pos;
	float		rad;
	// t_transform	transform;
}				t_sphere;

typedef struct s_plane
{
	t_vec3		pos;
	t_vec3		normal;
	t_vec3		coord[2];	//u, v
	float		d;			//D is in plane formula: Ax + By + Cz = D
	t_vec3		w;			//const calc if pt hit within quad surf
	bool		b_rotate;
}				t_plane;

// typedef struct s_quad
// {
// 	t_vec3		pos;
// 	t_vec3		coord[2];	//u, v
// 	t_vec3		normal;
// 	float		d;			//D in plane formula: Ax + By + Cz = D
// 	t_vec3		w;			//const calc if pt hit within quad surf
// }				t_quad;

typedef struct s_cylinder
{
	t_vec3		pos;
	t_vec3		axis;
	t_vec3		axis_height;
	float		rad;
	float		height;
	t_vec3		coord[2];
	float		d[2];	// d[0]:bottom_cap, d[1]:top cap
	t_vec3		w;		// for calculating plane alpha beta or x-z side
}				t_cy;

typedef enum e_obj_type
{
	SPHERE = 0,
	PLANE = 1,
	CYLINDER = 2,
	BVH = 3,
}				t_obj_type;

typedef struct s_obj
{
	t_obj_type	type;			// tells what type of obj
	union						// stores the actual shape of data 
	{
		t_sphere	sph;
		t_plane		plane;
		t_cy		cyl;
	};
	t_uint		id;
	t_mat		material;
	t_vec3		bbox_center;
	t_interval	bbox[3];
	t_interval	bbox_ori[3];

	bool		b_rotate;
	t_vec3		rotate;
}				t_obj;

#endif
