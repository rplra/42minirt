/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 08:44:18 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/10 12:40:21 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vector_len(t_vector vec)
{
	return ((sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.y, 2))));
}

t_vector	*vector_normalize(t_vector *vec)
{
	double	norm;

	norm = vector_len(*vec);
	if (norm == 0.0)
		exit_with_error("Error: Vector length is zero, unable to normalize\n");
	norm = 1.0 / norm;
	vec->x *= norm;
	vec->y *= norm;
	vec->z *= norm;
	return (vec);
}