/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:05:46 by hsim              #+#    #+#             */
/*   Updated: 2025/08/17 15:45:46 by rraja-az         ###   ########.fr       */
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
typedef struct s_interval	t_interval;
typedef unsigned char		t_uchar;
typedef struct s_img		t_img;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

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
	t_vec3		at;			// intersection point, result frm a + t*d
	t_vec3		surf_norm;	// surface normal at the point
	t_obj		*obj;		// the object hit
	float		t;			// distance, (formula: pt_at = a + t*d)
	// float	coord[2];	// uv vals (surf coords of hit pt, for texture)
	int			index;		// object index of the hitted obj
	t_uchar		setting;	// helper variable for rendering cyl
}	t_hit;

enum	e_bvh_node
{
	L = 0,
	R = 1
};

typedef struct s_bvh_tree
{
	int			id[2];
	int			id_orig[2];
	void		*left;
	void		*right;
	t_obj_type	type[2];		//can remove this if using t_obj
	t_interval	bbox[3];
}	t_bvh_tree;

/* __________________ initialization __________________ */
void			init_mlx(t_rt *rt);
void			init_rt(t_rt *rt);
void			init_cam(t_rt *rt);
void			init_hit(t_rt *rt);
void			init_bg_color(t_rt *rt, float intensity);
// void				update_cam_pos(t_rt *rt);

void			set_render_quality(t_rt *rt);

/* __________________ aabb __________________ */
void			aabb(t_vec3 a, t_vec3 v, t_interval range[3]);
void			create_bbox(t_obj *obj, t_interval bound_box[3]);
void			copy_bbox(t_interval dest[3], t_interval src[3]);
void			update_aabb_box(t_interval box_0[3], t_interval box_1[3],
					t_interval res[3]);
void			get_bbox_val(t_obj *obj, int argc, t_interval res[3]);
void			aabb_rotate(t_obj obj, t_interval dest[3]);
void			aabb_translate(t_obj obj, t_interval res[3], t_vec3 offset);

t_interval		assign_min_max(float a, float v);
t_vec3			get_vec_min(t_vec3 j, t_vec3 k);
t_vec3			get_vec_max(t_vec3 j, t_vec3 k);
t_vec3			get_bbox_center(t_interval bbox[3]);

t_interval		new_interval(float min, float max);
t_interval		interval(t_interval a, t_interval v);
void			add_padding(t_interval res[3]);

/* __________________ objs __________________ */
void			assign_obj(t_obj *obj);
void			assign_material(t_mat *material);
void			assign_rotation(t_obj *obj);
void			assign_bbox(t_obj *obj);
void			assign_bbox_translate(t_obj *obj, t_vec3 delta);
t_mat			new_material(t_vec3 color, t_mat_type type);
t_vec3			set_tmp_vec(t_vec3 normal);
void			setup_plane_geometry(t_obj *obj);
void			setup_cylinder_geometry(t_obj *obj);
void			update_material(t_obj *obj, t_mat_type type, float fuzz);
// t_uint			get_obj_index(t_obj *obj, int obj_count, t_uint id);

// debug
t_obj			new_sphere(t_vec3 position, float sph_radius, t_vec3 color,
					t_mat_type mat_type);
t_obj			new_plane_2(t_vec3 position, t_vec3 coord_u, t_vec3 coord_v,
					t_mat mat);
t_obj			new_plane(t_vec3 position, t_vec3 normal, t_mat mat);
// t_obj		new_cyl(t_vec3 position, t_vec3 normal, t_material mat);
t_obj			new_cyl(t_vec3 position, t_vec3 normal, float radius,
					float height, t_mat mat);
t_obj			new_cyl_2(t_vec3 position, t_vec3 coord_u, t_vec3 coord_v,
					float radius, float height, t_mat mat);

/* __________________ func_pointers __________________ */
void			init_box_compare(bool (*box_compare[])(t_obj, t_obj));
void			init_surf_norm(t_vec3 (*get_surf_norm[])(t_ray, t_obj,
						float, t_uchar));
void			init_hit_func(bool (*has_hit[])());
void			init_loading_img(t_rt *rt);

/* __________________ merge_sort __________________ */
void			copy_array(t_obj *dest, t_obj *src, int n);
void			copy_obj(t_obj *dest, t_obj src);
void			merge_sort(t_obj *res, int argc, bool (*func)(t_obj, t_obj));

/* __________________ bvh __________________ */
t_bvh_tree		*build_bvh_tree(t_obj *obj, int id[2],
					bool (*func[3])(t_obj, t_obj));
void			init_bvh_node(t_rt *vars);

/* __________________ img render __________________ */
void			render(t_rt *rt);
void			ft_mlx_pixel_put(t_rt vars, int x, int y, int color);
void			ft_create_img(t_rt *vars, t_img *img);
void			render(t_rt *vars);
void			load_menu(t_rt *rt, t_img *img, char *filepath,
					int size[2]);
void			clear_image(t_rt vars, int win_width, int win_height,
					int color);
int				animate_loading(t_rt *rt);
void			load_menu_label_info(t_rt *rt);

/* __________________ rotate __________________ */
t_ray			transform_ray(t_obj obj, t_ray ray);
void			transform_hit_pt(t_rt *rt, t_obj res);
void			transform_bbox(t_rt *rt, t_uint index);

/* __________________ hit __________________ */
t_obj			*hit(t_rt *rt, t_interval ray_range, t_ray ray);
bool			hit_bvh(t_bvh_tree *bvh, t_interval ray_range,
					t_ray ray, t_rt *vars);
bool			has_hit_sphere(t_rt *rt, int index, t_interval ray_range,
					t_ray ray);
bool			has_hit_plane(t_rt *rt, int index, t_interval ray_range,
					t_ray ray);
bool			within_plane_range(float alpha, float beta, int flag);
bool			has_hit_cylinder(t_rt *rt, int index, t_interval ray_range,
					t_ray ray);
float			check_hit_body(t_rt *rt, int i, t_ray ray, float t[2]);
float			has_hit_body(t_cylinder cyl, t_interval ray_range,
					t_ray ray, float t[2]);
float			has_hit_cap(t_rt *rt, int i, t_interval ray_range, t_ray ray);
int				update_hit_rec(t_rt *vars, int index, t_ray ray, float t);

void			get_point_on_surf(t_cylinder cyl, t_ray ray, float t[2],
					float res[2]);
t_interval		get_cyl_axis_height(t_cylinder cyl);

t_vec3			set_face_norm(t_ray ray, t_vec3 surf_norm);
t_vec3			get_surf_norm_plane(t_ray ray, t_obj obj, float t,
					t_uchar setting);
t_vec3			get_surf_norm_sph(t_ray ray, t_obj obj, float t,
					t_uchar setting);
t_vec3			get_surf_norm_cyl(t_ray ray, t_obj obj, float t,
					t_uchar setting);

/* __________________ ray __________________ */
t_vec3			ray_color(t_rt *vars, t_ray ray, t_uchar ray_bounce,
					t_uint *seed);
t_vec3			bg_color(t_rt vars, t_ray ray);
t_ray			new_ray(t_vec3 origin, t_vec3 dir);
int				sample_pixels(t_rt rt, t_vec3 target, t_vec3 viewport_d[2],
					t_uint *seed);
t_vec3			sample_sq_rand(unsigned int *seed);
t_vec3			point_at(float t, t_ray ray);

/* __________________ color __________________ */
int				create_rgb(int r_value, int g_value, int b_value);
t_col			lerp_rgb(t_col c1, t_col c2, float t);
t_col			color_correction(t_col color);
t_col			split_rgb(int color);

/* __________________ utils __________________ */
bool			is_near_zero(t_vec3 vec);
void			vec3_to_arr(t_vec3 pt, float res[3]);
// void			swap_float(float t[2]);
void			assign_int(int value[2], int width, int height);

/* __________________ random __________________ */
float			rand_lcg(unsigned int *seed);
float			rand_lcg_range(unsigned int *seed, float min, float max);
t_vec3			rand_vec(unsigned int *seed);
t_vec3			rand_vec_range(unsigned int *seed, float min, float max);
t_vec3			rand_unit_vec(unsigned int *seed);
t_vec3			rand_unit_disk(unsigned int *seed);
int				rand_int(unsigned int *seed, int min, int max);

/* __________________ malloc functions __________________ */
int				malloc_obj_ptr(t_obj **dest, int num);

/* __________________ memory free functions __________________ */
void			free_bvh(t_bvh_tree *bvh);
void			free_render(t_rt *rt, int indicator);
// void			ft_lstclear_obj(t_obj **lst);

/* __________________ debug_scene functions __________________ */
void			init_obj(t_rt *rt);
void			init_sph_scene(t_rt *rt);
void			init_plane_scene(t_rt *rt);
void			init_cyl_scene(t_rt *rt);

/* __________________ debug_print functions __________________ */
void			debug_print_vec(char *str, t_vec3 vec);
void			debug_print_lst(char *str, t_obj *lst);
void			debug_print_arr(char *str, t_obj *obj, int obj_count);
void			debug_print_bvh(char *str, t_bvh_tree *bvh);
void			debug_print_bbox(char *str, t_interval bbox[3]);

t_vec3			mat_lambertian(t_vec3 surf_norm, t_uint *seed);
t_vec3			mat_metal(t_vec3 incoming_ray, t_vec3 surf_norm,
					float fuzz, t_uint *seed);

#endif