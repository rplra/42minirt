/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:49:25 by rraja-az          #+#    #+#             */
/*   Updated: 2025/10/07 21:00:38 by hsim             ###   ########.fr       */
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
# include "render.h"
# include "transform.h"

# define RED				"\033[31m"
# define TURQ				"\033[38;2;29;253;227m"
# define MINT				"\033[38;2;134;255;199m"
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

#endif