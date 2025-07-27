/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:22:13 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/27 23:04:05 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#ifndef TRANSFORM_H
# define TRANSFORM_H

# define TRANSLATE	0.5f
# define SCALE_UP	1.1f
# define SCALE_DOWN 0.9f
# define ROTATE		1.0f

typedef struct s_transform
{
	t_vec3		translate;
	t_vec3		scale;
	t_vec3		rotate;
}				t_transform;

#endif