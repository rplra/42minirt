/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:01:32 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/19 12:25:01 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "scene.h"

/*	math constant	*/
# define EPSILON 0.00001
//# define PI 3.14159265358979323846

/*	window	*/
# define WIN_WIDTH	600
# define WIN_HEIGHT	400

/*	ambient	*/
# define AMBIENT_RATIO_MIN	0.0
# define AMBIENT_RATIO_MAX	1.0

/*	colour	*/
# define COL_MIN	0
# define COL_MAX	255

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

/*	material	*/
# define MAT_TYPE		METAL
# define MAT_SPECULAR	0.5
# define MAT_REFLECT	0.5
# define MAT_FUZZ		0.2

/*	sample	*/
# define SAMPLE_SOFT_SHADOW		15  // > == softer shadow
# define SAMPLE_RAY_BOUNCE		5	// > == more realistic lighting
# define SAMPLE_PER_PIXEL		5	// > == smoother img


#endif