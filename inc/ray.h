/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:12:17 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/02 16:46:22 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "scene.h"

typedef struct s_ray
{
	t_vec3	orig;
	t_vec3	vector;
}	t_ray;

typedef struct s_hit
{
	t_vec3		point;			// intersection point
	t_vec3		normal;			// surface normal at the point
	t_object	*obj;			// the object hit
	float		t;				// ray paremeter (distance)
	bool		front_face;		// for correct normal orientation
}				t_hit;

// normal.c
void		get_normal(t_hit *hit);
t_vec3		get_cylinder_normal(t_vec3 point, t_cylinder *cy);

// light.c
t_vec3		ambient(t_hit *hit, t_ambient amb);
t_vec3		diffuse(t_hit *hit, t_light *light);
t_vec3		specular(t_hit *hit, t_light *light, t_camera *camera);
t_vec3		light_col(t_hit *hit, t_scene *scene);

// shadow.c


t_vec3		reflect(t_vec3 I, t_vec3 N);

#endif