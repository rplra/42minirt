/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:22:13 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/14 15:59:36 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
# define TRANSFORM_H

# include "../lib/quaternion/ft_vector.h"

# define TRANSLATE	1.0f
# define SCALE_UP	1.1f
# define SCALE_DOWN 0.9f
# define ROTATE		15.0f

typedef struct s_transform
{
	t_vec3		translate;
	t_vec3		rotate;
}				t_transform;

#endif