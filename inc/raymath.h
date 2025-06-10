/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymath.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:12:17 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/10 12:13:01 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RAYMATH_H
# define RAYMATH_H

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

double		vector_len(t_vector vec);
t_vector	*vector_normalize(t_vector *vec);

#endif