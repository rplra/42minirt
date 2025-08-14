/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:49:25 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/14 15:26:14 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../lib/gnl/get_next_line.h"
# include "../lib/inc/libft.h"
# include "../lib/quaternion/ft_enum.h"
# include "../lib/quaternion/ft_vector.h"
# include "config.h"
# include "keybind.h"
# include "parse.h"
# include "scene.h"
# include "utils.h"
# include <errno.h>
# include <fcntl.h>
# include <float.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// # include "interval.h"
# include "render.h"
# include "transform.h"

# define RED				"\033[31m"
# define RESET				"\033[0m"

# define YES				1
# define NO					0

typedef unsigned int		t_uint;
typedef struct s_bvh_tree	t_bvh_tree;

typedef struct s_animate
{
	int						count;
	float					step;
	float					pos;
	float					intensity;
}							t_animate;

typedef struct s_rt
{
	// mlx
	void					*mlx;
	void					*mlx_win;
	t_img					img;
	t_img					img_menu;
	t_img					img_load;
	t_img					img_intro;

	// interactive
	bool					b_preview_mode;
	bool					b_show_light;
	bool					b_animate;
	int						b_style;
	t_sel					sel;
	t_label					label;
	t_info					info;

	// animate
	t_animate				animate;

	// scene
	t_ambient				ambient;
	t_camera				camera;
	t_light					light;
	t_obj					*obj;
	size_t					obj_count;
	t_vec3					color_bg[2];

	// raytracing
	t_hit					hit;
	t_ray					ray;	// helper pointer
	t_uint					seed;

	t_bvh_tree				*bvh;

	// transform
	t_transform				transform;
}							t_rt;

// typedef struct s_vars
// {
// 	void		*mlxconnect;
// 	void		*mlxwindow;
// 	t_img		img;

// 	//camera setup
// 	t_vec3			cam_orig;
// 	t_vec3			cam_lookat;
// 	t_vec3			vup; //camera orientation
// 	float			vfov; //vertical fov
// 	float			focus_dist;
// 	float			defoc_ang; //blur angle
// 	t_vec3			defoc_disk[2];
// 	int				sample_per_pixel;
// 	t_uchar			ray_bounce; //how many times a ray should bounce

// 	//scene
// 	t_vec3			color_bg[2];
// 	//obj
// 	int				count_sph;
// 	t_sph			*sph;

// 	//general
// 	t_ray			ray; //helper pointer
// }	t_vars;

#endif