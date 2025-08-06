/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:49:25 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/06 15:35:19 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <errno.h>
# include <fcntl.h>
# include <float.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>

# include "../lib/inc/libft.h"
# include "../lib/gnl/get_next_line.h"
# include "../lib/quaternion/ft_vector.h"
# include "../lib/quaternion/ft_enum.h"
# include "config.h"
# include "keybind.h"
# include "utils.h"
# include "scene.h"
# include "parse.h"
// # include "interval.h"
# include "render.h"
# include "transform.h"

# define RED "\033[31m"
# define RESET "\033[0m"

# define YES	1
# define NO		0

typedef unsigned int		t_uint;
// typedef struct s_hit		t_hit;
// typedef struct s_ray		t_ray;
// typedef struct s_sph		t_sphere;
// typedef struct s_obj		t_obj;
typedef struct s_bvh_tree	t_bvh_tree;
typedef struct s_sel 		t_sel; 

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

// typedef struct s_animate
// {
// 	t_uint	i;
// 	char	**path;	//malloc
// 	int		size[2];
// }	t_animate;


typedef struct s_rt
{
	//mlx
	void		*mlx;
	void		*mlx_win;
	t_img		img;
	t_img		img_menu;
	t_img		img_load;
	t_img		img_intro;

	//interactive
	bool		b_preview_mode;
	bool		b_show_light;
	t_sel		sel;

	//scene
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_obj		*obj;
	size_t		obj_count;
	t_vec3		color_bg[2];

	// raytracing
	t_hit		hit;
	t_ray		ray;		//helper pointer
	t_uint		seed;

	t_bvh_tree	*bvh;

	//transform
	t_transform transform;
}				t_rt;

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