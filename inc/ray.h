/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:12:17 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/24 10:11:08 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RAY_H
# define RAY_H

#include "scene.h"

typedef struct s_ray
{
	t_vector	orig;
	t_vector	vector;
}	t_ray;

typedef struct s_hit
{
	t_vector	point;			// intersection point
	t_vector	normal;			// surface normal at the point
	t_object	*obj;			// the object hit
	float		t;				// ray paremeter (distance)
	bool		front_face;		// for correct normal orientation
}				t_hit;

float		vector_len(t_vector vec);
t_vector	vector_subtract(t_vector v1, t_vector v2);
t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	vector_scale(t_vector v, float scale);
t_vector	vector_negate(t_vector v);
t_vector	vector_normalize(t_vector vec);

t_colour	colour_add(t_colour c1, t_colour c2);
t_colour	colour_multiply(t_colour c1, t_colour c2);
t_colour	colour_scale(t_colour col, float scale);

// product.c
float		dot_product(t_vector u, t_vector v);
t_vector 	cross_product(t_vector u, t_vector v);

// normal.c
void		get_normal(t_hit *hit);
t_vector	get_cylinder_normal(t_vector point, t_cylinder *cy);


// light.c
t_colour	ambient(t_hit *hit, t_ambient amb);
t_colour	diffuse(t_hit *hit, t_light *light);
t_colour	specular(t_hit *hit, t_light *light, t_camera *camera);
t_colour	light_col(t_hit *hit, t_scene *scene);

t_vector	reflect(t_vector I, t_vector N);

#endif