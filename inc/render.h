/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:05:46 by hsim              #+#    #+#             */
/*   Updated: 2025/06/27 14:08:19 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"

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

typedef struct s_mat
{
	t_uchar	type;		//material type
	t_vec3	albedo;		//obj base color
}	t_mat;

typedef struct s_sph
{
	t_vec3		orig;	//origin
	float		rad;	//radius
	t_mat		mat;
}	t_sph;

typedef struct s_obj
{
	t_obj_type		type;		// tells what type of obj
	t_obj_union		*is;		// stores the actual shape of data
	t_mat			mat;
	struct s_obj	*next;
}					t_obj;

void		initialize_mlx(t_rt *vars);
void		init_variable(t_rt *vars);

/* __________________ bound box __________________ */
void		bounding_box(t_obj_type type, void *obj, t_interval bound_box[3]);
t_interval	new_interval(float min, float max);
t_interval	interval(t_interval a, t_interval b);

/* __________________ objs __________________ */
t_sph	new_sphere(t_vec3 position, float sph_radius, t_vec3 color, t_uchar mat_type);


/* __________________ img render __________________ */
void		my_mlx_pixel_put(t_rt vars, int x, int y, int color);
void		my_create_image(t_rt *vars, t_img *img);
void		my_render_image(t_rt *vars);
void		clear_image(t_rt vars, int win_width, int win_height, int color);

/* __________________ ray __________________ */
float		has_hit_sphere(t_vec3 sphere, float radius, t_ray ray);
t_vec3		ray_color(t_rt vars, t_ray ray, unsigned char ray_bounce, unsigned int *seed);
// t_vector3d	ray_color_loop(t_vars vars, t_ray ray, unsigned int *seed);
t_ray		new_ray(t_vec3 origin, t_vec3 dir);
int			sample_pixels(t_rt vars, t_vec3 target, t_vec3 viewport_d[2], int x);
t_vec3		sample_sq_rand(unsigned int *seed);

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
int			malloc_sph_ptr(t_sph **dest, int num);

/* __________________ memory free functions __________________ */
void		free_malloc(t_rt *vars, int indicator);

/* __________________ debug functions __________________ */
void		debug_print_vec(char *str, t_vec3 vec);

#endif