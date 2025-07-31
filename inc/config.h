/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:01:32 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/29 17:43:37 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

/*	math constant	*/
# define EPSILON 0.00001
# define PI 3.14159265358979323846

/*	window	*/
# define WIN_WIDTH	300
# define WIN_HEIGHT	200

/*	ambient	*/
# define AMBIENT_RATIO_MIN	0.0
# define AMBIENT_RATIO_MAX	1.0

/*	colour	*/
# define COL_MIN	0
# define COL_MAX	255

/*	normal vector	*/
# define VEC_MIN	-1
# define VEC_MAX	1

/*	camera	*/
# define FOV_MIN	0
# define FOV_MAX	180

/*	light	*/
# define LIGHT_BRIGHTNESS_MIN	0.0
# define LIGHT_BRIGHTNESS_MAX	1.0


#endif