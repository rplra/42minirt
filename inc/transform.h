/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:22:13 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/04 18:09:36 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/quaternion/ft_vector.h"

#ifndef TRANSFORM_H
# define TRANSFORM_H

# define TRANSLATE	1.0f
// # define TRANSLATE	0.5f
# define SCALE_UP	1.1f
# define SCALE_DOWN 0.9f
# define ROTATE		5.0f

typedef struct s_transform
{
	t_vec3		translate;
	// t_vec3		scale;
	t_vec3		rotate;
}				t_transform;

#endif