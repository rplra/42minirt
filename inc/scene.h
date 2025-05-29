/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:32:00 by rraja-az          #+#    #+#             */
/*   Updated: 2025/05/29 16:55:16 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

typedef struct	s_colour
{
	uint		r;
	uint		g;
	uint		b;		
}				t_colour;

typedef struct s_material
{
	t_colour	diffuse;
	double		specular;
	double		reflect;
	double		refract;
}				t_material;

typedef struct	s_ambient
{
	double		ratio;
	t_colour	colour;
}				t_ambient;

typedef struct s_camera
{
	t_vector	origin;
	t_vector	orientation;
	uint		fov;
}				t_camera;

typedef struct s_light
{
	t_vector	position;
	double		brightness;
	t_colour	colour;
}				t_light;

typedef struct s_sphere
{
	t_vector	center;
	double		diameter;
}				t_sphere;

typedef struct s_plane
{
	t_vector	point;
	t_vector	normal;
}				t_plane;

typedef struct s_cylinder
{
	t_vector	point;
	t_vector	normal;
}				t_cylinder;

typedef enum 	e_obj_type
{
	obj_ambient,
	obj_camera,
	obj_light,
	obj_sphere,
	obj_plane,
	obj_cylinder,
}				t_obj_type;

typedef union	u_obj
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}				t_obj_union;

typedef	struct s_object
{
	t_obj_type	type;
	t_obj_union	obj;
	t_colour	colour;
	t_material	material;
}				t_object;

typedef struct	s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		*lights;
	t_object	*objects;
}				t_scene;

#endif
