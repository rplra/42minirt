/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:01:32 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/05 15:02:39 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "scene.h"

/*	math constant	*/
# define EPSILON		0.00001
//# define PI 3.14159265358979323846

/*	window	*/
# define WIN_WIDTH		800
# define WIN_HEIGHT		600

/*	menu	*/
# if WIN_HEIGHT <= 400
#  define MENU			"asset/menu-400.xpm"
#  define PANEL_WIDTH	133
# elif WIN_HEIGHT <= 600
#  define MENU			"asset/menu-600.xpm"
#  define PANEL_WIDTH	199
# elif WIN_HEIGHT <= 800
#  define MENU			"asset/menu-800.xpm"
#  define PANEL_WIDTH	266
# endif

# define TOTAL_WIDTH	(WIN_WIDTH + PANEL_WIDTH)

/*	ambient	*/
# define AMBIENT_RATIO_MIN	0.0
# define AMBIENT_RATIO_MAX	1.0

/*	colour	*/
# define COL_MIN	0
# define COL_MAX	255

# define BLACK		0x000000  // (0, 0, 0)
# define GREEN		0x00FF00  // (0, 255, 0)
# define YELLOW		0xFFFF00  // (255, 255, 0)
# define BLUE		0x0000FF  // (0, 0, 255)
# define MAGENTA	0xFF00FF  // (255, 0, 255)
# define CYAN		0x00FFFF  // (0, 255, 255)
# define WHITE		0xFFFFFF  // (255, 255, 255)
# define GREY		0x808080  // (128, 128, 128)

/*	vector	*/
# define VEC_MIN	-1
# define VEC_MAX	1

/*	camera	*/
# define FOV_MIN	0
# define FOV_MAX	180
# define DEFOC_ANG	radian(0)
# define DEFOC_XX	0
# define DEFOC_XY	0
# define DEFOC_XZ	0
# define DEFOC_YX	0
# define DEFOC_YY	0
# define DEFOC_YZ	0

/*	light	*/
# define LIGHT_BRIGHTNESS_MIN	0.0
# define LIGHT_BRIGHTNESS_MAX	1.0
# define LIGHT_RADIUS			0.1

/*	plane	*/
# define PLANE_X				-4
# define PLANE_Y				4

/*	material	*/
# define MAT_TYPE				DIFFUSE
# define MAT_SPECULAR			0.5
# define MAT_REFLECT			0.5
# define MAT_FUZZ				0.2

/*	sample	*/
# define SAMPLE_SOFT_SHADOW		15  // > == softer shadow
# define SAMPLE_RAY_BOUNCE		5	// > == more realistic lighting
# define SAMPLE_PER_PIXEL		100	// > == smoother img
# define SAMPLE_PREVIEW			2

#endif