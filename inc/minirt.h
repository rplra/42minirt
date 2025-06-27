/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:49:25 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/27 16:36:05 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <errno.h>
# include <fcntl.h>
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
# include "config.h"
# include "keymap.h"
# include "keybind.h"
# include "ray.h"
# include "utils.h"
# include "scene.h"
# include "parse.h"
# include "interval.h"
# include "render.h"

# define RED "\033[31m"
# define RESET "\033[0m"

# define YES	1
# define NO		0

typedef unsigned int		t_uint;
typedef struct s_ray		t_ray;
typedef struct s_sph		t_sph;
typedef struct s_obj		t_obj;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_rt
{
	void		*mlx;
	void		*mlx_win;
	t_img		img;
	t_camera	cam;

	//scene
	t_vec3		color_bg[2];
	t_obj		*obj;
	t_sph		*sph;
	int			count_sph;
	t_interval	bbox[3];	//bounding box, aabb = t_interval[3]

	//general
	t_ray		ray;		//helper pointer

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