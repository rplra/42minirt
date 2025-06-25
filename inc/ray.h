/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:12:17 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/24 22:10:56 by hsim             ###   ########.fr       */
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

float		vector_len(t_vec3 vec);
t_vec3		vector_subtract(t_vec3 v1, t_vec3 v2);
t_vec3		vector_add(t_vec3 v1, t_vec3 v2);
t_vec3		vector_scale(t_vec3 v, float scale);
t_vec3		vector_negate(t_vec3 v);
t_vec3		vector_normalize(t_vec3 vec);

t_colour	colour_add(t_colour c1, t_colour c2);
t_colour	colour_multiply(t_colour c1, t_colour c2);
t_colour	colour_scale(t_colour col, float scale);

// product.c
float		dot_product(t_vec3 u, t_vec3 v);
t_vec3 		cross_product(t_vec3 u, t_vec3 v);

// normal.c
void		get_normal(t_hit *hit);
t_vec3		get_cylinder_normal(t_vec3 point, t_cylinder *cy);


// light.c
t_colour	ambient(t_hit *hit, t_ambient amb);
t_colour	diffuse(t_hit *hit, t_light *light);
t_colour	specular(t_hit *hit, t_light *light, t_camera *camera);
t_colour	light_col(t_hit *hit, t_scene *scene);

t_vec3		reflect(t_vec3 I, t_vec3 N);

#endif