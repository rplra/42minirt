/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymath.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:12:17 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/24 18:36:30 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RAYMATH_H
# define RAYMATH_H

# include "scene.h"

double		vector_len(t_vector vec);
t_vector	vector_subtract(t_vector v1, t_vector v2);
t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	vector_multiply(t_vector v, float f);
t_vector	*vector_normalize(t_vector *vec);

t_colour	colour_multiply(t_colour c1, t_colour c2);
t_colour	colour_scale(t_colour col, float scale);

// light.c
t_colour	ambient(t_object *obj, t_ambient amb);
t_colour	diffuse(t_object *obj, t_light *light, t_vector intersection, t_vector normal);

#endif