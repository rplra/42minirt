/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:05:46 by hsim              #+#    #+#             */
/*   Updated: 2025/07/07 14:14:58 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <stdbool.h>         // for bool
# include "scene.h"           // for t_object, t_obj_type
# include "interval.h"        // for t_interval
# include "../lib/quaternion/ft_vector.h" 

typedef struct s_rt			t_rt;
typedef struct s_ray		t_ray;
typedef struct s_img		t_img;
typedef struct s_interval	t_interval;
typedef unsigned char		t_uchar;

enum	e_vector_values
{
	X = 0,
	Y = 1,
	Z = 2,
	W = 0,
	H = 1
};

enum	e_quadratic_values
{
	A = 0,
	B = 1,
	C = 2
};

typedef struct s_ray
{
	t_vec3		orig;
	t_vec3		vector;
}	t_ray;

typedef struct s_hit
{
	t_vec3		at;				// intersection point
	t_vec3		surf_norm;		// surface normal at the point
	t_obj		*obj;			// the object hit
	float		t;				// ray paremeter (distance)
	bool		front_face;		// for correct normal orientation
}				t_hit;

// typedef struct s_record
// {
// 	float		t;			//t = pt along a ray (formula: pt_at = a + t*d)
// 	t_vec3		surf_norm;	//surface_normal
// 	t_vec3		at;			//pt_at, result frm a + t*d
// }	t_record;

// enum	e_material_type
// {
// 	DIFFUSE,
// 	METAL,
// 	// DIELEC
// 	// BUBBLE
// };

// typedef struct s_ray
// {
// 	t_vec3	orig;
// 	t_vec3	vector;
// }	t_ray;

// typedef struct s_mat
// {
// 	t_uchar			type;		//material type
// 	t_vec3			albedo;		//obj base color
// }	t_mat;

// typedef struct s_sph
// {
// 	t_vec3			orig;		//origin
// 	float			rad;		//radius
// 	// t_mat		mat;
// }	t_sph;

// typedef struct s_obj
// {
// 	t_obj_type		type;		// tells what type of obj
// 	union
// 	{
// 		t_sph		sph;
// 		t_plane		plane;
// 		t_cylinder	cyl;
// 	};
// 	t_mat			mat;
// 	struct s_obj	*next;
// }	t_obj;

/* __________________ initialization __________________ */
void		initialize_mlx(t_rt *vars);
void		init_variable(t_rt *vars);
void		init_obj(t_rt *vars);

/* __________________ bound box __________________ */
void		aabb(t_vec3 a, t_vec3 b, t_interval range[3]);
void		get_bbox(t_obj_type type, t_obj *obj, t_interval bound_box[3]);
void		update_aabb_box(t_interval box_0[3], t_interval box_1[3], \
t_interval res[3]);

t_interval	new_interval(float min, float max);
t_interval	interval(t_interval a, t_interval b);

/* __________________ objs __________________ */
//t_obj		*new_sph(t_vec3 position, float sph_radius, t_vec3 color, t_uchar mat_type);
//t_sph		new_sphere(t_vec3 position, float sph_radius, t_vec3 color, t_uchar mat_type);
//void		new_obj(t_rt *vars, t_obj **lst, t_obj *new);


/* __________________ img render __________________ */
void		my_mlx_pixel_put(t_rt vars, int x, int y, int color);
void		my_create_image(t_rt *vars, t_img *img);
void		my_render_image(t_rt *vars);
void		clear_image(t_rt vars, int win_width, int win_height, int color);

/* __________________ ray __________________ */
// float		has_hit_sphere(t_vec3 sphere, float radius, t_ray ray);
void		init_hit_func(float (*has_hit[])());
float		has_hit_plane(t_obj obj, t_interval ray_range, t_ray ray);
float		has_hit_sphere(t_obj obj, t_interval ray_range, t_ray ray);
float		has_hit_cylinder(t_obj obj, t_interval ray_range, t_ray ray);
t_vec3		ray_color(t_rt *vars, t_ray ray, t_uchar ray_bounce, \
t_uint *seed);
// t_vect3d	ray_color_loop(t_vars vars, t_ray ray, unsigned int *seed);
t_ray		new_ray(t_vec3 origin, t_vec3 dir);
int			sample_pixels(t_rt vars, t_vec3 target, t_vec3 viewport_d[2], int x);
t_vec3		sample_sq_rand(unsigned int *seed);
t_vec3		point_at(float t, t_ray ray);
void		init_surf_norm(t_vec3 (*get_surf_norm[])(t_ray, t_obj, float));
t_vec3		get_surf_norm_plane(t_ray ray, t_obj obj, float t);
t_vec3		get_surf_norm_sph(t_ray ray, t_obj obj, float t);
t_vec3		get_surf_norm_cyl(t_ray ray, t_obj obj, float t);
t_obj		*hit(t_rt *vars, t_interval ray_range, t_ray ray);

// t_obj	*hit(t_rt *vars, t_interval ray_range, t_vec3 *at);
// t_obj	*hit(t_rt *vars, t_ray ray, t_vec3 *surf_norm, t_vec3 *at);

/* __________________ color __________________ */
t_vec3		lerp_rgb(t_vec3 c1, t_vec3 c2, float t);
int			create_rgb(int r_value, int g_value, int b_value);
t_vec3		color_correction(t_vec3 color);
t_vec3		split_rgb(int color);

/* __________________ utils __________________ */
bool		is_near_zero(t_vec3 vec);
void		vec3_to_arr(t_vec3 pt, float res[3]);


/* __________________ random __________________ */
float		rand_lcg(unsigned int *seed);
float		rand_lcg_range(unsigned int *seed, float min, float max);
t_vec3		rand_vec(unsigned int *seed);
t_vec3		rand_vec_range(unsigned int *seed, float min, float max);
t_vec3		rand_unit_vec(unsigned int *seed);
t_vec3		rand_unit_disk(unsigned int *seed);

/* __________________ malloc functions __________________ */
//int			malloc_sph_ptr(t_sph **dest, int num);

/* __________________ memory free functions __________________ */
void		free_malloc(t_rt *vars, int indicator);
//void		ft_lstclear_obj(t_obj **lst);

/* __________________ debug functions __________________ */
void		debug_print_vec(char *str, t_vec3 vec);


/*			normal.c		*/
// void		get_normal(t_hit *hit);
// t_vec3	get_cylinder_normal(t_vec3 point, t_cylinder *cy);

/*			light.c			*/
t_vec3		ambient(t_hit *hit, t_ambient amb);
t_vec3		diffuse(t_hit *hit, t_light *light);
t_vec3		specular(t_hit *hit, t_light *light, t_camera *camera);
t_vec3		light_col(t_hit *hit, t_rt *rt);
t_vec3		reflect(t_vec3 I, t_vec3 N);

/*			shadow.c		*/
int			is_shadow(t_rt	*vars, t_vec3 point, t_vec3 normal, t_rt *rt);

#endif